#pragma once
#include <glew.h>
#include <glfw3.h>

class Time
{
public:
	static void Initialize();
	static void Update();
	static float GetDeltaTime();
	static float GetTime();
private:
	static float delta_time_;
	static float time_;
};

