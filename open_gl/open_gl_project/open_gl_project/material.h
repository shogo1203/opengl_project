#pragma once

#include "object.h"
#include "texture_asset.h"
#include "image_loader.h"

class Material : public Object
{
public:
	void CreateTexture(const char* path);
	void Finalize();
	TextureAsset* image_data_;
};

