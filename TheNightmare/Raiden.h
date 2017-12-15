#pragma once
#include "Enemy.h"
class Raiden : public Enemy
{
	static Model*RaidenModel;
	void Move();
	static int NumberOfRaidens;
public:
	static int GetNumberOfRaidens();
	Raiden();
	static void LoadRaidenModel();
	void Draw(Shader*ourShader);
	~Raiden();
};

