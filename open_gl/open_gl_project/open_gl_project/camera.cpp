#include "camera.h"

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
	if (main_ == nullptr)
	{
		main_ = this;
	}
}

void Camera::Finalize()
{
}
