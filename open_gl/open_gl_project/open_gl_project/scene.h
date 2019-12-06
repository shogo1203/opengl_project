#pragma once
#include "object.h"

class Scene :
	public Object
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Finalize();
};

