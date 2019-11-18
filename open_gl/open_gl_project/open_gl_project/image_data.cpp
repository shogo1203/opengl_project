#include "image_data.h"

float ImageData::GetWidth() const
{
	return image.rows;
}

float ImageData::GetHeight() const
{
	return image.cols;
}
