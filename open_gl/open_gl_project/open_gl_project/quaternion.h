#pragma once
#include "quaternion.h"
#include "vector3.h"
#include <cmath>
#include "object.h"

class Quaternion : Object
{
public:
	static Quaternion Euler(float x, float y, float z);
	static Quaternion Identity();

	Quaternion();
	Quaternion(const Quaternion& quaternion);
	Quaternion(float x, float y, float z, float w);
	Vector3 Euler();

	float x_;
	float y_;
	float z_;
	float w_;
private:
};

