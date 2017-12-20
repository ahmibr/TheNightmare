#include "Wizard.h"

Model* Wizard::WizardModel = NULL;
int Wizard::NumberOfWizards = 0;

int Wizard::GetNumberOfWizards()
{
	return NumberOfWizards;
}

Wizard::Wizard()
{
	NumberOfWizards++;
	UpD = true;
	JmpTimes = 0;
	FirstTime = true;
	MaxHeight = 700;
	MinVertex = WizardModel->MinVertex;
	MaxVertex = WizardModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

Ray Wizard::attack()
{
	return Enemy::attack();
}

void Wizard::Move()
{
	if (FirstTime)
	{
		GameObject::Translate(glm::vec3(0.0f, 0.01f, 0));
		JmpTimes++;
		if (JmpTimes == MaxHeight)
		{
			JmpTimes = 0;
			FirstTime = false;
		}
	}
	else
	{
		if (UpD)
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
				GameObject::Translate(glm::vec3(-0.005f, 0.005f, 0));
			JmpTimes++;
		}
		else
		{
			if (HorizontalDistance != 0)
			{
				GameObject::Translate(glm::vec3(0.0f, 0.0f, -0.005f));
				HorizontalDistance--;
			}
			else
				GameObject::Translate(glm::vec3(-0.005f, -0.005f, 0));
			JmpTimes++;
		}
		if (JmpTimes == 100)
		{
			UpD = !UpD;
			JmpTimes = 0;
		}
	}
}

void Wizard::Draw(Shader*ourShader)
{
	Wizard::Move();
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
