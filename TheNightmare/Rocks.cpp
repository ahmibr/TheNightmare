#include "Rocks.h"

Model* Rocks::RocksModel = NULL;

Rocks::Rocks()
{
	MinVertex = RocksModel->MinVertex;
	MaxVertex = RocksModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	Environment::InitalizeEnvironmentPosition();
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