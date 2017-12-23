#pragma once
#include "Enemy.h"
class Pika : public Enemy
{
	static Model*PikaModel;
	bool UpD;
	int JmpTimes;
	static int NumberOfPikas;
public:
	static int GetNumberOfPikas();
	Pika();
	static void LoadPikaModel();
	void Draw(Shader*ourShader);
	virtual Ray attack();
	void Move();
	float GetRadius();
	~Pika();
};

