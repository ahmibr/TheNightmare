#include "Dounat.h"

Model* Dounat::DounatModel = NULL;
int Dounat::NumberOfDounats = 0;

int Dounat::GetNumberOfDounats()
{
	return NumberOfDounats;
}

Ray Dounat::attack()
{
	return Enemy::attack();

}

Dounat::Dounat()
{
	NumberOfDounats++;
	JmpTimes = 0;
	FirstTime = true;
	Angle = 0;
	PreviousAngle = -20;
	MinVertex = DounatModel->MinVertex;
	MaxVertex = DounatModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void Dounat::Move()
{
	glm::vec3 PreviousCenter = GetCenter();
	if (HorizontalDistance != 0)
	{
		if (FirstTime && JmpTimes != 20)
		{
			GameObject::Translate(glm::vec3(0.0f, 0.01f, 0.0f));
			JmpTimes++;
		}
		else
		{
			FirstTime = false;
			if (Angle == 0)
			{
				JmpTimes = 1;
				//if (Direction == 0)
				///	GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);
				//else
				///GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
				Angle = 20;
			}

			if (Direction == 0)
				GameObject::Translate(glm::vec3(-0.0f, 0.0f, -0.04f));
			else
				GameObject::Translate(glm::vec3(0.0f, 0.0f, 0.04f));

			HorizontalDistance--;
			if (HorizontalDistance == 0)
			{
				//if (Direction == 0)
				/*	GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
				else
				GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);*/
				Angle = 0;
			}
		}
	}
	else
	{
		if (Angle == 0)
		{
			//GameObject::Rotate(glm::vec3(abs(ObjectCenter.x), 0.0f, 0.0f), -20);
			Angle = -20;
		}
		else
		{
			FirstTime = false;
			GameObject::Translate(glm::vec3(-0.02f, 0.0f, 0.0f));
			if (JmpTimes == 0)
			{
				/*GameObject::Rotate(glm::vec3(abs(ObjectCenter.x), 0.0f, 0.0f), -2 * Angle);*/
				Angle = -Angle;
				JmpTimes = 50;
			}
			JmpTimes--;
		}
	}
	LastMove = GetCenter() - PreviousCenter;
}

void Dounat::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	DounatModel->Draw(*ourShader);
}

float Dounat::GetRadius()
{
	return DounatModel->radius;
}

void Dounat::LoadDounatModel()
{
	DounatModel = new Model("../resources/objects/Dounat/Dounat.obj");
}


Dounat::~Dounat()
{ }