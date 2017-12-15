#pragma once
#include "Enemy.h"
class Wizard :public Enemy
{
	static Model*WizardModel;
	bool UpD;
	int JmpTimes;
	int MaxHeight;
	bool FirstTime;
	void Move();
	static int NumberOfWizards;
public:
	static int GetNumberOfWizards();
	Wizard();
	static void LoadWizardModel();
	void Draw(Shader*ourShader);
	~Wizard();
};