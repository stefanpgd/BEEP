#include "Game/Systems/SimpleSpawnerSystem.h"
#include "Game/Objects/Walker.h"
#include "Framework/Input.h"
#include "Utilities/Random.h"

SimpleSpawnerSystem::SimpleSpawnerSystem(Scene* scene) : GameSystem(scene) { }

void SimpleSpawnerSystem::Update(float deltaTime)
{
	if(Input::GetKeyDown(KeyCode::Spacebar))
	{
		glm::vec3 spawn = glm::vec3(RandomInRange(-10.0f, 10.0f), 0.5f, RandomInRange(-10.0f, 10.0f));
		glm::vec3 hole = glm::vec3(0.0f, 0.5f, 0.0f);

		Walker* newWalker = new Walker(spawn, hole);
		scene->AddGameObject(newWalker);
	}
}