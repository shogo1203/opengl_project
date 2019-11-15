#include "component_manager.h"

void ComponentManager::Initialize()
{
	components_.clear();
	Time::Initialize();
}

void ComponentManager::Update()
{
	Time::Update();

	std::list<Component*> enable_components, awake_components, initialize_components, disable_components, finalize_components;

	for (auto&& [key, value] : components_) {
		if (value->GetComponentState() == ComponentState::None)
		{
			enable_components.push_back(value);
		}
	}

	for (auto&& value : enable_components)
	{
		value->OnEnable();
		value->SetComponentState(ComponentState::Enable);
		if (!value->GetInitialized())
		{
			awake_components.push_back(value);
		}
	}

	for (auto&& value : awake_components)
	{
		value->Awake();
		value->SetComponentState(ComponentState::Awake);
		initialize_components.push_back(value);
	}

	for (auto&& value : initialize_components)
	{
		value->Initialize();
		value->Initialized();
		value->SetComponentState(ComponentState::Initialize);
	}

	for (auto&& [key, value] : components_)
	{
		if (value->is_enable_)
		{
			value->Update();
		}
		else
		{
			disable_components.push_back(value);
		}
	}

	for (auto&& value : disable_components)
	{
		value->OnDisble();
		if (value->GetDestroyed())
		{
			finalize_components.push_back(value);
		}
		else
		{
			value->SetComponentState(ComponentState::None);
		}
	}

	for (auto&& value : finalize_components)
	{
		value->Finalize();
		RemoveComponent(value->GetInstanceId());
	}
}

void ComponentManager::Draw()
{
	for (auto&& [key, value] : components_)
	{
		if (value->is_enable_)
		{
			value->Draw();
		}
	}
}

void ComponentManager::Finalize()
{
	Singleton::Finalize();
}

void ComponentManager::AddComponent(Component* component)
{
	components_[component->GetInstanceId()] = component;
}

void ComponentManager::RemoveComponent(std::string id)
{
	components_.erase(id);
}
