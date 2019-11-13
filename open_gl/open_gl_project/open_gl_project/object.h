#pragma once
#include <string>
#include <iostream>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

class Object
{
public:
	template <typename T, typename T1>
	static bool Equals(const T* t, const T1* t1);
	virtual std::string ToString() const;
	Object();

private:
	std::string instance_id_;
};

template<typename T, typename T1>
inline bool Object::Equals(const T* t, const T1* t1)
{
	return t == t1;
}
