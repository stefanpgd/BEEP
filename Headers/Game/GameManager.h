#pragma once

class SimpleSpawnerSystem;
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
	bool updateGame = true;

	Scene* scene;

	// Game System(s) //
	SimpleSpawnerSystem* spawnSystem;
};