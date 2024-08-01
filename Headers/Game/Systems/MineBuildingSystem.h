#pragma once

#include "Game/GameSystem.h"

class MineBuildingSystem : public GameSystem
{
public:
	MineBuildingSystem(Scene* scene);

	virtual void Update(float deltaTime) override;

private:
};