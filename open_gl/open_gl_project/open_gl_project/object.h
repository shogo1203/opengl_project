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
	template <class T>
	static T Create();
	virtual std::string ToString() const;
	std::string GetInstanceId() const;

private:
	Object();
	std::string instance_id_;
};

template<class T>
inline T Object::Create()
{
	return T();
}
