#include "material.h"

Material* Material::CreateMaterial(const char* texture_path)
{
	Material* material = new Material();

	if (texture_path) {
		material->image_data_ = ImageLoader::Load(texture_path);
	}

	return material;
}
