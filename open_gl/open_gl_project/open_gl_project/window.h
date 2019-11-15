#pragma once
#include <iostream>
#include <glew.h>
#include <glfw3.h>

class Window
{
public:
	static void Resize(GLFWwindow* const window, int width, int height);
	static void Wheel(GLFWwindow* const window, double x, double y);
	static void Keyboard(GLFWwindow* const window, int key, int scancode, int action, int mods);

	Window(int width = 640, int height = 480, const char* title = "title");
	virtual ~Window();
	bool IsOpenWindow();    // 描画ループ継続判定
	void SwapBuffers() const;    // ダブルバッファリング
	const GLfloat* GetSize() const;
	const GLfloat GetScale() const;
	const GLfloat* GetLocation() const;
	const int IsDownKey(int key) const;
	const float GetAspect() const;

private:
	GLFWwindow* const window_;    // ウィンドウのハンドル
	GLfloat size_[2];
	GLfloat scale_;
	GLfloat location_[2];
	int key_status_;    // キーボードの状態
};

