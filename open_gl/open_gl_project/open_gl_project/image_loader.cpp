#include "image_loader.h"

ImageData* ImageLoader::Load(const char* path)
{
	ImageData* image_data = new ImageData();

	// テクスチャの読み込み
	image_data->mat = cv::imread(path, cv::IMREAD_UNCHANGED);

	if (image_data->mat.empty())
	{
		std::cerr << "failed load to image" << std::endl;
		return nullptr;
	}
	return image_data;
}
