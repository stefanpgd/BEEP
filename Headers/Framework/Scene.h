#pragma once

#include <vector>

class Camera;
class GameObject;

/// <summary>
/// Acts a container for all 'GameObjects' and 'GameSystems' that run in the game.
/// It also is responsible for Updating these objects and systems. 
/// </summary>
class Scene
{
public:
	Scene();

	void Update(float deltaTime);

	void AddGameObject(GameObject* gameObject);

	Camera* GetCamera();
	const std::vector<GameObject*>& GetGameObjects();

private:
	Camera* camera;

	std::vector<GameObject*> gameObjects;
};