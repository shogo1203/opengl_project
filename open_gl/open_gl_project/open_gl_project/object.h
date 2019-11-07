#pragma once
#include <string>
class Object
{
public:
	template <typename T, typename T1>
	static bool Equals(const T* t, const T1* t1);
	virtual std::string ToString() const;
};

template<typename T, typename T1>
inline bool Object::Equals(const T* t, const T1* t1)
{
	return t == t1;
}
