#pragma once
#include "singleton.h"
#include <list>
#include "component.h"

class ComponentManager : public Singleton<ComponentManager>
{
public:
	void Initialize();
	void Update();
	void Finalize() override;
	template <class T>
	void AddComponent(const T* component);

private:
	std::list<Component*> component_list_;
};

template<class T>
inline void ComponentManager::AddComponent(const T* component)
{
}
