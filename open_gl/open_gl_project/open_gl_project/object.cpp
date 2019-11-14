#include "object.h"

std::string Object::ToString() const
{
	return "Object";
}

std::string Object::GetInstanceId() const
{
	return instance_id_;
}

Object::Object()
{
	boost::uuids::uuid id = boost::uuids::random_generator()();
	instance_id_ = boost::lexical_cast<std::string>(id);
}
