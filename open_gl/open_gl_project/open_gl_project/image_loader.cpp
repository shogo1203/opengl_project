#include "image_loader.h"

ImageData* ImageLoader::Load(const char* path)
{
	ImageData image_data;

	// テクスチャの読み込み
	image_data.mat = cv::imread(path);

	if (image_data.mat.empty())
	{
		std::cerr << "failed load to image" << std::endl;
		return nullptr;
	}

	cv::flip(image_data.mat, image_data.mat, 0);
	cv::cvtColor(image_data.mat, image_data.mat, cv::COLOR_BGR2RGB);

	// opengl gpuに転送する
	glGenTextures(1, &image_data.id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, image_data.id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_data.GetWidth(), image_data.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image_data.mat.ptr());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	return &image_data;
}
