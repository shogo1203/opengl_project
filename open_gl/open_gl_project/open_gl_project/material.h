#pragma once

#include "object.h"
#include "image_data.h"
#include "image_loader.h"

class Material : public Object
{
public:
	ImageData* image_data_;

	static Material* CreateMaterial(const char* texture_path);
};

