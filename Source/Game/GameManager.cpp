#include "Game/GameManager.h"
#include "Game/Systems/SimpleSpawnerSystem.h"

GameManager::GameManager(Scene* scene) : scene(scene)
{
	spawnSystem = new SimpleSpawnerSystem(scene);
}

void GameManager::UpdateGame(float deltaTime)
{
	if(!updateGame)
	{
		// Game is paused //
		return;
	}

	spawnSystem->Update(deltaTime);
}

void GameManager::PauseGame()
{
	updateGame = false;
}

void GameManager::ResumeGame()
{
	updateGame = true;
}