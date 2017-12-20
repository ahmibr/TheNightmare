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
	glm::vec3 diff = (MinVertex - MaxVertex) / glm::vec3(2);
	Myradius = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
	CalculateGraphIndex();
	AddToSceneG(this);
}

void GrimReaper::Move()
{
	GameObject::RemoveFromSG(this);

	GameObject::Translate(glm::vec3(-0.05f, 0.0f, 0.0f));
	CheckMoveValidity();
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