#include "window.h"

Window::Window(int width, int height, const char* title) :
	// monitor: �t���X�N���[�����[�h�ɂ��郂�j�^���w��A�t���X�N���[�����[�h�łȂ����NULL���w�肷��
	// share: ����window�̃n���h�����w�肷��΁A���̃E�B���h�E�ƃe�N�X�`���Ȃǂ̃��\�[�X�����L���܂��BNULL���w�肷��΃��\�[�X�̋��L�͍s��Ȃ�
	window_(glfwCreateWindow(width, height, title, NULL, NULL)),
	scale_(100.0f),
	location_{ 0.0f, 0.0f },
	key_status_(GLFW_RELEASE)
{
	if (window_ == nullptr)
	{
		std::cerr << "failed to create GLFW window" << std::endl;
		exit(1);
	}

	glfwMakeContextCurrent(window_);    // ���݂̃E�B���h�E�������Ώۂɂ���
	glewExperimental = GL_TRUE;    // GLEW������������

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "failed to initialize GLEW" << std::endl;
		exit(1);
	}

	glfwSwapInterval(1);    // ���������̃^�C�~���O��҂�
	glfwSetWindowUserPointer(window_, this);    // �C���X�^���X��this�|�C���^���L�^���Ă���
	glfwSetWindowSizeCallback(window_, Resize);    // �E�B���h�E�̃T�C�Y�ύX���ɌĂяo�������̓o�^
	glfwSetScrollCallback(window_, Wheel);
	glfwSetKeyCallback(window_, Keyboard);

	Resize(window_, width, height);    // �J�����E�B���h�E�̏����ݒ�

	//	�J�����O�ݒ�
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	// �f�v�X�o�b�t�@�̐ݒ�
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 640, 480);    // �r���[�|�[�g��ݒ肷��
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);    //�E�B���h�E�̔w�i�F��ݒ�
}

Window::~Window()
{
	glfwDestroyWindow(window_);
}

bool Window::IsOpenWindow()
{
	//if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)
	//{
	//	// �}�E�X�J�[�\���̈ʒu���擾����
	//	double x, y;
	//	glfwGetCursorPos(window_, &x, &y);

	//	// �}�E�X�J�[�\���̐��K���f�o�C�X���W�n��ł̈ʒu�����߂�
	//	location_[0] = static_cast<GLfloat>(x) * 2.0f / size_[0] - 1.0f;
	//	location_[1] = 1.0f - static_cast<GLfloat>(y) * 2.0f / size_[1];
	//}

	//const float speed = 100.0f;

	//if (IsDownKey(GLFW_KEY_LEFT) != GLFW_RELEASE)
	//{
	//	location_[0] -= speed / size_[0];
	//}
	//else if (IsDownKey(GLFW_KEY_RIGHT) != GLFW_RELEASE)
	//{
	//	location_[0] += speed / size_[0];
	//}
	//else if (IsDownKey(GLFW_KEY_DOWN) != GLFW_RELEASE)
	//{
	//	location_[1] -= speed / size_[1];
	//}
	//else if (IsDownKey(GLFW_KEY_UP) != GLFW_RELEASE)
	//{
	//	location_[1] += speed / size_[1];
	//}
	return !glfwWindowShouldClose(window_) && !IsDownKey(GLFW_KEY_ESCAPE);
}

void Window::SwapBuffers() const
{
	glfwSwapBuffers(window_);
}

void Window::Resize(GLFWwindow* const window, int width, int height)
{
	// �t���[���o�b�t�@�̃T�C�Y�𒲂ׂ�
	int frame_buffer_width, frame_buffer_height;
	glfwGetFramebufferSize(window, &frame_buffer_width, &frame_buffer_height);

	glViewport(0, 0, frame_buffer_width, frame_buffer_height);    // �t���[���o�b�t�@�S�̂̃r���[�|�[�g�ɐݒ肷��

	Window* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));    // �o�^���Ă���Window�̃|�C���^�𓾂�

	if (instance != nullptr)
	{
		instance->size_[0] = static_cast<GLfloat>(width);
		instance->size_[1] = static_cast<GLfloat>(height);
	}
}

void Window::Wheel(GLFWwindow* const window, double x, double y)
{
	Window* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

	if (instance != nullptr)
	{
		instance->scale_ += static_cast<GLfloat>(y);
	}
}

void Window::Keyboard(GLFWwindow* const window, int key, int scancode, int action, int mods)
{
	Window* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));

	if (instance != nullptr)
	{
		instance->key_status_ = action;
	}
}

const GLfloat* Window::GetSize() const
{
	return size_;
}

const GLfloat Window::GetScale() const
{
	return scale_;
}

const GLfloat* Window::GetLocation() const
{
	return location_;
}

const int Window::IsDownKey(int key) const
{
	return glfwGetKey(window_, key);
}

const float Window::GetAspect() const
{
	return size_[0] / size_[1];
}
