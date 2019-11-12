#pragma once
#include "object.h"
#include "vector3.h"
#include "matrix.h"
#include "glm/glm.hpp"

class Transform : Object
{
public:
	Transform();
	Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	glm::vec3 position_;
	glm::vec3 scale_;
	glm::vec3 rotation_;

private:

};

