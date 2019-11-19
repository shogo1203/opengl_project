#pragma once
#include <opencv2/opencv.hpp>
#include <glfw3.h>

struct ImageData
{
	cv::Mat mat;

	float GetWidth() const;
	float GetHeight() const;
	GLuint id;
};

