#pragma once

#include <vector>

class Model;

/// <summary>
/// Acts a container of all "Objects" in a given scene.
/// For now these are meshes.
/// </summary>
class Scene
{
public:
	Scene();

	const std::vector<Model*>& GetModels();

private:
	//TODO: In the future probably replace the 'Models' list, with a list of GameObjects
	// Then if the Model/Mesh of the model is nullptr, we simply don't need to render it.
	std::vector<Model*> models;
};