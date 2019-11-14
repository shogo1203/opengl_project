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
	Object();
	virtual std::string ToString() const;
	std::string GetInstanceId() const;

private:
	std::string instance_id_;
};
