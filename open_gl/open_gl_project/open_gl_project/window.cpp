#include "window.h"

Window::Window(int width, int height, const char* title) :
	// monitor: フルスクリーンモードにするモニタを指定、フルスクリーンモードでなければNULLを指定する
	// share: 他のwindowのハンドルを指定すれば、そのウィンドウとテクスチャなどのリソースを共有します。NULLを指定すればリソースの共有は行わない
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

	glfwMakeContextCurrent(window_);    // 現在のウィンドウを処理対象にする
	glewExperimental = GL_TRUE;    // GLEWを初期化する

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "failed to initialize GLEW" << std::endl;
		exit(1);
	}

	glfwSwapInterval(1);    // 垂直同期のタイミングを待つ
	glfwSetWindowUserPointer(window_, this);    // インスタンスのthisポインタを記録しておく
	glfwSetWindowSizeCallback(window_, Resize);    // ウィンドウのサイズ変更時に呼び出す処理の登録
	glfwSetScrollCallback(window_, Wheel);
	glfwSetKeyCallback(window_, Keyboard);

	Resize(window_, width, height);    // 開いたウィンドウの初期設定

	//	カリング設定
	//glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);

	// デプスバッファの設定
	glClearDepth(1.0f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, 640, 480);    // ビューポートを設定する
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);    //ウィンドウの背景色を設定
}

Window::~Window()
{
	glfwDestroyWindow(window_);
}

bool Window::IsOpenWindow()
{
	//if (glfwGetMouseButton(window_, GLFW_MOUSE_BUTTON_1) != GLFW_RELEASE)
	//{
	//	// マウスカーソルの位置を取得する
	//	double x, y;
	//	glfwGetCursorPos(window_, &x, &y);

	//	// マウスカーソルの正規化デバイス座標系上での位置を求める
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
	// フレームバッファのサイズを調べる
	int frame_buffer_width, frame_buffer_height;
	glfwGetFramebufferSize(window, &frame_buffer_width, &frame_buffer_height);

	glViewport(0, 0, frame_buffer_width, frame_buffer_height);    // フレームバッファ全体のビューポートに設定する

	Window* const instance(static_cast<Window*>(glfwGetWindowUserPointer(window)));    // 登録してあるWindowのポインタを得る

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
