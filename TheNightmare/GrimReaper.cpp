#include "GrimReaper.h"

Model* GrimReaper::GrimModel = NULL;
int GrimReaper::NumberOfGrims = 0;

int GrimReaper::GetNumberOfGrims()
{
	return NumberOfGrims;
}

GrimReaper::GrimReaper()
{
	NumberOfGrims++;
	MinVertex = GrimModel->MinVertex;
	MaxVertex = GrimModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

Ray GrimReaper::attack()
{
	//glm::vec3 bullet = glm::normalize(glm::vec3(rand(), 8.5f, rand()));
	return Enemy::attack();
}

void GrimReaper::Move()
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

void GrimReaper::Draw(Shader*ourShader)
{
	GrimReaper::Move();
	ourShader->setMat4("model", ModelMatrix);
	GrimModel->Draw(*ourShader);
}

void GrimReaper::LoadGrimModel()
{
	GrimModel = new Model("../resources/objects/GrimReaper/GrimReaper.obj");
}


GrimReaper::~GrimReaper()
{
}