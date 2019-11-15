#pragma once
#include "object.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"

class Transform : Object
{
public:
	Transform();
	Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	void Rotate(float x, float y, float z);
	void Rotate(glm::vec3 euler_angles);
	void SetRotation(float x, float y, float z);
	void SetRotation(glm::vec3 euler_angles);
	glm::vec3 eulerAngles() const;
	std::string ToString() const override;
	glm::quat GetRotation() const;

	glm::vec3 position_;
	glm::vec3 scale_;

private:
	glm::quat rotation_;
};

