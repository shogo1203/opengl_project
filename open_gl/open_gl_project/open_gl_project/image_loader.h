#pragma once
#include "png.h"
#include <stdio.h>
#include <iostream>
#include "image_data.h"

class ImageLoader
{
public:
	static ImageData* Load(const char* path);
private:
};

