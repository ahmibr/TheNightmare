#pragma once
#include "Enemy.h"
class Alien : public Enemy
{
	float Angle;
	float PreviousAngle;
	float InvrseAngle;
	int RotationTime;
	bool RightLeft;
	static Model*AlienModel;
	void Move();
	static int NumberOfAliens;
public:
	static int GetNumberOfAliens();
	Alien();
	virtual Ray attack();
	static void LoadAlienModel();
	void Draw(Shader*ourShader);
	~Alien();
};

