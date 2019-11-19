#include "image_data.h"

float ImageData::GetWidth() const
{
	return mat.rows;
}

float ImageData::GetHeight() const
{
	return mat.cols;
}
