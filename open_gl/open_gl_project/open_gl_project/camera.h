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
	glm::mat4 Projection();    // �������e�s��
	glm::mat4 LookAt();    // �r���[�ϊ��s��

	float near_;
	float far_;
	float fovy_;
	float visibility_;
	Window* window_;
};

