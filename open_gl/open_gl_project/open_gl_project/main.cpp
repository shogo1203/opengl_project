#include <cstdlib>
#include <iostream>
#include <glew.h>
#include <glfw3.h>

// vsrc: �o�[�e�b�N�X�V�F�[�_�̃\�[�X�v���O�����̕�����
// fsrc: �t���O�����g�V�F�[�_�̃\�[�X�v���O�����̕�����
GLuint createProgram(const char* v_src, const char* f_src) {
	const GLuint program(glCreateProgram());		// ��̃v���O�����I�u�W�F�N�g���쐬����

	if (v_src != NULL) {
		// �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
		const GLuint v_obj(glCreateShader(GL_VERTEX_SHADER));  
		glShaderSource(v_obj, 1, &v_src, NULL);
		glCompileShader(v_obj);

		// �o�[�e�b�N�X�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
		glAttachShader(program, v_obj);
		glDeleteShader(v_obj);
	}

	if (f_src != NULL) {
		// �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���쐬����
		const GLuint f_obj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(f_obj, 1, &f_src, NULL);
		glCompileShader(f_obj);

		// �t���O�����g�V�F�[�_�̃V�F�[�_�I�u�W�F�N�g���v���O�����I�u�W�F�N�g�ɑg�ݍ���
		glAttachShader(program, f_obj);
		glDeleteShader(f_obj);
	}
}

int main() {

	//GLFW������������
	if (glfwInit() == GL_FALSE) {
		std::cerr << "failed initialize GLFW" << std::endl;
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
		std::cerr << "failed initialzie GLEW" << std::endl;
	}

	glfwSwapInterval(1);	//���������̃^�C�~���O��҂�
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);    //�E�B���h�E�̔w�i�F��ݒ�

	while (glfwWindowShouldClose(window) == GL_FALSE) {
		glClear(GL_COLOR_BUFFER_BIT);		// �E�B���h�E���폜����

		//�`�揈��

		glfwSwapBuffers(window);	//�J���[�o�b�t�@�����ւ���
		glfwWaitEvents();		//�C�x���g�����o��
	}
	return 0;
}