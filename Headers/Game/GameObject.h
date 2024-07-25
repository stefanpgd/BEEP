#pragma once

#include <string>
#include "Graphics/Transform.h"
#include "Graphics/Model.h"
#include "Graphics/Material.h"

/// <summary>
/// A 'GameObject' is any object that's visible in-game. Meaning that it should always have
/// A model/mesh attached to it, otherwise it's likely a GameSystem instead.
/// Optionally, extra logic can be added into the Update function, e.g. for movement.
/// </summary>
class GameObject
{
public:
	virtual void Update(float deltaTime); // Called by the Scene

	Model* GetModel();

public:
	Transform Transform;
	Material Material;

protected:
	Model* model;
};