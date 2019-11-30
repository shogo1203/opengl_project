#include "renderer.h"

Renderer::Renderer(const char* fbx_path, const char* vertex_shader_path, const char* fragment_shader_path, Transform* transform)
{
	transform_ = transform;
	model_data_ = FbxLoader::Load(fbx_path);

	for (auto&& name : model_data_->textures_) {
		model_data_->materials_.push_back(Material::CreateMaterial(name.c_str()));
	}

	model_data_->LoadTexture();
	gl_renderer_ = new OpenGLRenderer(vertex_shader_path, fragment_shader_path, model_data_);
	gl_renderer_->Initialize();
}

void Renderer::Draw() const
{
	gl_renderer_->Draw(transform_->position_, transform_->scale_, transform_->GetRotation());
}

void Renderer::Finalize()
{
	delete model_data_;
	gl_renderer_->Finalize();
	delete this;
}
