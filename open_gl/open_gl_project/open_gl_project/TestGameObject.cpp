#include "TestGameObject.h"

void TestGameObject::Update()
{
	transform_.Rotate(0, 1, 0);
}

void TestGameObject::Initialize()
{
	MeshRenderer* mesh = Component::Create<MeshRenderer>(true, this);
	mesh->fbx_path_ = "cube.fbx";
	mesh->vertex_shader_path_ = "point.vert";
	mesh->fragment_shader_path_ = "point.frag";
}
