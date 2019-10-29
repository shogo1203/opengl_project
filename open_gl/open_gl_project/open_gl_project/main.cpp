#include <cstdlib>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "shape.h"
#include "window.h"
#include "matrix.h"

constexpr VertexArrayObject::Vertex rectangleVertex[] =
{
	{-0.5f, -0.5f},
	{0.5f, -0.5f},
	{0.5f, 0.5f},
	{-0.5f, 0.5f}
};

// プログラムオブジェクトのリンク結果を表示する
// program: プログラムオブジェクト名
GLboolean PrintProgramInfoLog(GLuint program)
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

// shader: シェーダオブジェクト名
// str: コンパイルエラーが発生した場所を示す文字列
GLboolean PrintShaderInfoLog(GLuint shader, const char* str)
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

// vsrc: バーテックスシェーダのソースプログラムの文字列
// fsrc: フラグメントシェーダのソースプログラムの文字列
GLuint CreateProgram(const char* v_src, const char* f_src) {
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

// name: シェーダのソースファイル名
// buffer: 読み込んだソースファイルのテキスト
bool ReadShaderSource(const char* name, std::vector<GLchar>& buffer)
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

GLuint LoadProgram(const char* vert, const char* frag)
{
	// シェーダのソースファイルを読み込む
	std::vector<GLchar> v_src;
	std::vector<GLchar> f_src;
	const bool v_stat(ReadShaderSource(vert, v_src));
	const bool f_stat(ReadShaderSource(frag, f_src));

	return v_stat && f_stat ? CreateProgram(v_src.data(), f_src.data()) : 0;
}

int main() {

	//GLFWを初期化する
	if (glfwInit() == GL_FALSE) {
		std::cerr << "failed to initialize GLFW" << std::endl;
		return 0;
	}

	atexit(glfwTerminate);	//プログラム終了時の処理を登録する, glfwTerminateはglfwInit()を呼ぶ前の状態に戻れる

	//OpenGl ver 3.2 Core Profile を選択する
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Window window;

	glfwSwapInterval(1);	//垂直同期のタイミングを待つ
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);    //ウィンドウの背景色を設定

	glViewport(100, 50, 300, 300);    // ビューポートを設定する

	const GLuint program(LoadProgram("point.vert", "point.frag"));    // プログラムオブジェクトを作成

	// uniform変数の場所を取得する
	const GLuint model_view_unifrom_location(glGetUniformLocation(program, "modelview"));

	std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

	while (window.IsOpenWindow()) {
		glClear(GL_COLOR_BUFFER_BIT);		// ウィンドウを削除する

		glUseProgram(program);	// シェーダプログラムの使用開始

		//拡大縮小の変換行列を求める
		const GLfloat* const size(window.GetSize());
		const GLfloat  scale(window.GetScale() * 2.0f);
		const Matrix scaling(Matrix::Scale(scale / size[0], scale / size[1], 1.0f));

		// 並行移動の変換行列を求める
		const GLfloat* const position(window.GetLocation());
		const Matrix translation(Matrix::Translate(position[0], position[1], 0.0f));

		const Matrix model(translation * scaling);    // モデル変換行列を求める
		const Matrix view(Matrix::LookAt(0.0f, 0.0f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f));    // ビュー変換行列を求める
		const Matrix model_view(view * model);    // モデルビュー変換行列を求める

		// uniform変数に値を設定する
		glUniformMatrix4fv(model_view_unifrom_location, 1, GL_FALSE, model_view.GetMatrix());

		//描画処理
		shape->Draw();

		window.SwapBuffers();
		glfwWaitEvents();		//イベントを取り出す
	}
	return 0;
}