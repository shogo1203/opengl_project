#include "quaternion.h"

Quaternion Quaternion::Euler(float x, float y, float z)
{
	return Quaternion::Identity();
}

Quaternion Quaternion::Identity()
{
	return Quaternion(0, 0, 0, 1);
}

Quaternion::Quaternion()
{
	Quaternion::Identity();
}

Quaternion::Quaternion(const Quaternion& quaternion) :
	x_(quaternion.x_),
	y_(quaternion.y_),
	z_(quaternion.z_),
	w_(quaternion.w_)
{
}

Quaternion::Quaternion(float x, float y, float z, float w) :
	x_(x),
	y_(y),
	z_(z),
	w_(w)
{
}

Vector3 Quaternion::Euler()
{
	Vector3 euler;

	float x = x_ * x_;
	float xy = x_ * y_;
	float xz = x_ * z_;
	float xw = x * w_;
	float y = y_ * y_;
	float yz = y_ * z_;
	float yw = y_ * w_;
	float z = z_ * z_;
	float  zw = z_ * w_;
	float w = w_ * w_;

	euler.x_ = std::atan2f(2.0f * (zw + xy), x - y - z + w);
	euler.y_ = std::asinf(2.0f * (xz - yw));
	euler.z_ = std::atan2f(2.0f * (yz + xw), x + y - z - w);

	return euler;
}
