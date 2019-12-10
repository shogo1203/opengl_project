#include <glew.h>
#include <cstdlib>
#include <iostream>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "window.h"
#include "model_asset.h"
#include "time.h"
#include "camera.h"
#include "transform.h"
#include "component_manager.h"
#include "TestGameObject.h"
#include "scene_manager.h"

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

	ComponentManager::GetInstance().Initialize();
	Window window;
	SceneManager::GetInstance().Initialize();
	Camera::main_->window_ = &window;

	GameObject* obje = Component::Create<TestGameObject>();

	while (window.IsOpenWindow()) {

		glfwPollEvents();
		SceneManager::GetInstance().Update();
		ComponentManager::GetInstance().Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// ウィンドウを削除する

		ComponentManager::GetInstance().Draw();

		window.SwapBuffers();
	}

	ComponentManager::GetInstance().Finalize();
	SceneManager::GetInstance().Finalize();

	return 0;
}