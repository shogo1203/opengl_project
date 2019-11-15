#pragma once
#include "transform.h"
#include "component.h"

class GameObject :public Component
{
public:
	Transform transform_;
private:
};
