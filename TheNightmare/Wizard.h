#pragma once
#include "Enemy.h"
class Wizard :public Enemy
{
	static Model*WizardModel;
	void Move();
public:
	Wizard();
	static void LoadWizardModel();
	void Draw(Shader*ourShader);
	~Wizard();
};