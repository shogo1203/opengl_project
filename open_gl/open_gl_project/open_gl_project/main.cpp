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

	//GLFW������������
	if (glfwInit() == GL_FALSE) {
		std::cerr << "failed to initialize GLFW" << std::endl;
		return 0;
	}

	atexit(glfwTerminate);	//�v���O�����I�����̏�����o�^����, glfwTerminate��glfwInit()���ĂԑO�̏�Ԃɖ߂��

	//OpenGl ver 3.2 Core Profile ��I������
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// �E�B���h�E���폜����

		ComponentManager::GetInstance().Draw();

		window.SwapBuffers();
	}

	ComponentManager::GetInstance().Finalize();
	SceneManager::GetInstance().Finalize();

	return 0;
}