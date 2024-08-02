#include "Game/GameManager.h"
#include "Game/Systems/LeaderSystem.h"
#include "Game/Objects/StaticMesh.h"

#include "Graphics/Camera.h"
#include "Graphics/DXAccess.h"
#include "Framework/Input.h"
#include "Utilities/Logger.h"

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

	RaycastTesting();

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

void GameManager::RaycastTesting()
{
	int sW = DXAccess::GetWindowWidth();
	int sH = DXAccess::GetWindowHeight();

	float aspectRatio = float(sW) / float(sH);
	
	int mX = glm::clamp(Input::GetMouseX(), 0, sW);
	int mY = glm::clamp(Input::GetMouseY(), 0, sH);

	float ndcX = float(mX) / float(sW) - 0.5;
	float ndcY = float(mY) / float(sH) - 0.5;

	// Figure out the virtual plane //
	Camera* camera = scene->GetCamera();

	glm::vec3 vpC = camera->Position + camera->GetForwardVector();
	glm::vec3 vpW = glm::cross(camera->GetForwardVector(), camera->GetUpwardVector()) * aspectRatio;
	glm::vec3 vpH = camera->GetUpwardVector();

	float focalLength = 0.85f;
	// Center of the VP //
	glm::vec3 virtualPlaneTarget = camera->Position + camera->GetForwardVector() * focalLength;
	virtualPlaneTarget += vpW * ndcX; // add mouse X contribution
	virtualPlaneTarget += -vpH * ndcY; // add mouse Y contribution

	glm::vec3 rayDir = glm::normalize(virtualPlaneTarget - camera->Position);

	// Now with the rayDirection, we can compute the plane intersection //
	glm::vec3 planeNormal = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 planeCenter = glm::vec3(0.0f);

	float denom = glm::dot(planeNormal, rayDir);

	if(abs(denom) > 1e-6)
	{
		glm::vec3 pToIntersect = planeCenter - camera->Position;
		float d = glm::dot(pToIntersect, planeNormal);
		float t = d / denom;

		if(t >= 0.0f)
		{
			glm::vec3 hitpoint = camera->Position + rayDir * t;
			testingBubble->Transform.Position = hitpoint;
		}
		else
		{
			LOG("Ray cast didn't hit world-plane...");
		}
	}
}