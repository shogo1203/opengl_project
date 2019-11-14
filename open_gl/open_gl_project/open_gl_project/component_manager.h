#pragma once
#include "singleton.h"
#include <map>
#include "component.h"
#include <list>

class ComponentManager : public Singleton<ComponentManager>
{
public:
	void Initialize();
	void Update();
	void Finalize() override;
	void AddComponent(Component* component);

private:
	void RemoveComponent(std::string id);
	std::map<std::string, Component*> components_;
};
