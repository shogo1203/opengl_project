#include "transform.h"

Transform::Transform() :
	Transform(glm::vec3(), glm::vec3(5, 5, 5), glm::vec3(0))
{

}

Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation) :
	position_(position),
	scale_(scale),
	rotation_(rotation)
{

}

void Transform::Rotate(float x, float y, float z)
{
	rotation_ += glm::quat(glm::vec3(x, y, z));
}

void Transform::Rotate(glm::vec3 euler_angles)
{
	Rotate(euler_angles.x, euler_angles.y, euler_angles.z);
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation_ = glm::quat(glm::vec3(x, y, z));
}

void Transform::SetRotation(glm::vec3 euler_angles)
{
	SetRotation(euler_angles.x, euler_angles.y, euler_angles.z);
}

glm::vec3 Transform::eulerAngles() const
{
	return glm::eulerAngles(rotation_);
}

std::string Transform::ToString() const
{
	return "position(" + std::to_string(position_.x) + "," + std::to_string(position_.y) + "," + std::to_string(position_.z) + ")\nscale(" +
		std::to_string(scale_.x) + "," + std::to_string(scale_.y) + "," + std::to_string(scale_.z) + ")\nrotation(" +
		std::to_string(rotation_.x) + "," + std::to_string(rotation_.y) + "," + std::to_string(rotation_.z) + ")";
}

glm::quat Transform::GetRotation() const
{
	return rotation_;
}
