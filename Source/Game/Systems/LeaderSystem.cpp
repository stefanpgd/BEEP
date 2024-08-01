#include "Game/Systems/LeaderSystem.h"
#include "Game/Objects/StaticMesh.h"
#include "Game/Resources.h"
#include "Framework/Input.h"

LeaderSystem::LeaderSystem(Scene* scene, Resources& resources) : GameSystem(scene), resources(resources)
{
	leader = new StaticMesh("Assets/Models/Sphere/sphere.gltf");
	leader->Transform.Position = glm::vec3(0.0f, 0.5f, 4.5f);

	scene->AddGameObject(leader);
}

void LeaderSystem::Update(float deltaTime)
{
	timer += deltaTime;

	if(timer > timeTillBop)
	{
		resources.bops++;
		timer = 0.0f;
	}

	if(Input::GetKeyDown(KeyCode::Spacebar))
	{
		if(resources.bops >= int(PriceForBeep))
		{
			resources.unassignedBeeps++;
			resources.bops -= int(PriceForBeep);

			PriceForBeep *= PurchaseMultiplier;
		}
	}
}