#include "Framework/Scene.h"
#include "Framework/GameObject.h"
#include "Graphics/Camera.h"
#include "Graphics/DXAccess.h"

Scene::Scene()
{
	camera = new Camera(glm::vec3(0.0f, 0.0f, 5.0f), DXAccess::GetWindowWidth(), DXAccess::GetWindowHeight());
	
	// TODO: Remove once GameSystems are a thing //
	gameObjects.push_back(new GameObject("Assets/Models/Sphere/sphere.gltf"));
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