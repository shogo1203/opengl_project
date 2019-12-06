#include "opengl_genderer.h"

void OpenGLRenderer::Initialize()
{
	model_view_uniform_location_ = glGetUniformLocation(program_, "modelview");
	projection_uniform_location_ = glGetUniformLocation(program_, "projection");
	texture_location_ = glGetUniformLocation(program_, "texture_2d");
	vertex_object_.Initialize(model_data_);
}

void OpenGLRenderer::Draw()
{
	glUseProgram(program_);	// シェーダプログラムの使用開始
	glBindTexture(GL_TEXTURE_2D, model_data_->texture_id_);
	const glm::mat4 translation_mat = glm::translate(glm::mat4(1.0f), transform_->position_);
	const glm::mat4 rotation_mat = glm::toMat4(transform_->GetRotation());
	const glm::mat4 scale_mat = glm::scale(glm::mat4(1.0f), transform_->scale_);
	const glm::mat4 model_view_mat(Camera::main_->Projection() * Camera::main_->LookAt() * translation_mat * rotation_mat * scale_mat);    // モデルビュー変換行列

	// uniform変数に値を設定する
	glUniformMatrix4fv(model_view_uniform_location_, 1, GL_FALSE, &model_view_mat[0][0]);
	vertex_object_.Draw();

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);    // シェーダプログラムの使用終了
}

void OpenGLRenderer::Finalize()
{
	model_data_->Finalize();
	vertex_object_.Finalize();
	delete this;
}

void OpenGLRenderer::SetTransform(Transform* transform)
{
	transform_ = transform;
}

void OpenGLRenderer::LoadShader(const char* vertex_path, const char* fragment_path)
{
	program_ = LoadProgram(vertex_path, fragment_path);
}

void OpenGLRenderer::LoadModel(const char* model_path)
{
	model_data_ = FbxLoader::Load(model_path);
	model_data_->Initialize();
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
	glBindAttribLocation(program, 1, "color");
	glBindAttribLocation(program, 2, "normal");
	glBindAttribLocation(program, 3, "uv");

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
		return false;
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
