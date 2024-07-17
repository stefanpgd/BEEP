#include "Framework/Scene.h"
#include "Graphics/Model.h"

Scene::Scene()
{
	Model* scenePlane = new Model("Assets/Models/GroundPlane/plane.gltf");
	scenePlane->Transform.Position = glm::vec3(0.0f, -1.0f, 0.0f);

	models.push_back(scenePlane);
	models.push_back(new Model("Assets/Models/Sphere/sphere.gltf"));
}

const std::vector<Model*>& Scene::GetModels()
{
	return models;
}