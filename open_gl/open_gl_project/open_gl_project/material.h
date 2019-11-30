#pragma once

#include "object.h"
#include "image_data.h"
#include "image_loader.h"

class Material : public Object
{
public:
	void CreateTexture(const char* path);
	void Finalize();
	ImageData* image_data_;
};

