#pragma once
#include "game_object.h"
#include "mesh_renderer.h"

class TestGameObject : public GameObject
{
public:
	void Update() override;
	void Initialize() override;
};

