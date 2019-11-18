#include "image_loader.h"

ImageData* ImageLoader::Load(const char* path)
{
	ImageData image_data;
	image_data.image = cv::imread(path);

	if (image_data.image.empty())
	{
		std::cerr << "failed load to image" << std::endl;
		return nullptr;
	}

	cv::flip(image_data.image, image_data.image, 0);
	cv::cvtColor(image_data.image, image_data.image, cv::COLOR_BGR2RGB);

	return &image_data;
}
