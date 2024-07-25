#pragma once

#include "Game/GameSystem.h"

class SimpleSpawnerSystem : public GameSystem
{
public:
	SimpleSpawnerSystem(Scene* scene);

	virtual void Update(float deltaTime) override;
};