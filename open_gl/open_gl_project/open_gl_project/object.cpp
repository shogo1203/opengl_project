#include "object.h"

std::string Object::ToString() const
{
	return "Object";
}

Object::Object()
{
	boost::uuids::uuid id = boost::uuids::random_generator()();
	instance_id_ = boost::lexical_cast<std::string>(id);
	std::cout << instance_id_ << std::endl;
}
