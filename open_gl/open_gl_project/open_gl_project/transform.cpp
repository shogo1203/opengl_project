#include "transform.h"

Transform::Transform() :
	Transform(Vector3(), Vector3(1, 1, 1), Vector3())
{

}

Transform::Transform(Vector3 position, Vector3 scale, Vector3 rotation) :
	position_(position),
	scale_(scale),
	rotation_(rotation)
{

}

void Transform::Rotate(float angle, float x, float y, float z)
{
	if (angle < 0) {
		return;
	}
}

