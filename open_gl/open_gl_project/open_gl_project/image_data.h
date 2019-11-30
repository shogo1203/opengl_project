#pragma once
#include <glew.h>;
#include <opencv2/opencv.hpp>

struct ImageData
{
	cv::Mat mat;    // Matはスマートポインタ

	float GetWidth() const;
	float GetHeight() const;
};

