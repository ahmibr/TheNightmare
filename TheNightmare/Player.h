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
	//void Shoot(glm::vec4 proj, glm::vec4 view, float mouseX, float mouseY);
	bool Dead();
	~Player();
};

