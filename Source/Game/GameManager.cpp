#include "Game/GameManager.h"
#include "Game/Systems/LeaderSystem.h"
#include "Game/Objects/StaticMesh.h"

#include "Graphics/Camera.h"
#include "Graphics/DXAccess.h"
#include "Framework/Physics.h"

#include <imgui.h>

// Steps to do:
// 1 DONE - Have a 'leader/king' system, by default it creates 1 bops every second
// 2 DONE - With 5 bops you can buy an unsigned beep
// 3 - Have a Mine System, which beeps can be assigned to
// 4 - When a beep gets assigned they fall out of the sky next to the 'Mine' and land near the ground
// 5 - After landing he starts working, he travels from the mine and stops next to the hole, waits and goes back
// 6 - When the beep stops near the hole, it throws a little rock into the hole

StaticMesh* testingBubble;

GameManager::GameManager(Scene* scene) : scene(scene)
{
	leaderSystem = new LeaderSystem(scene, resources);

	testingBubble = new StaticMesh("Assets/Models/Sphere/sphere.gltf");
	testingBubble->Transform.Scale = glm::vec3(0.1f);
	scene->AddGameObject(testingBubble);
}

void GameManager::UpdateGame(float deltaTime)
{
#if _DEBUG
	DebugWindow();
#endif

	testingBubble->Transform.Position = Physics::GetWorldMousePosition();

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