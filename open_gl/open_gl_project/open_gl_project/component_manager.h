#pragma once
#include "singleton.h"
#include <map>
#include <list>
#include "time.h"
#include "component.h"

class ComponentManager : public Singleton<ComponentManager>
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize() override;
	void AddComponent(Component* component);

private:
	void RemoveComponent(std::string id);
	std::map<std::string, Component*> components_;
};
