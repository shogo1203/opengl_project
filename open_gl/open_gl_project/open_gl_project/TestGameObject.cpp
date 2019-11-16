#include "TestGameObject.h"
float a = 0.08f;
void TestGameObject::Update()
{
	transform_.Rotate(0, 0.001f, 0);
	transform_.scale_ = glm::vec3(a, a, a);
}

void TestGameObject::Initialize()
{
	transform_.SetRotation(-90, 0, 0);
	MeshRenderer* mesh = Component::Create<MeshRenderer>(true, this);
	mesh->fbx_path_ = "dragon.fbx";
	mesh->vertex_shader_path_ = "point.vert";
	mesh->fragment_shader_path_ = "point.frag";
}
