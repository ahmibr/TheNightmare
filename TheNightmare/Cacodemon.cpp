#include "Cacodemon.h"

Model* Cacodemon::CacodemonModel = NULL;
int Cacodemon::NumberOfCacodemons = 0;

int Cacodemon::GetNumberOfCacodemons()
{
	return NumberOfCacodemons;
}

Cacodemon::Cacodemon()
{
	NumberOfCacodemons++;
	UpD = true;
	JmpTimes = 0;
	FirstTime = true;
	MaxHeight = 300;
	MinVertex = CacodemonModel->MinVertex;
	MaxVertex = CacodemonModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	BlinkTime = 0;
	Enemy::InitalizeEnemyPosition();
}

void Cacodemon::Move()
{
	if (FirstTime)
	{
		GameObject::Translate(glm::vec3(0.0f, 0.03f, 0));
		JmpTimes++;
		if (JmpTimes == MaxHeight)
		{
			JmpTimes = 0;
			if (Direction == 0)
				GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);
			else
				GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
			FirstTime = false;
		}
	}
	else
	{
		if (HorizontalDistance > 0)
		{
			if (UpD)
			{
				if (Direction == 0)
					GameObject::Translate(glm::vec3(0.02f, 0.01f, 0.0f));
				else
					GameObject::Translate(glm::vec3(-0.02f, 0.01f, 0.0f));
				HorizontalDistance--;
				JmpTimes++;
			}
			else
			{
				if (Direction == 0)
					GameObject::Translate(glm::vec3(0.02f, -0.01f, 0.0f));
				else
					GameObject::Translate(glm::vec3(-0.02f, -0.01f, 0.0f));
				HorizontalDistance--;

				JmpTimes++;
			}
			if (JmpTimes == 40)
			{
				UpD = !UpD;
				JmpTimes = 0;
			}
		}
		else
		{
			if (HorizontalDistance == 0)
			{
				if (Direction == 0)
					GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
				else
					GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);
				HorizontalDistance = -1;
			}


			if (UpD)
			{
				GameObject::Translate(glm::vec3(-0.01f, 0.01f, 0));
				JmpTimes++;
			}
			else
			{
				GameObject::Translate(glm::vec3(-0.01f, -0.01f, 0));
				JmpTimes++;
			}
			if (JmpTimes == 40)
			{
				UpD = !UpD;
				JmpTimes = 0;
			}

		}
	}
}

void Cacodemon::Draw(Shader*ourShader)
{
	Cacodemon::Move();
	ourShader->setMat4("model", ModelMatrix);
	CacodemonModel->meshes[1].Draw(*ourShader);
	if (BlinkTime == 0)
		BlinkTime = 15;
	else
		CacodemonModel->meshes[0].Draw(*ourShader);

	BlinkTime--;
}

void Cacodemon::LoadCacodemonModel()
{
	CacodemonModel = new Model("../resources/objects/Cacodemon/cacodemon.obj");
}

Ray Cacodemon::attack()
{
	return Enemy::attack();
}


Cacodemon::~Cacodemon()
{
}
