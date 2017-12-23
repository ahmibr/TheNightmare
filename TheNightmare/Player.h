#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	Model GunModel;
	float playerHealth;
	glm::vec3 InitPos;
public:
	Player();
	void Translate(glm::vec3 tran);
	void moveWithCursor(const glm::mat4& LookAt);
	void Draw(Shader*ourShader);
	void Move();
	float GetRadius();
	bool Dead();
	void reducehealth(float dec);
	~Player();
};

