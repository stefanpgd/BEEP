#include "Game/GameManager.h"
#include "Game/Systems/LeaderSystem.h"

#include <imgui.h>

// Steps to do:
// 1 - Have a 'leader/king' system, by default it creates 1 bops every second
// 2 - With 5 bops you can buy an unsigned beep
// 3 - Have a Mine System, which beeps can be assigned to
// 4 - When a beep gets assigned they fall out of the sky next to the 'Mine' and land near the ground
// 5 - After landing he starts working, he travels from the mine and stops next to the hole, waits and goes back
// 6 - When the beep stops near the hole, it throws a little rock into the hole

GameManager::GameManager(Scene* scene) : scene(scene)
{
	leaderSystem = new LeaderSystem(scene, resources);
}

void GameManager::UpdateGame(float deltaTime)
{
#if _DEBUG
	DebugWindow();
#endif

	if(!updateGame)
	{
		// Game is paused //
		return;
	}

	leaderSystem->Update(deltaTime);
}

void GameManager::PauseGame()
{
	updateGame = false;
}

void GameManager::ResumeGame()
{
	updateGame = true;
}

void GameManager::DebugWindow()
{
	ImGui::Begin("Game Manager - Debug");
	ImGui::Text("Bops: %i", resources.bops);
	ImGui::Text("Unassigned beeps: %i", resources.unassignedBeeps);
	ImGui::End();
}