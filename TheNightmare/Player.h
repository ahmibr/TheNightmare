#pragma once
#include "GameObject.h"

class Player : public GameObject
{
	Model GunModel;
	float playerHealth = 100.0f;
	glm::vec3 InitPos;
public:
	Player();
	void Draw(Shader*ourShader);
	void Move();
	bool reduceHealth(float hitPower);
	void Shoot(glm::vec4 proj, glm::vec4 view, float mouseX, float mouseY);
	~Player();
};

