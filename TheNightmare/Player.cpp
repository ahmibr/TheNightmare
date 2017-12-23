#include "Player.h"


Player::Player() :GunModel("../resources/objects/Gun/Gun.obj")
{
	MinVertex = GunModel.MinVertex;
	MaxVertex = GunModel.MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	InitPos = glm::vec3(-35.0f, 8.5f, 0.0f);
	//GameObject::Translate(-ObjectCenter);
	GameObject::Translate(InitPos);
	playerHealth = 7000;
}

void Player::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	GunModel.Draw(*ourShader);
	//playerHealth--;
}

void Player::Move()
{
}

void Player::reducehealth(float dec)
{
	playerHealth -= dec;
	cout << playerHealth << endl;
}
float Player::GetRadius()
{
	return GunModel.radius + 10.0f;
}


bool Player::Dead()
{
	return (playerHealth > 0) ? 0 : 1;
}

void Player::moveWithCursor(const glm::mat4& LookAt) {
	ModelMatrix = LookAt;
	ModelMatrix[0] *= -1;
	for (int i = 0; i < 3; ++i)
		swap(ModelMatrix[i][0], ModelMatrix[i][2]);
	ModelMatrix[3] = glm::vec4(glm::vec3(InitPos), 1.0f);

}
void Player::Translate(glm::vec3 tran)
{
	ModelMatrix[3] += glm::vec4(tran, 0.0f);
	InitPos += tran;
	MinVertex += tran;
	MaxVertex += tran;
	ObjectCenter += tran;
}

Player::~Player()
{
}
