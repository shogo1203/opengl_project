#include <cstdlib>
#include <iostream>
#include <glew.h>
#include <glfw3.h>

// vsrc: バーテックスシェーダのソースプログラムの文字列
// fsrc: フラグメントシェーダのソースプログラムの文字列
GLuint createProgram(const char* v_src, const char* f_src) {
	const GLuint program(glCreateProgram());		// 空のプログラムオブジェクトを作成する

	if (v_src != NULL) {
		// バーテックスシェーダのシェーダオブジェクトを作成する
		const GLuint v_obj(glCreateShader(GL_VERTEX_SHADER));  
		glShaderSource(v_obj, 1, &v_src, NULL);
		glCompileShader(v_obj);

		// バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		glAttachShader(program, v_obj);
		glDeleteShader(v_obj);
	}

	if (f_src != NULL) {
		// フラグメントシェーダのシェーダオブジェクトを作成する
		const GLuint f_obj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(f_obj, 1, &f_src, NULL);
		glCompileShader(f_obj);

		// フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		glAttachShader(program, f_obj);
		glDeleteShader(f_obj);
	}
}

int main() {

	//GLFWを初期化する
	if (glfwInit() == GL_FALSE) {
		std::cerr << "failed initialize GLFW" << std::endl;
		return 0;
	}

	atexit(glfwTerminate);	//プログラム終了時の処理を登録する, glfwTerminateはglfwInit()を呼ぶ前の状態に戻れる

	//OpenGl ver 3.2 Core Profile を選択する
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// monitor: フルスクリーンモードにするモニタを指定、フルスクリーンモードでなければNULLを指定する
	// share: 他のwindowのハンドルを指定すれば、そのウィンドウとテクスチャなどのリソースを共有します。NULLを指定すればリソースの共有は行わない
	GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello", NULL, NULL));

	if (window == NULL) {
		std::cerr << "failed create GLFW window" << std::endl;
		return 0;
	}

	glfwMakeContextCurrent(window);		//作成したウィンドウをOpenGLの処理対象にする

	glewExperimental = GL_TRUE;    //プラットフォームではサポートされていないOpenGLの機能を有効にし、プログラムから呼び出せるようにする
	if (glewInit() != GLEW_OK) {
		std::cerr << "failed initialzie GLEW" << std::endl;
	}

	glfwSwapInterval(1);	//垂直同期のタイミングを待つ
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);    //ウィンドウの背景色を設定

	while (glfwWindowShouldClose(window) == GL_FALSE) {
		glClear(GL_COLOR_BUFFER_BIT);		// ウィンドウを削除する

		//描画処理

		glfwSwapBuffers(window);	//カラーバッファを入れ替える
		glfwWaitEvents();		//イベントを取り出す
	}
	return 0;
}