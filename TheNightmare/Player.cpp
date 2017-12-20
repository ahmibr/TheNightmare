#include "Player.h"


Player::Player():GunModel("../resources/objects/Gun/Gun.obj")
{
	MinVertex = GunModel.MinVertex;
	MaxVertex = GunModel.MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	InitPos = glm::vec3(-35.0f, 8.5f, 0.0f);
	GameObject::Translate(-ObjectCenter);
	GameObject::Translate(InitPos);
	//ModelMatrix = glm::translate(ModelMatrix, -ObjectCenter);
	//ModelMatrix = glm::translate(ModelMatrix,InitPos);
}

void Player::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	GunModel.Draw(*ourShader);
}

void Player::Move()
{

}

bool Player::reduceHealth(float hitPower)
{
	if (abs(hitPower - 0) <= EPSILON)
		return true;

	this->playerHealth -= hitPower;

	if (playerHealth < 0 || abs(playerHealth - 0) <= EPSILON)
		return false;
	return true;
}

void Player::Shoot(glm::vec4 proj, glm::vec4 view, float mouseX, float mouseY) {

}

Player::~Player()
{
}
