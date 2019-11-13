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

std::string Transform::ToString() const
{
	return "position(" + std::to_string(position_.x) + "," + std::to_string(position_.y) + "," + std::to_string(position_.z) + ")\nscale(" +
		std::to_string(scale_.x) + "," + std::to_string(scale_.y) + "," + std::to_string(scale_.z) + ")\nrotation(" +
		std::to_string(rotation_.x) + "," + std::to_string(rotation_.y) + "," + std::to_string(rotation_.z) + ")";
}
