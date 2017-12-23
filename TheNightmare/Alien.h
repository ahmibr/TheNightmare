#pragma once
#include "Enemy.h"
class Alien : public Enemy
{
	int RotationTime;
	bool RightLeft;
	static Model*AlienModel;
	static int NumberOfAliens;
public:
	static int GetNumberOfAliens();
	Alien();
	static void LoadAlienModel();
	void Draw(Shader*ourShader);
	void Move();
	float GetRadius();
	virtual Ray attack();
	~Alien();
};

