#include "Framework/Scene.h"
#include "Framework/GameObject.h"
#include "Graphics/Camera.h"
#include "Graphics/DXAccess.h"

Scene::Scene()
{
	camera = new Camera(glm::vec3(0.0f, 12.0f, 0.0f), DXAccess::GetWindowWidth(), DXAccess::GetWindowHeight());
	
	// TODO: Remove once GameSystems are a thing //
	gameObjects.push_back(new GameObject("Assets/Models/Sphere/sphere.gltf"));

	GameObject* sceneGround = new GameObject("Assets/Models/GroundPlane/plane.gltf");
	sceneGround->Transform.Position = glm::vec3(0.0f, -1.0f, 0.0f);
	sceneGround->Transform.Scale = glm::vec3(100.0f, 100.0f, 100.0f);
	gameObjects.push_back(sceneGround);

	GameObject* hole = new GameObject("Assets/Models/Hole/hole.gltf");
	hole->Transform.Position = glm::vec3(0.0f, 0.0f, -5.0f);
	gameObjects.push_back(hole);
}

void Scene::Update(float deltaTime)
{
	for(GameObject* gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}

	camera->Update(deltaTime);
}

Camera* Scene::GetCamera()
{
	return camera;
}

const std::vector<GameObject*>& Scene::GetGameObjects()
{
	return gameObjects;
}