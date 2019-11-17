#include "TestGameObject.h"

void TestGameObject::Update()
{
	transform_.Rotate(0, 0.01f, 0);
}

void TestGameObject::Initialize()
{
	transform_.scale_ = glm::vec3(0.1f, 0.1f, 0.1f);
	MeshRenderer* mesh = Component::Create<MeshRenderer>(true, this);
	mesh->fbx_path_ = "Sadface.fbx";
	mesh->vertex_shader_path_ = "point.vert";
	mesh->fragment_shader_path_ = "point.frag";

	ImageLoader::Load("image.png");
}
