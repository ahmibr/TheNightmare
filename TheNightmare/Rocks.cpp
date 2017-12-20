#include "Rocks.h"

Model* Rocks::RocksModel = NULL;

Rocks::Rocks()
{
	MinVertex = RocksModel->MinVertex;
	MaxVertex = RocksModel->MaxVertex;
	glm::vec3 diff = (MinVertex - MaxVertex) / glm::vec3(2);
	Myradius = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	Environment::InitalizeEnvironmentPosition();
	CalculateGraphIndex();
	AddToSceneG(this,1);
}

void Rocks::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	RocksModel->Draw(*ourShader);
}

void Rocks::LoadRocksModel()
{
	RocksModel = new Model("../resources/objects/Rocks/Rocks.obj");
}


Rocks::~Rocks()
{
}