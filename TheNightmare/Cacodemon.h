#pragma once
#include "Enemy.h"
class Cacodemon :public Enemy
{
	static Model*CacodemonModel;
	bool UpD;
	int JmpTimes;
	int MaxHeight;
	bool FirstTime;
	void Move();
	static int NumberOfCacodemons;
	int BlinkTime;
public:
	static int GetNumberOfCacodemons();
	Cacodemon();
	static void LoadCacodemonModel();
	void Draw(Shader*ourShader);
	~Cacodemon();
};