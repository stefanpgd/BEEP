#pragma once

#include <string>
#include "Graphics/Transform.h"

class Model;

/// <summary>
/// A 'GameObject' is any object that's visible in-game. Meaning that it should always have
/// A model/mesh attached to it, otherwise it's likely a GameSystem instead.
/// Optionally, extra logic can be added into the Update function. For things like movement
/// </summary>
class GameObject
{
public:
	GameObject(std::string modelFilePath);

	virtual void Update(float deltaTime); // Called by the Scene

	Model* GetModel();

public:
	Transform Transform;

private:
	Model* model;
};