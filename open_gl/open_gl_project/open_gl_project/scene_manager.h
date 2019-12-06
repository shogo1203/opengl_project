#pragma once
#include "singleton.h"
#include "scene.h"

class SceneManager :
	public Singleton<SceneManager>
{
public:
	template <typename T>
	void LoadScene();
	void Initialize();
	void Update();
	void Finalize();

private:
	Scene* current_scene_;
};

template<typename T>
inline void SceneManager::LoadScene()
{
	current_scene_ = new T();
}
