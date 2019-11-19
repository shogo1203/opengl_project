#include "image_data.h"

float ImageData::GetWidth() const
{
	return mat.cols;
}

float ImageData::GetHeight() const
{
	return mat.rows;
}
