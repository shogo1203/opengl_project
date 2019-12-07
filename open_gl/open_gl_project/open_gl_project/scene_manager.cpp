#include "scene_manager.h"

void SceneManager::Initialize()
{
	current_scene_ = nullptr;

	// ƒJƒƒ‰‚Ìİ’è
	Camera::Create();
	Camera::main_->transform_.position_ = glm::vec3(4.0f, 5.0f, 15.0f);
	Camera::main_->transform_.Rotate(0, 180, 0);
}

void SceneManager::Update()
{
	if (current_scene_) {
		current_scene_->Update();
	}
}

void SceneManager::Finalize()
{
	current_scene_->Finalize();
}

Scene* SceneManager::GetCurrentScene() const
{
	return current_scene_;
}
