#include "Player.h"


Player::Player():GunModel("../resources/objects/Gun/Gun.obj")
{
	MinVertex = GunModel.MinVertex;
	MaxVertex = GunModel.MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	InitPos = glm::vec3(-35.0f, 8.5f, 0.0f);
	GameObject::Translate(-ObjectCenter);
	GameObject::Translate(InitPos);
	playerHealth = 7000;
}

void Player::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	GunModel.Draw(*ourShader);
	playerHealth--;
}

void Player::Move()
{

}

// void Player::Shoot(glm::vec4 proj, glm::vec4 view, float mouseX, float mouseY) {

// }
bool Player::Dead()
{
	return (playerHealth > 0) ? 0:1;
}


Player::~Player()
{
}
