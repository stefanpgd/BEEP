#include "Game/Objects/StaticMesh.h"

StaticMesh::StaticMesh(const std::string& modelFilePath)
{
	model = new Model(modelFilePath);
}