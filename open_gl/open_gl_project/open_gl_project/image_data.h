#pragma once
#include <glfw3.h>
#include <opencv2/opencv.hpp>

struct ImageData
{
	cv::Mat mat;

	float GetWidth() const;
	float GetHeight() const;
	GLuint id;
};

