#pragma once
#include "object.h"
#include <typeinfo>

enum class ComponentState
{
	None,
	Enable,
	Awake,
	Initialize,
	Update,
	Disable,
	Finalize,
};

class Component : public Object
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Finalize();
	virtual void OnEnable();
	virtual void OnDisble();
	virtual void FixedUpdate();
	virtual void LateUpdate();
	virtual void Awake();
	virtual void Draw();
	bool is_enable_;
	template <class T>
	static T* Create(bool is_enable = true, Component* parent = nullptr);
	Component();
	Component* parent_;
	ComponentState GetComponentState();
	void SetComponentState(ComponentState component_state);
	void Initialized();
	bool GetInitialized() const;
	void Destroy();
	bool GetDestroyed() const;

protected:
	virtual ~Component();

private:
	ComponentState component_state_;
	bool is_initialized_;
	bool is_destroy_;
};

template<class T>
inline T* Component::Create(bool is_enable, Component* parent)
{
	if (typeid(T) == typeid(Component)) {
		return nullptr;
	}

	T* instance = new T();

	if (parent) {
		instance->parent_ = parent;
	}
	instance->is_enable_ = is_enable;

	ComponentManager::GetInstance().AddComponent(instance);
	return instance;
}
