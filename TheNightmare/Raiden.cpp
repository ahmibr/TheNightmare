#include "Raiden.h"

Model* Raiden::RaidenModel = NULL;

Raiden::Raiden()
{
	MinVertex = RaidenModel->MinVertex;
	MaxVertex = RaidenModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void Raiden::Move()
{
}

void Raiden::LoadRaidenModel()
{
	RaidenModel = new Model("../resources/objects/Raiden/Raiden.obj");
}

void Raiden::Draw(Shader * ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	RaidenModel->Draw(*ourShader);
}


Raiden::~Raiden()
{
}
