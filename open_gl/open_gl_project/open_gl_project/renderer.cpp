#include "renderer.h"

Renderer::Renderer(const char* fbx_path, const char* vertex_shader_path, const char* fragment_shader_path, Transform* transform)
{
	transform_ = transform;
	fbx_data_ = FbxLoader::Load(fbx_path);
	gl_renderer_ = new OpenGLRenderer(new Shape(fbx_data_), vertex_shader_path, fragment_shader_path);
	gl_renderer_->Initialize();
}

void Renderer::Draw() const
{
	gl_renderer_->Draw(transform_->position_, transform_->scale_, transform_->GetRotation());
}

void Renderer::Finalize()
{
	delete fbx_data_;
	delete gl_renderer_;
	delete this;
}
