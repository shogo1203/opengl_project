#pragma once
#include "transform.h"
#include "window.h"

class Camera : public Transform
{
public:
	static Camera* main_;

	Camera(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float near, float far, float fovy, float visibility);
	Camera();
	~Camera();
	glm::mat4 Projection();    // 透視投影行列
	glm::mat4 LookAt();    // ビュー変換行列

	float near_;
	float far_;
	float fovy_;
	float visibility_;
	Window* window_;
};

