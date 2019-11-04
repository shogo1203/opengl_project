#include "opengl_genderer.h"

OpenGLRenderer::OpenGLRenderer(Shape* shape, const char* vert_path, const char* frag_path, Window* window) :
	program_(LoadProgram(vert_path, frag_path)),
	model_view_uniform_location_(glGetUniformLocation(program_, "modelview")),
	projection_uniform_location_(glGetUniformLocation(program_, "projection")),
	shape_(shape),
	window_(window)
{
}

void OpenGLRenderer::Initialize()
{
}

void OpenGLRenderer::Draw()
{
	glUseProgram(program_);	// シェーダプログラムの使用開始

	//拡大縮小の変換行列を求める
	const GLfloat* const size(window_->GetSize());
	const GLfloat fovy(window_->GetScale() * 0.01f);
	const GLfloat aspect(size[0] / size[1]);
	const Matrix projection(Matrix::Perspective(fovy, aspect, 1.0f, 10.0f));

	const GLfloat* const location(window_->GetLocation());
	const Matrix model(Matrix::Translate(location[0], location[1], 0.0f));    // モデル変換行列を求める
	const Matrix view(Matrix::LookAt(3.0f, 4.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));    // ビュー変換行列を求める
	const Matrix model_view(view * model);    // モデルビュー変換行列を求める

	// uniform変数に値を設定する
	glUniformMatrix4fv(model_view_uniform_location_, 1, GL_FALSE, model_view.GetMatrix());
	glUniformMatrix4fv(projection_uniform_location_, 1, GL_FALSE, projection.GetMatrix());

	shape_->Draw();
}

void OpenGLRenderer::Finalize()
{
	delete shape_;
	delete this;
}

GLboolean OpenGLRenderer::PrintProgramInfoLog(GLuint program)
{
	// リンク結果を取得する
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cerr << "link error" << std::endl;
	}

	// シェーダのリンク時のログの長さを取得する
	GLsizei buf_size;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buf_size);

	if (buf_size > 1)
	{
		// シェーダのリンク時のログの内容を取得する
		std::vector<GLchar> info_log(buf_size);
		GLsizei length;
		glGetProgramInfoLog(program, buf_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

GLboolean OpenGLRenderer::PrintShaderInfoLog(GLuint shader, const char* str)
{
	// コンパイル結果を取得する
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		std::cerr << "compile error in " << str << std::endl;
	}

	// シェーダのコンパイル時のログの長さを取得する
	GLsizei buf_size;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_size);

	if (buf_size > 1)
	{
		// シェーダのコンパイル時のログの内容を取得する;
		std::vector<GLchar> info_log(buf_size);
		GLsizei length;
		glGetShaderInfoLog(shader, buf_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

GLuint OpenGLRenderer::CreateProgram(const char* v_src, const char* f_src)
{
	const GLuint program(glCreateProgram());		// 空のプログラムオブジェクトを作成する

	if (v_src != nullptr) {
		// バーテックスシェーダのシェーダオブジェクトを作成する
		const GLuint v_obj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(v_obj, 1, &v_src, NULL);
		glCompileShader(v_obj);

		// バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		if (PrintShaderInfoLog(v_obj, "vertex shader"))
		{
			glAttachShader(program, v_obj);
		}
		glDeleteShader(v_obj);
	}

	if (f_src != nullptr) {
		// フラグメントシェーダのシェーダオブジェクトを作成する
		const GLuint f_obj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(f_obj, 1, &f_src, NULL);
		glCompileShader(f_obj);

		// フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		if (PrintShaderInfoLog(f_obj, "fragment shader"))
		{
			glAttachShader(program, f_obj);
		}
		glDeleteShader(f_obj);
	}

	// プログラムオブジェクトをリンクする
	glBindAttribLocation(program, 0, "position");
	glBindFragDataLocation(program, 0, "fragment");
	glLinkProgram(program);

	// 作成したプログラムオブジェクトを返す
	if (PrintProgramInfoLog(program))
	{
		return program;
	}

	// プログラムオブジェクトが作成できなければ 0 を返す
	glDeleteProgram(program);

	return 0;
}

bool OpenGLRenderer::ReadShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	if (name == nullptr)
	{
		return false;
	}

	std::ifstream file(name, std::ios::binary);    // ソースファイルを開く

	if (file.fail())
	{
		std::cerr << "failed to open source file:" << name << std::endl;
	}

	// ファイルの末尾に移動し現在位置（＝ファイルサイズ）を得る
	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());

	buffer.resize(length + 1);    // ファイルサイズのメモリを解放

	// ファイルを先頭から読み込む
	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail())
	{
		// 読み込めなかった
		std::cerr << "could not read source file:" << name << std::endl;
		file.close();
		return false;
	}

	// 読み込めた
	file.close();
	return true;
}

GLuint OpenGLRenderer::LoadProgram(const char* vert, const char* frag)
{
	// シェーダのソースファイルを読み込む
	std::vector<GLchar> v_src;
	std::vector<GLchar> f_src;
	const bool v_stat(ReadShaderSource(vert, v_src));
	const bool f_stat(ReadShaderSource(frag, f_src));

	return v_stat && f_stat ? CreateProgram(v_src.data(), f_src.data()) : 0;
}
