#pragma once
#include "transform.h"
#include "window.h"
#include "game_object.h"

class Camera : public GameObject
{
public:
	static inline Camera* main_ = nullptr;
	static Camera* Create();

	glm::mat4 Projection();    // �������e�s��
	glm::mat4 LookAt();    // �r���[�ϊ��s��
	void Initialize() override;
	void Finalize() override;

	float near_;
	float far_;
	float fovy_;
	float visibility_;
	Window* window_;
private:
};

