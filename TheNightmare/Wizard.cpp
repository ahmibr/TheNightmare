#include "Wizard.h"

Model* Wizard::WizardModel = NULL;

Wizard::Wizard()
{
	MinVertex = WizardModel->MinVertex;
	MaxVertex = WizardModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void Wizard::Move()
{
}

void Wizard::Draw(Shader*ourShader)
{
		ourShader->setMat4("model", ModelMatrix);
		WizardModel->Draw(*ourShader);
}

void Wizard::LoadWizardModel()
{
	WizardModel = new Model("../resources/objects/Wizard/Wizard.obj");
}


Wizard::~Wizard()
{
}
