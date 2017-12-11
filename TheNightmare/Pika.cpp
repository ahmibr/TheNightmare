#include "Pika.h"

Model* Pika::PikaModel = NULL;

Pika::Pika()
{
	UpD = false;
	JmpTimes = 0;
	MinVertex = PikaModel->MinVertex;
	MaxVertex = PikaModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void Pika::Move()
{
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
