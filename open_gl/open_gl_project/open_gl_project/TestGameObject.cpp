#include "TestGameObject.h"
float a = 1.0f;
void TestGameObject::Update()
{
	transform_.Rotate(0, 0.01f, 0);
	transform_.scale_ = glm::vec3(a, a, a);
}

void TestGameObject::Initialize()
{
	MeshRenderer* mesh = Component::Create<MeshRenderer>(true, this);
	mesh->fbx_path_ = "cube.fbx";
	mesh->vertex_shader_path_ = "point.vert";
	mesh->fragment_shader_path_ = "point.frag";
}
