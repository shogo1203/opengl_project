#include "camera.h"

Camera* Camera::main_ = nullptr;

Camera::Camera(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float near, float far, float fovy, float visibility) :
	Transform(position, scale, rotation),
	near_(near),
	far_(far),
	fovy_(fovy),
	visibility_(visibility)
{
	window_ = nullptr;
	if (main_ == nullptr)
	{
		main_ = this;
	}
}

Camera::Camera() :
	Transform(),
	near_(0.001f),
	far_(100.0f),
	fovy_(0.01f),
	visibility_(glm::radians(45.0f))
{
	window_ = nullptr;
	if (main_ == nullptr) {
		main_ = this;
	}
}

Camera::~Camera()
{

}

glm::mat4 Camera::Projection()
{
	return glm::perspective(visibility_, window_->GetAspect(), near_, far_);
}

glm::mat4 Camera::LookAt()
{
	return glm::lookAt(position_, glm::vec3(), glm::vec3(0, 1, 0));
}
