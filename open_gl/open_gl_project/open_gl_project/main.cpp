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

	Window window;

	glfwSwapInterval(1);	//���������̃^�C�~���O��҂�
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);    //�E�B���h�E�̔w�i�F��ݒ�

	glViewport(100, 50, 640, 480);    // �r���[�|�[�g��ݒ肷��
	FbxLoader loader;

	ModelData* data = loader.Load("cube.fbx");

	OpenGLRenderer* renderer = new OpenGLRenderer(new ShapeIndex(3, data->vertices_count, data->vertices.data(), data->indices_count, data->indices.data()), "point.vert", "point.frag", &window);

	while (window.IsOpenWindow()) {
		glClear(GL_COLOR_BUFFER_BIT);		// �E�B���h�E���폜����

		//�`�揈��
		renderer->Draw();
		window.SwapBuffers();
		glfwWaitEvents();		//�C�x���g�����o��
	}
	return 0;
}