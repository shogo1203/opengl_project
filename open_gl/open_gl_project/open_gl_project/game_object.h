#pragma once
#include "transform.h"
#include "component.h"

class GameObject :public Component
{
public:
	Transform transform_;
	void AddComponent(const Component* component);
	void Remove(const Component* component);
	template <typename T>
	T GetComponent();
private:
	std::vector<Component*> components_;
};

template<typename T>
inline T GameObject::GetComponent()
{
	return T();
}
