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
	MaxHeight = 300;
	MinVertex = WizardModel->MinVertex;
	MaxVertex = WizardModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Enemy::InitalizeEnemyPosition();
}

void Wizard::Move()
{
	if (FirstTime)
	{
		GameObject::Translate(glm::vec3(0.0f, 0.03f, 0));
		JmpTimes++;
		if (JmpTimes == MaxHeight)
		{
			JmpTimes = 0;
			if (Direction == 0)
				GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), -90);
			else
				GameObject::Rotate(glm::vec3(0.0f, ObjectCenter.y, 0.0f), 90);
			FirstTime = false;
		}
	}
	else
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
