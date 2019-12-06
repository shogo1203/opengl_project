#pragma once
#include "game_object.h"
#include "image_loader.h"
#include "opengl_genderer.h"

class TestGameObject : public GameObject
{
public:
	void Update() override;
	void Initialize() override;
};

