#pragma once
#include "GameObject.h"
#include <glm/gtx/euler_angles.hpp>//rotation
#include <glm/gtx/vector_angle.hpp>

class Player : public GameObject
{
	Model GunModel;
	float playerHealth;
	glm::vec3 InitPos;
	glm::vec3 up;
	float pitch;
	float yaw;
	float lastX;
	float lastY;
	bool first;
public:
	Player();
	void Draw(Shader*ourShader);
	void Move();
	void Translate(glm::vec3 tran);
	void moveWithCursor(const glm::mat4& LookAt);
	~Player();
};

