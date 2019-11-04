#include <cstdlib>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "window.h"
#include "shape_index.h"
#include "model_data.h"
#include "opengl_genderer.h"
#include "fbx_loader.h"
#include <ObjectArray.h>

// 六面体の頂点の位置
constexpr Vertex cube_vertex[] =
{
	{ -1.0f, -1.0f, -1.0f},  // (0)   
{ -1.0f, -1.0f,  1.0f },  // (1)   
{ -1.0f,  1.0f,  1.0f },  // (2)  
{ -1.0f,  1.0f, -1.0f },  // (3)   
{  1.0f,  1.0f, -1.0f },  // (4)  
{  1.0f, -1.0f, -1.0f },  // (5)  
{  1.0f, -1.0f,  1.0f },  // (6)  
{  1.0f,  1.0f,  1.0f }   // (7) 
};

// 六面体の稜線の両端点のインデックス
constexpr GLuint wireCubeIndex[] =
{
	1, 0, // (a) 
	2, 7, // (b)  
	3, 0, // (c)  
	4, 7, // (d)  
	5, 0, // (e)  
	6, 7, // (f)  
	1, 2, // (g)  
	2, 3, // (h) 
	3, 4, // (i)   
	4, 5, // (j)   
	5, 6, // (k) 
	6, 1  // (l) 
};

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

	glViewport(100, 50, 640, 480);    // ビューポートを設定する
	FbxLoader loader;

	ModelData* data = loader.Load("cube.fbx");

	OpenGLRenderer* renderer = new OpenGLRenderer(new ShapeIndex(3, data->vertices_count, data->vertices.data(), data->indices_count, data->indices.data()), "point.vert", "point.frag", &window);

	while (window.IsOpenWindow()) {
		glClear(GL_COLOR_BUFFER_BIT);		// ウィンドウを削除する

		//描画処理
		renderer->Draw();
		window.SwapBuffers();
		glfwWaitEvents();		//イベントを取り出す
	}
	return 0;
}