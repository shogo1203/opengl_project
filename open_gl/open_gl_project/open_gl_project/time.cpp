#include "time.h"

float Time::delta_time_;
float Time::time_;

void Time::Initialize()
{
	glfwSetTime(0);
	time_ = 0.0f;
	delta_time_ = 0.0f;
}

void Time::Update()
{
	float current_time = glfwGetTime();
	delta_time_ = current_time - time_;
	time_ = current_time;
}

float Time::GetDeltaTime()
{
	return delta_time_;
}

float Time::GetTime()
{
	return time_;
}
