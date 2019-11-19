#include <glew.h>
#include <cstdlib>
#include <iostream>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "window.h"
#include "model_data.h"
#include "renderer.h"
#include "time.h"
#include "camera.h"
#include "transform.h"
#include "component_manager.h"
#include "test_component.h"
#include "mesh_renderer.h"
#include "TestGameObject.h"

// �Z�ʑ̂̒��_�̈ʒu
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

// �Z�ʑ̗̂Ő��̗��[�_�̃C���f�b�N�X
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

	// �J�����̐ݒ�
	Camera* camera = Component::Create<Camera>();
	camera->transform_.position_ = glm::vec3(4.0f, 5.0f, 15.0f);
	camera->transform_.Rotate(0, 180, 0);
	camera->window_ = &window;

	GameObject* obje = Component::Create<TestGameObject>();

	while (window.IsOpenWindow()) {

		glfwPollEvents();
		ComponentManager::GetInstance().Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// �E�B���h�E���폜����

		ComponentManager::GetInstance().Draw();

		window.SwapBuffers();
	}

	ComponentManager::GetInstance().Finalize();

	return 0;
}