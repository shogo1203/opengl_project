#include "image_loader.h"

ImageData* ImageLoader::Load(const char* path)
{
	ImageData image_data;

	// �e�N�X�`���̓ǂݍ���
	image_data.mat = cv::imread(path, cv::IMREAD_UNCHANGED);

	if (image_data.mat.empty())
	{
		std::cerr << "failed load to image" << std::endl;
		return nullptr;
	}

	cv::flip(image_data.mat, image_data.mat, 0);
	cv::cvtColor(image_data.mat, image_data.mat, cv::COLOR_RGB2BGR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glGenTextures(1, &image_data.id);    // �e�N�X�`���쐬
	glBindTexture(GL_TEXTURE_2D, image_data.id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, image_data.mat.step / image_data.mat.elemSize());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_data.GetWidth(), image_data.GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image_data.mat.ptr());    // �e�N�X�`���Ƀf�[�^��R����

	return &image_data;
}
