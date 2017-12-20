#include "Alien.h"

Model* Alien::AlienModel = NULL;
int Alien::NumberOfAliens = 0;

int Alien::GetNumberOfAliens()
{
	return NumberOfAliens;
}

Alien::Alien()
{
	NumberOfAliens++;
	RightLeft = 1;
	RotationTime = 40;
	MinVertex = AlienModel->MinVertex;
	MaxVertex = AlienModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();

	if (Direction == 0)
		GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);
	else
		GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
}

void Alien::Move()
{
	
	if (RotationTime == 0)
	{
		if (RightLeft) //Rotating Right
		{
			GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 25);
		}
		else //Rotating Left
		{
			GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y + 10.0f, 0.0f), -25);
			if (HorizontalDistance != 0)
			{
				GameObject::Translate(glm::vec3(-2.0f, 0.0f, 0.0f));
			}
			else
				GameObject::Translate(glm::vec3(-5.0f, 0.0f, 0.0f));
		}
		if (HorizontalDistance == 0)
		{
			if (Direction == 0)
				GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
			else
				GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);
			HorizontalDistance = -1;
		}
		RotationTime = 20;
		RightLeft = !RightLeft;
	}

	if (HorizontalDistance != 0)
	{
		HorizontalDistance--;
		if (HorizontalDistance == 0)
			RotationTime = 20;
	}


	RotationTime--;

}

void Alien::Draw(Shader*ourShader)
{
	Alien::Move();
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