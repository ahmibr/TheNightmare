#include "Alien.h"

Model* Alien::AlienModel = NULL;

Alien::Alien()
{
	MinVertex = AlienModel->MinVertex;
	MaxVertex = AlienModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void Alien::Move()
{
}

void Alien::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	AlienModel->Draw(*ourShader);
}

void Alien::LoadAlienModel()
{
	AlienModel = new Model("../resources/objects/Alien/Alien.obj");
}


Alien::~Alien()
{
}