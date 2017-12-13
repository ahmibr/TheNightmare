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


Player::~Player()
{
}
