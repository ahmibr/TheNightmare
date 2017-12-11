#pragma once
#include "Enemy.h"
class Raiden : public Enemy
{
	static Model*RaidenModel;
	void Move();
public:
	Raiden();
	static void LoadRaidenModel();
	void Draw(Shader*ourShader);
	~Raiden();
};

