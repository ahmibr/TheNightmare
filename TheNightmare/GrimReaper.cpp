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
	return Enemy::attack();

}

void GrimReaper::Move()
{
	GameObject::Translate(glm::vec3(-0.05f, 0.0f, 0.0f));
	LastMove = glm::vec3(-0.05f, 0.0f, 0.0f);
}

void GrimReaper::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	GrimModel->Draw(*ourShader);
}

float GrimReaper::GetRadius()
{
	return GrimModel->radius;
}

void GrimReaper::LoadGrimModel()
{
	GrimModel = new Model("../resources/objects/GrimReaper/GrimReaper.obj");
}


GrimReaper::~GrimReaper()
{
}