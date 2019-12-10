#include "texture_asset.h"

float TextureAsset::GetWidth() const
{
	return mat.cols;
}

float TextureAsset::GetHeight() const
{
	return mat.rows;
}
