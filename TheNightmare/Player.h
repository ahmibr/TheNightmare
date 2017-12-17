#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	Model GunModel;
	float playerHealth;
	glm::vec3 InitPos;
public:
	Player();
	void Draw(Shader*ourShader);
	void Move();
	bool Dead();
	~Player();
};

