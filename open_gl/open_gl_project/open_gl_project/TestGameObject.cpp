#include "TestGameObject.h"

void TestGameObject::Update()
{
	transform_.Rotate(0, 0.01f, 0);
}

void TestGameObject::Initialize()
{
	transform_.scale_ = glm::vec3(0.5f, 0.5f, 0.5f);
	OpenGLRenderer* mesh = Component::Create<OpenGLRenderer>(true, this);
	mesh->SetTransform(&transform_);
	mesh->LoadModel("cube.fbx");
	mesh->LoadShader("point.vert", "point.frag");
}
