#pragma once
#include "component.h"
#include "renderer.h"

class MeshRenderer :
	public Component
{
public:
	void Initialize() override;
	void Draw() override;
	void Finalize() override;

	const char* fbx_path_;
	const char* vertex_shader_path_;
	const char* fragment_shader_path_;

private:
	Renderer* renderer_;
};

