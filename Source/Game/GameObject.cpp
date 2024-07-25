#include "Game/GameObject.h"
#include "Utilities/Logger.h"

void GameObject::Update(float deltaTime) { }

Model* GameObject::GetModel()
{
	if(!model)
	{
		LOG(Log::MessageType::Error, "Game Object never initialized the model.");
	}

	return model;
}