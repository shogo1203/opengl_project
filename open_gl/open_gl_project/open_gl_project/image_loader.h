#pragma once
#include <glew.h>
#include <stdio.h>
#include <iostream>
#include "texture_asset.h"
#include <opencv2/opencv.hpp>

class ImageLoader
{
public:
	static TextureAsset* Load(const char* path);
private:
};