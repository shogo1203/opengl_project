#pragma once
#include "object.h"

template<class T>
class Singleton :
	public Object
{
public:
	static T& GetInstance();
	virtual void Finalize();
private:
	static inline T* instance_ = nullptr;

	Singleton(const Singleton<T>&) = delete;
	Singleton<T>& operator =(const Singleton<T>&) = delete;
};

template<class T>
inline T& Singleton<T>::GetInstance()
{
	if (instance_ == nullptr) {
		instance_ = Object::Create<T>();
	}

	return *instance_;
}

template<class T>
inline void Singleton<T>::Finalize()
{
	delete instance_;
}
