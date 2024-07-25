#pragma once
#include "Game/GameObject.h"

class StaticMesh : public GameObject
{
public:
	StaticMesh(const std::string& modelFilePath);
};