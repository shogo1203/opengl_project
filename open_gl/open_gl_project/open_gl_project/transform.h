#pragma once
#include "object.h"
#include "vector3.h"
#include "matrix.h"

class Transform : Object
{
public:
	Transform();
	Transform(Vector3 position, Vector3 scale, Vector3 rotation);
	Vector3 scale_;
	Vector3 position_;
	Vector3 rotation_;
	void Rotate(float angle, float x, float y, float z);
	void Rotate(float angle, Vector3& axis);

private:
	Matrix matrix_;
};

