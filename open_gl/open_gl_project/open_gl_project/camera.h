#pragma once
#include "transform.h"
#include "window.h"
#include "game_object.h"

class Camera : public GameObject
{
public:
	static inline Camera* main_ = nullptr;
	static Camera* Create();

	glm::mat4 Projection();    // 透視投影行列
	glm::mat4 LookAt();    // ビュー変換行列
	void Initialize() override;
	void Finalize() override;

	float near_;
	float far_;
	float fovy_;
	float visibility_;
	Window* window_;
private:
};

