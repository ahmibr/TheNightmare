#pragma once
#include "Enemy.h"
class Dounat : public Enemy
{
	static Model*DounatModel;
	bool FirstTime;
	int JmpTimes;
	int Angle;
	int PreviousAngle;
	void Move();
	static int NumberOfDounats;
public:
	static int GetNumberOfDounats();
	Dounat();
	virtual Ray attack();
	static void LoadDounatModel();
	void Draw(Shader*ourShader);
	~Dounat();
};

