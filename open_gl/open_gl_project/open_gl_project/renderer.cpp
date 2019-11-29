#include "renderer.h"
#include "image_loader.h"
Renderer::Renderer(const char* fbx_path, const char* vertex_shader_path, const char* fragment_shader_path, Transform* transform)
{
	transform_ = transform;
	model_data_ = FbxLoader::Load(fbx_path);


	std::cout << model_data_->textures[0];
	model_data_->image_data_ = ImageLoader::Load(model_data_->textures[1].c_str());
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
