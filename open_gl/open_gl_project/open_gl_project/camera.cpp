#include "camera.h"

Camera* Camera::main_ = nullptr;

Camera::Camera(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, float near, float far, float fovy) :
	Transform(position, scale, rotation),
	near_(near),
	far_(far),
	fovy_(fovy)
{
	window_ = nullptr;
	if (main_ == nullptr)
	{
		main_ = this;
	}
}

Camera::Camera() :
	Transform(),
	near_(1),
	far_(10),
	fovy_(0.3)
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
	const GLfloat* const size(window_->GetSize());
	const GLfloat fovy(window_->GetScale() * fovy_);
	const GLfloat aspect(size[0] / size[1]);

	return glm::perspective(fovy, aspect, near_, far_);
}
