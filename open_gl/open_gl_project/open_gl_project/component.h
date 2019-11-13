#pragma once
#include "object.h"
#include <typeinfo>

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
	bool is_enable_;
	template <class T>
	static T* Create();
	Component();

protected:
	virtual ~Component();

private:
};


template<class T>
inline T* Component::Create()
{
	if (typeid(T) == typeid(Component)) {
		return nullptr;
	}

	T* instance = new T();

	return instance;
}
