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
	Angle = 30;
	InvrseAngle = 0;
	RotationTime = 40;
	MinVertex = AlienModel->MinVertex;
	MaxVertex = AlienModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
	//GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 30);
}

void Alien::Move()
{
	if (RotationTime == 0)
	{
		if (RightLeft) //Rotating Right
		{
			GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 30);
		}
		else //Rotating Left
		{
			GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y+10.0f,0.0f), -30);
			GameObject::Translate(glm::vec3(-1.0f, 0.0f, 0.0f));
		}
		RotationTime = 150;
		RightLeft = !RightLeft;
	}

	
	RotationTime--;
	//if (RotationTime == 0)
	//{
	//	if (Angle == 30 || Angle == -30)
	//		PreviousAngle = Angle;
	//	if (PreviousAngle == 30 && InvrseAngle != 6)
	//	{
	//		GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -15);
	//		Angle -= 15;
	//		InvrseAngle++;
	//	}
	//	else if (PreviousAngle == -30 && InvrseAngle != 0)
	//	{
	//		GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 15);
	//		Angle += 15;
	//		InvrseAngle -= 15;
	//	}

	//	if (Angle == 30 || Angle == -30)
	//		RotationTime = 150;
	//	else
	//		RotationTime = 15;

	//}

	//RotationTime--;

	//GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -Angle);
	//if (Angle == 30 || Angle == -30)
	//	GameObject::Translate(glm::vec3(-0.005f, 0.0f, 0.0f));
	//if (Angle == 30 || Angle == -30)
	//	GameObject::Translate(glm::vec3(-0.009f, 0.0f, 0.0f));

	//GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), Angle);

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