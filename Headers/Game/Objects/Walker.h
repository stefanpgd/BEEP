#pragma once

#include "Game/GameObject.h"
#include "Framework/Mathematics.h"

class Walker : public GameObject
{
public:
	Walker(const glm::vec3& startPosition, const glm::vec3& endPosition);

	virtual void Update(float deltaTime) override;

private:
	float time = 0.0f;
	float speed = 2.5f;
	bool returning = false;

	glm::vec3 start;
	glm::vec3 end;
};