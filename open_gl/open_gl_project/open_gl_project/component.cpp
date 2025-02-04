#include "component.h"
#include "component_manager.h"

void Component::Initialize()
{
}

void Component::Update()
{
}

void Component::Finalize()
{
	delete this;
}

void Component::OnEnable()
{
}

void Component::OnDisble()
{
}

void Component::FixedUpdate()
{
}

void Component::LateUpdate()
{
}

void Component::Awake()
{
}

void Component::Draw()
{
}

ComponentState Component::GetComponentState()
{
	return component_state_;
}

void Component::SetComponentState(ComponentState component_state)
{
	component_state_ = component_state;
}

void Component::Initialized()
{
	is_initialized_ = true;
}

bool Component::GetInitialized() const
{
	return is_initialized_;
}

void Component::Destroy()
{
	is_enable_ = false;
	is_destroy_ = true;
}

bool Component::GetDestroyed() const
{
	return is_destroy_;
}

void Component::AddComponent(Component* component)
{
	ComponentManager::GetInstance().AddComponent(component);
}

Component::~Component()
{
}
