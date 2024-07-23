#include "Framework/Scene.h"
#include "Framework/GameObject.h"

Scene::Scene()
{
	gameObjects.push_back(new GameObject("Assets/Models/Sphere/sphere.gltf"));
}

const std::vector<GameObject*>& Scene::GetGameObjects()
{
	return gameObjects;
}