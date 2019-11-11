#include "transform.h"

Transform::Transform() :
	Transform(glm::vec3(), glm::vec3(1, 1, 1), glm::vec3())
{
}

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) :
	position_(position),
	scale_(scale),
	rotation_(rotation)
{

}

glm::vec3 Transform::GetPosition() const
{
	return position_;
}

glm::vec3 Transform::GetScale() const
{
	return scale_;
}

glm::vec3 Transform::GetRotation() const
{
	return rotation_;
}
