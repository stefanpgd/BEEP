#include "Game/Objects/Walker.h"
#include "Framework/Mathematics.h"
#include "Utilities/Random.h"

Walker::Walker(const glm::vec3& startPosition, const glm::vec3& endPosition) : start(startPosition), end(endPosition) 
{
	Transform.Position = startPosition;

	Transform.Scale = glm::vec3(0.5f);
	Material.Color = glm::vec3(Random01());

	model = new Model("Assets/Models/Sphere/sphere.gltf");
}

void Walker::Update(float deltaTime)
{
	time += deltaTime;

	glm::vec3& target = returning ? start : end;
	glm::vec3 newPosition = glm::normalize(target - Transform.Position) * speed;

	Transform.Position.x += newPosition.x * deltaTime;
	Transform.Position.z += newPosition.z * deltaTime;

	float bounceTime = time * 16.0f;
	float bounceHeight = 0.35f;
	float worldHeight = 0.25f;
	Transform.Position.y = (cosf(bounceTime) * bounceHeight) + worldHeight;

	if(glm::length(target - Transform.Position) < 0.5f)
	{
		returning = !returning;
	}
}