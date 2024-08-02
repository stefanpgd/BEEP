#pragma once

#include <glm.hpp>

class Scene;

class Physics
{
public:
	static void Initialize(Scene* scene);
	static glm::vec3 GetWorldMousePosition();

private:
	static Scene* activeScene;
	static bool initialized;

	friend class GameManager;
};