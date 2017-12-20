#pragma once
#include "Enemy.h"
class GrimReaper : public Enemy
{
	static Model*GrimModel;
	void Move();
	static int NumberOfGrims;
public:
	static int GetNumberOfGrims();
	GrimReaper();
	virtual Ray attack();
	static void LoadGrimModel();
	void Draw(Shader*ourShader);
	~GrimReaper();
};

