#pragma once
#include <opencv2/opencv.hpp>

struct ImageData
{
	cv::Mat image;

	float GetWidth() const;
	float GetHeight() const;
};

