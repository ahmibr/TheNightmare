#pragma once
#include "Enemy.h"
class Alien : public Enemy
{
	static Model*AlienModel;
	void Move();
public:
	Alien();
	static void LoadAlienModel();
	void Draw(Shader*ourShader);
	~Alien();
};

