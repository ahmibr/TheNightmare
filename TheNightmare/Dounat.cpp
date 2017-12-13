#include "Dounat.h"

Model* Dounat::DounatModel = NULL;

Dounat::Dounat()
{
	MinVertex = DounatModel->MinVertex;
	MaxVertex = DounatModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void Dounat::Move()
{
}

void Dounat::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	DounatModel->Draw(*ourShader);
}

void Dounat::LoadDounatModel()
{
	DounatModel = new Model("../resources/objects/Dounat/Dounat.obj");
}


Dounat::~Dounat()
{
}