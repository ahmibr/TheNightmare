#pragma once
#include "Enemy.h"
class Raiden : public Enemy
{
	static Model*RaidenModel;
	void Move();
	static int NumberOfRaidens;
	glm::mat4 ArmModelMatrix;
public:
	static int GetNumberOfRaidens();
	Raiden();
	virtual Ray attack();
	static void LoadRaidenModel();
	void Draw(Shader*ourShader);
	~Raiden();
};

