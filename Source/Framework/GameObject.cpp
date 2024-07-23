#include "Framework/GameObject.h"
#include "Framework/Input.h"
#include "Graphics/Model.h"

GameObject::GameObject(std::string modelFilePath)
{
	model = new Model(modelFilePath);
}

void GameObject::Update(float deltaTime) 
{
	float dir = Input::GetKey(KeyCode::E) - Input::GetKey(KeyCode::Q);
	float speed = dir * 3.5f;

	Transform.Position.x += speed * deltaTime;
}

Model* GameObject::GetModel()
{
	return model;
}