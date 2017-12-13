#pragma once
#include "Enemy.h"
class Dounat : public Enemy
{
	static Model*DounatModel;
	void Move();
public:
	Dounat();
	static void LoadDounatModel();
	void Draw(Shader*ourShader);
	~Dounat();
};

