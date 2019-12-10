#pragma once
#include "object.h"
#include <typeinfo>

class GameObject;

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
	static T* Create(bool is_enable = true, GameObject* parent = nullptr);
	GameObject* parent_;
	ComponentState GetComponentState();
	void SetComponentState(ComponentState component_state);
	void Initialized();
	bool GetInitialized() const;
	void Destroy();
	bool GetDestroyed() const;

protected:
	static void AddComponent(Component* component);
	Component();
	virtual ~Component();

private:
	ComponentState component_state_;
	bool is_initialized_;
	bool is_destroy_;
};

template<class T>
inline T* Component::Create(bool is_enable, GameObject* parent)
{
	T* t = Object::Create<T>();
	Component* c = dynamic_cast<Component*>(t);

	if (!c) {
		std::cerr << "failed create component" << std::endl;
		return nullptr;
	}

	c->is_enable_ = is_enable;
	c->parent_ = parent;
	c->component_state_ = ComponentState::None;
	c->is_initialized_ = false;
	c->is_destroy_ = false;

	AddComponent(t);
	return t;
}
