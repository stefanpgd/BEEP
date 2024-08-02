#include "Framework/Physics.h"
#include "Framework/Mathematics.h"
#include "Framework/Input.h"
#include "Framework/Scene.h"
#include "Graphics/DXAccess.h"
#include "Graphics/Camera.h"
#include "Utilities/Logger.h"

Scene* Physics::activeScene;
bool Physics::initialized = false;

/// <summary>
/// Casts a single ray from the camera, based on mouse & camera position
/// In this project we know that we will always have a "world-plane" that is the ground
/// in our scene. We raycast towards that using some standard ray tracing techniques.
/// </summary>
glm::vec3 Physics::GetWorldMousePosition()
{
	int sW = DXAccess::GetWindowWidth();
	int sH = DXAccess::GetWindowHeight();

	float aspectRatio = float(sW) / float(sH);

	int mX = glm::clamp(Input::GetMouseX(), 0, sW);
	int mY = glm::clamp(Input::GetMouseY(), 0, sH);

	float ndcX = float(mX) / float(sW) - 0.5;
	float ndcY = float(mY) / float(sH) - 0.5;

	// Figure out the virtual plane //
	Camera* camera = activeScene->GetCamera();

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
			return hitpoint;
		}
	}

	LOG(Log::MessageType::Error, "Couldn't find a hitpoint for the ray cast!");
	return glm::vec3(0.0f);
}

void Physics::Initialize(Scene* scene)
{
	if(!initialized)
	{
		activeScene = scene;
		initialized = false;
	}
}