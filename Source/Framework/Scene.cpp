#include "Framework/Scene.h"
#include "Game/Objects/StaticMesh.h"
#include "Graphics/Camera.h"
#include "Graphics/DXAccess.h"

Scene::Scene()
{
	camera = new Camera(glm::vec3(0.0f, 12.0f, 0.0f), DXAccess::GetWindowWidth(), DXAccess::GetWindowHeight());
	
	GameObject* sceneGround = new StaticMesh("Assets/Models/GroundPlane/plane.gltf");
	sceneGround->Transform.Position = glm::vec3(0.0f, -1.0f, 0.0f);
	sceneGround->Transform.Scale = glm::vec3(100.0f, 100.0f, 100.0f);

	sceneGround->Material.Color = glm::vec3(0.75f);
	gameObjects.push_back(sceneGround);

	GameObject* hole = new StaticMesh("Assets/Models/Hole/hole.gltf");
	hole->Transform.Position = glm::vec3(0.0f, 0.0f, 0.0f);
	hole->Material.Color = glm::vec3(0.02f);

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

void Scene::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

Camera* Scene::GetCamera()
{
	return camera;
}

const std::vector<GameObject*>& Scene::GetGameObjects()
{
	return gameObjects;
}