#pragma once
#include <stdio.h>
#include <iostream>
#include "image_data.h"
#include <opencv2/opencv.hpp>

class ImageLoader
{
public:
	static ImageData* Load(const char* path);
private:
};

