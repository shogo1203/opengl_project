#include "mesh_renderer.h"

void MeshRenderer::Initialize()
{
	renderer = new Renderer(fbx_path_, vertex_shader_path_, fragment_shader_path_, &parent_->transform_);
}

void MeshRenderer::Draw()
{
	renderer->Draw();
}

void MeshRenderer::Finalize()
{
	renderer->Finalize();
}
