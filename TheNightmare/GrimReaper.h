#pragma once
#include "Enemy.h"
class GrimReaper : public Enemy
{
	static Model*GrimModel;
	void Move();
public:
	GrimReaper();
	static void LoadGrimModel();
	void Draw(Shader*ourShader);
	~GrimReaper();
};

