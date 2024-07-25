#pragma once

#include "Framework/Mathematics.h"

// TODO: For now this excludes Textures, in the future 
// the option to use a model's texture or use the material info itself should be present

/// <summary>
/// Containter that holds all information about a model's material properties.
/// </summary>
struct Material
{
	glm::vec3 Color{ 1.0f, 1.0f, 1.0f };
};