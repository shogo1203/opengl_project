#include "camera.h"

Camera* Camera::Create()
{
	Camera* camera = Component::Create<Camera>();
	if (main_ == nullptr)
	{
		std::cout << 222;
		main_ = camera;
	}
	return camera;
}

glm::mat4 Camera::Projection()
{
	return glm::perspective(visibility_, window_->GetAspect(), near_, far_);
}

glm::mat4 Camera::LookAt()
{
	return glm::lookAt(transform_.position_, glm::vec3(), glm::vec3(0, 1, 0));
}

void Camera::Initialize()
{
	near_ = 0.001f;
	far_ = 100.0f;
	fovy_ = 0.01f;
	visibility_ = glm::radians(45.0f);
}

void Camera::Finalize()
{
	if (Camera::main_ == this) {
		Camera::main_ = nullptr;
	}

	Component::Finalize();
}
