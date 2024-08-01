#pragma once

#include "Game/GameSystem.h"

struct Resources;

class LeaderSystem : public GameSystem
{
public:
	LeaderSystem(Scene* scene, Resources& resources);

	virtual void Update(float deltaTime) override;

public:
	float PriceForBeep = 5;
	float PurchaseMultiplier = 1.2;

private:
	Resources& resources;
	GameObject* leader;

	float timer = 0.0f;
	float timeTillBop = 1.0f;
};