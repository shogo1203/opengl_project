#pragma once
#include "singleton.h"
#include "scene.h"
#include "camera.h"

class SceneManager :
	public Singleton<SceneManager>
{
public:
	template <typename T>
	void LoadScene();
	void Initialize();
	void Update();
	void Finalize();
	Scene* GetCurrentScene()  const;

private:
	Scene* current_scene_;
};

template<typename T>
inline void SceneManager::LoadScene()
{
	if (current_scene_) {
		current_scene_->Finalize();
	}

	current_scene_ = new T();
	current_scene_->Initialize();
}
