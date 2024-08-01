#pragma once

#include "Game/Resources.h"

class LeaderSystem;
class Scene;

/// <summary>
/// Owns all Game Systems, and makes sure they run in the right order.
/// </summary>
class GameManager
{
public:
	GameManager(Scene* scene);
	
	void UpdateGame(float deltaTime);

	void PauseGame();
	void ResumeGame();

private:
	void DebugWindow();

private:
	bool updateGame = true;

	Scene* scene;
	Resources resources;

	// Game System(s) //
	LeaderSystem* leaderSystem;
};