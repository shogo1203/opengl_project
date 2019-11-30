#include "material.h"

void Material::CreateTexture(const char* path)
{
	image_data_ = ImageLoader::Load(path);
}

void Material::Finalize()
{
	delete image_data_;
	delete this;
}
