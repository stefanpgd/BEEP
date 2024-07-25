#include "Framework/GameObject.h"
#include "Framework/Input.h"
#include "Graphics/Model.h"

GameObject::GameObject(std::string modelFilePath)
{
	model = new Model(modelFilePath);
}

void GameObject::Update(float deltaTime) { }

Model* GameObject::GetModel()
{
	return model;
}