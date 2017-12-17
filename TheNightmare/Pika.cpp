#include "Pika.h"

Model* Pika::PikaModel = NULL;
int Pika::NumberOfPikas = 0;

int Pika::GetNumberOfPikas()
{
	return NumberOfPikas;
}

Pika::Pika()
{
	NumberOfPikas++;
	UpD = false;
	JmpTimes = 0;
	MinVertex = PikaModel->MinVertex;
	MaxVertex = PikaModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();

	if (Direction == 0)
		GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);
	else
		GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
}

void Pika::Move()
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

void Pika::Draw(Shader*ourShader)
{
	Pika::Move();
	ourShader->setMat4("model", ModelMatrix);
	PikaModel->Draw(*ourShader);
}

void Pika::LoadPikaModel()
{
	PikaModel = new Model("../resources/objects/Pika/Pika.obj");
}


Pika::~Pika()
{
}
