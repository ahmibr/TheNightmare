#pragma once
#include "Enemy.h"
class GrimReaper : public Enemy
{
	static Model*GrimModel;
	static int NumberOfGrims;
public:
	static int GetNumberOfGrims();
	GrimReaper();
	static void LoadGrimModel();
	void Draw(Shader*ourShader);
	void Move();
	float GetRadius();
	virtual Ray attack();
	~GrimReaper();
};

