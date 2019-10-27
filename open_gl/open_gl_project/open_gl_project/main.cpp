#include <cstdlib>
#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <memory>
#include "Shape.h"

constexpr VertexArrayObject::Vertex rectangleVertex[] =
{
	{-0.5f, -0.5f},
	{0.5f, -0.5f},
	{0.5f, 0.5f},
	{-0.5f, 0.5f}

};

// �v���O�����I�u�W�F�N�g�̃����N���ʂ�\������
// program: �v���O�����I�u�W�F�N�g��
GLboolean PrintProgramInfoLog(GLuint program)
{
	// �����N���ʂ��擾����
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		std::cerr << "link error" << std::endl;
	}

	// �V�F�[�_�̃����N���̃��O�̒������擾����
	GLsizei buf_size;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &buf_size);

	if (buf_size > 1)
	{
		// �V�F�[�_�̃����N���̃��O�̓��e���擾����
		std::vector<GLchar> info_log(buf_size);
		GLsizei length;
		glGetProgramInfoLog(program, buf_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

// shader: �V�F�[�_�I�u�W�F�N�g��
// str: �R���p�C���G���[�����������ꏊ������������
GLboolean PrintShaderInfoLog(GLuint shader, const char* str)
{
	// �R���p�C�����ʂ��擾����
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		std::cerr << "compile error in " << str << std::endl;
	}

	// �V�F�[�_�̃R���p�C�����̃��O�̒������擾����
	GLsizei buf_size;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &buf_size);

	if (buf_size > 1)
	{
		// �V�F�[�_�̃R���p�C�����̃��O�̓��e���擾����;
		std::vector<GLchar> info_log(buf_size);
		GLsizei length;
		glGetShaderInfoLog(shader, buf_size, &length, &info_log[0]);
		std::cerr << &info_log[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

// vsrc: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O�����̕�����
// fsrc: �t���O�����g�V�F�[�_�̃\�[�X�v���O�����̕�����
GLuint CreateProgram(const char* v_src, const char* f_src) {
	const GLuint program(glCreateProgram());		// ��̃v���O�����I�u�W�F�N�g���쐬����

	if (v_src != NULL) {
		// �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
		const GLuint v_obj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(v_obj, 1, &v_src, NULL);
		glCompileShader(v_obj);

		// �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
		if (PrintShaderInfoLog(v_obj, "vertex shader"))
		{
			glAttachShader(program, v_obj);
		}
		glDeleteShader(v_obj);
	}

	if (f_src != NULL) {
		// �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
		const GLuint f_obj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(f_obj, 1, &f_src, NULL);
		glCompileShader(f_obj);

		// �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
		if (PrintShaderInfoLog(f_obj, "fragment shader"))
		{
			glAttachShader(program, f_obj);
		}
		glDeleteShader(f_obj);
	}

	// �v���O�����I�u�W�F�N�g�������N����
	glBindAttribLocation(program, 0, "position");
	glBindFragDataLocation(program, 0, "fragment");
	glLinkProgram(program);

	// �쐬�����v���O�����I�u�W�F�N�g��Ԃ�
	if (PrintProgramInfoLog(program))
	{
		return program;
	}

	// �v���O�����I�u�W�F�N�g���쐬�ł��Ȃ���� 0 ��Ԃ�
	glDeleteProgram(program);

	return 0;
}

// name: �V�F�[�_�̃\�[�X�t�@�C����
// buffer: �ǂݍ��񂾃\�[�X�t�@�C���̃e�L�X�g
bool ReadShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	if (name == NULL)
	{
		return false;
	}

	std::ifstream file(name, std::ios::binary);    // �\�[�X�t�@�C�����J��

	if (file.fail())
	{
		std::cerr << "failed to open source file:" << name << std::endl;
	}

	// �t�@�C���̖����Ɉړ������݈ʒu�i���t�@�C���T�C�Y�j�𓾂�
	file.seekg(0L, std::ios::end);
	GLsizei length = static_cast<GLsizei>(file.tellg());

	buffer.resize(length + 1);    // �t�@�C���T�C�Y�̃����������

	// �t�@�C����擪����ǂݍ���
	file.seekg(0L, std::ios::beg);
	file.read(buffer.data(), length);
	buffer[length] = '\0';

	if (file.fail())
	{
		// �ǂݍ��߂Ȃ�����
		std::cerr << "could not read source file:" << name << std::endl;
		file.close();
		return false;
	}

	// �ǂݍ��߂�
	file.close();
	return true;
}

GLuint LoadProgram(const char* vert, const char* frag)
{
	// �V�F�[�_�̃\�[�X�t�@�C����ǂݍ���
	std::vector<GLchar> v_src;
	std::vector<GLchar> f_src;
	const bool v_stat(ReadShaderSource(vert, v_src));
	const bool f_stat(ReadShaderSource(frag, f_src));

	return v_stat && f_stat ? CreateProgram(v_src.data(), f_src.data()) : 0;
}

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

	// monitor: �t���X�N���[�����[�h�ɂ��郂�j�^���w��A�t���X�N���[�����[�h�łȂ����NULL���w�肷��
	// share: ����window�̃n���h�����w�肷��΁A���̃E�B���h�E�ƃe�N�X�`���Ȃǂ̃��\�[�X�����L���܂��BNULL���w�肷��΃��\�[�X�̋��L�͍s��Ȃ�
	GLFWwindow* const window(glfwCreateWindow(640, 480, "Hello", NULL, NULL));

	if (window == NULL) {
		std::cerr << "failed create GLFW window" << std::endl;
		return 0;
	}

	glfwMakeContextCurrent(window);		//�쐬�����E�B���h�E��OpenGL�̏����Ώۂɂ���

	glewExperimental = GL_TRUE;    //�v���b�g�t�H�[���ł̓T�|�[�g����Ă��Ȃ�OpenGL�̋@�\��L���ɂ��A�v���O��������Ăяo����悤�ɂ���
	if (glewInit() != GLEW_OK) {
		std::cerr << "failed to initialzie GLEW" << std::endl;
	}

	glfwSwapInterval(1);	//���������̃^�C�~���O��҂�
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);    //�E�B���h�E�̔w�i�F��ݒ�

	const GLuint program(LoadProgram("point.vert", "point.frag"));    // �v���O�����I�u�W�F�N�g���쐬

	std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));

	while (glfwWindowShouldClose(window) == GL_FALSE) {
		glClear(GL_COLOR_BUFFER_BIT);		// �E�B���h�E���폜����

		glUseProgram(program);	// �V�F�[�_�v���O�����̎g�p�J�n

		//�`�揈��
		shape->Draw();

		glfwSwapBuffers(window);	//�J���[�o�b�t�@�����ւ���
		glfwWaitEvents();		//�C�x���g�����o��
	}
	return 0;
}