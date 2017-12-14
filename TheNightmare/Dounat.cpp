#include "Dounat.h"

Model* Dounat::DounatModel = NULL;
int Dounat::NumberOfDounats = 0;

int Dounat::GetNumberOfDounats()
{
	return NumberOfDounats;
}

Dounat::Dounat()
{
	NumberOfDounats++;
	JmpTimes = 0;
	FirstTime = true;
	Angle = 0;
	PreviousAngle = -30;
	MinVertex = DounatModel->MinVertex;
	MaxVertex = DounatModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
	//GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
}

void Dounat::Move()
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
	{
		if (FirstTime && JmpTimes != 20)
		{
			GameObject::Translate(glm::vec3(0.0f, 0.01f, 0.0f));
			JmpTimes++;
		}
		{
			FirstTime = false;
			GameObject::Translate(glm::vec3(-0.01f, 0.0f, 0.0f));
			if (JmpTimes == 0)
			{
				if (Angle == 0)
				{
					GameObject::Rotate(glm::vec3(abs(ObjectCenter.x), 0.0f, 0.0f), -30);
					Angle = -30;
					JmpTimes = 1;
				}
				else
				{
					GameObject::Rotate(glm::vec3(abs(ObjectCenter.x), 0.0f, 0.0f), -2*Angle);
					Angle = !Angle;
					JmpTimes = 100;
				}
			}
			JmpTimes--;
		}
	}
}

void Dounat::Draw(Shader*ourShader)
{
	Dounat::Move();
	ourShader->setMat4("model", ModelMatrix);
	DounatModel->Draw(*ourShader);
}

void Dounat::LoadDounatModel()
{
	DounatModel = new Model("../resources/objects/Dounat/Dounat.obj");
}


Dounat::~Dounat()
{ }