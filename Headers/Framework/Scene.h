#pragma once

#include <vector>

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

	const std::vector<GameObject*>& GetGameObjects();

private:
	std::vector<GameObject*> gameObjects;
};