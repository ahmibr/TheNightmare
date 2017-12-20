#include "Raiden.h"
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

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
	glm::vec3 diff = (MinVertex - MaxVertex) / glm::vec3(2);
	Myradius = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
	ArmModelMatrix = ModelMatrix;
	CalculateGraphIndex();
	AddToSceneG(this);
}

void Raiden::Move()
{
	GameObject::RemoveFromSG(this);
	if (HorizontalDistance != 0)
	{
		if (Direction == 0)
			GameObject::Translate(glm::vec3(0.0f, 0.0f, -0.02f));
		else
			GameObject::Translate(glm::vec3(0.0f, 0.0f, 0.02f));
		ArmModelMatrix = ModelMatrix;
		HorizontalDistance--;
		if (HorizontalDistance == 0)
			Shooting = ShootingTime;
	}
	else
	{
		if (Shooting > 0)
		{
			if (Shooting == ShootingTime)
			{
				ArmModelMatrix = glm::translate(ArmModelMatrix, glm::vec3(0.0f, Objectheight / 2.0f, 0.0f));
				ArmModelMatrix = glm::rotate(ArmModelMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			}
			else if (Shooting == 1)
			{
				ArmModelMatrix = glm::rotate(ArmModelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				ArmModelMatrix = glm::translate(ArmModelMatrix, glm::vec3(0.0f, -Objectheight / 2.0f, 0.0f));
			}
			Shooting--;
		}
		else
		{
			GameObject::Translate(glm::vec3(-0.1f, 0.0f, 0.0f));
			ArmModelMatrix = ModelMatrix;
		}
		
	}

	CheckMoveValidity();
}

void Raiden::LoadRaidenModel()
{
	RaidenModel = new Model("../resources/objects/Raiden/Raiden.obj");
}

void Raiden::Draw(Shader * ourShader)
{
	Raiden::Move();
	ourShader->setMat4("model", ModelMatrix);
	RaidenModel->meshes[1].Draw(*ourShader);
	ourShader->setMat4("model", ArmModelMatrix);
	RaidenModel->meshes[0].Draw(*ourShader);
}


Raiden::~Raiden()
{
}
