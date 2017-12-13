#pragma once
#include "Enemy.h"
class Pika : public Enemy
{
	static Model*PikaModel;
	bool UpD;
	int JmpTimes;
	void Move();
public:
	Pika();
	static void LoadPikaModel();
	void Draw(Shader*ourShader);
	~Pika();
};

