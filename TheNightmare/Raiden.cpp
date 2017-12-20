#include "Raiden.h"

Model* Raiden::RaidenModel = NULL;
int Raiden::NumberOfRaidens = 0;

int Raiden::GetNumberOfRaidens()
{
	return NumberOfRaidens;
}

Raiden::Raiden()
{
	NumberOfRaidens++;
	MinVertex = RaidenModel->MinVertex;
	MaxVertex = RaidenModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

Ray Raiden::attack()
{
	return Enemy::attack();
}

void Raiden::Move()
{
	if (HorizontalDistance != 0)
	{
		if (Direction == 0)
			GameObject::Translate(glm::vec3(0.0f, 0.0f, -0.005f));
		else
			GameObject::Translate(glm::vec3(0.0f, 0.0f, 0.005f));
		HorizontalDistance--;
	}
	else
		GameObject::Translate(glm::vec3(-0.005f, 0.0f, 0.0f));
}

void Raiden::LoadRaidenModel()
{
	RaidenModel = new Model("../resources/objects/Raiden/Raiden.obj");
}

void Raiden::Draw(Shader * ourShader)
{
	Raiden::Move();
	ourShader->setMat4("model", ModelMatrix);
	RaidenModel->Draw(*ourShader);
}


Raiden::~Raiden()
{
}
