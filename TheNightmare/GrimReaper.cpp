#include "GrimReaper.h"

Model* GrimReaper::GrimModel = NULL;

GrimReaper::GrimReaper()
{
	MinVertex = GrimModel->MinVertex;
	MaxVertex = GrimModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void GrimReaper::Move()
{
}

void GrimReaper::Draw(Shader*ourShader)
{
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