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
	glm::vec3 position_;
	glm::vec3 scale_;
	glm::quat rotation_;
	std::string ToString() const override;

private:

};

