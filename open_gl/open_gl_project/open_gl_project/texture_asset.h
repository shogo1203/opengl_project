#pragma once
#include <glew.h>;
#include <opencv2/opencv.hpp>

struct TextureAsset
{
	cv::Mat mat;    // Mat�̓X�}�[�g�|�C���^

	float GetWidth() const;
	float GetHeight() const;
};

