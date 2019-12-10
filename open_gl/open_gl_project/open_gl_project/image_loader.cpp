#include "image_loader.h"

TextureAsset* ImageLoader::Load(const char* path)
{
	TextureAsset* image_data = new TextureAsset();

	// �e�N�X�`���̓ǂݍ���
	image_data->mat = cv::imread(path, cv::IMREAD_UNCHANGED);

	if (image_data->mat.empty())
	{
		std::cerr << "failed load to image" << std::endl;
		return nullptr;
	}
	return image_data;
}
