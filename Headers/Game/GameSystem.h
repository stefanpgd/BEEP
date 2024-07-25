#pragma once

#include "Framework/Scene.h"

/// <summary>
/// Game Systems are responsible for the backend game logic. They track resources, spawn
/// in game objects, and run the core loop of the game itself. Game Systems are managed by
/// the Game Manager.
/// </summary>
class GameSystem
{
public:
	GameSystem(Scene* scene);

	virtual void Update(float deltaTime);

protected:
	Scene* scene;
};