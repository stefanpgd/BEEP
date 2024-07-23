#include "Framework/Scene.h"
#include "Framework/GameObject.h"

Scene::Scene()
{
	gameObjects.push_back(new GameObject("Assets/Models/Sphere/sphere.gltf"));
}

void Scene::Update(float deltaTime)
{
	for(GameObject* gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

const std::vector<GameObject*>& Scene::GetGameObjects()
{
	return gameObjects;
}