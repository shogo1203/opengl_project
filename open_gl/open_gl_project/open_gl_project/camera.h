#pragma once
#include "transform.h"
#include "window.h"
#include "glm/ext.hpp"

class Camera : public Transform
{
public:
	static Camera* main_;

	Camera(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float near, float far, float fovy);
	Camera();
	~Camera();
	glm::mat4 Projection();

	float near_;
	float far_;
	float fovy_;
	Window* window_;
};

