#include "Player.h"


Player::Player() :GunModel("../resources/objects/Gun/Gun.obj")
{
	lastX = 0;
	lastY = glm::radians(90.0f);
	first = true;
	up = glm::vec3(-1, 0, 0);
	pitch = 0;
	yaw = 0;
	MinVertex = GunModel.MinVertex;
	MaxVertex = GunModel.MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	InitPos = glm::vec3(-33.7f, 8.5f, 0.0f);
	//cout << ObjectCenter.x << " " << ObjectCenter.y << " " << ObjectCenter.z << endl;
	//GameObject::Translate(-ObjectCenter);
	GameObject::Translate(InitPos);
	playerHealth = 7000;
	//ModelMatrix = glm::rotate(ModelMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//ModelMatrix = glm::translate(ModelMatrix, -ObjectCenter);
	//ModelMatrix = glm::translate(ModelMatrix,InitPos);
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


// bool Player::reduceHealth(float hitPower)
// {
// 	if (abs(hitPower - 0) <= EPSILON)
// 		return true;

// 	this->playerHealth -= hitPower;

// 	if (playerHealth < 0 || abs(playerHealth - 0) <= EPSILON)
// 		return false;
// 	return true;
// }

// void Player::Shoot(glm::vec4 proj, glm::vec4 view, float mouseX, float mouseY) {

// }

void Player::moveWithCursor(const glm::mat4& LookAt) {

	//glm::mat3 mat(cameraFront, cameraSide, cameraUp);
	ModelMatrix = LookAt;
	ModelMatrix[0] *= -1;
	for (int i = 0; i < 3; ++i)
		swap(ModelMatrix[i][0], ModelMatrix[i][2]);
	//ModelMatrix[3][1] *= -1;
	ModelMatrix[3] = glm::vec4(glm::vec3(InitPos),1.0f);
	
	//cout << endl;
	///*for (int i = 0; i < 3; ++i)
	//	ModelMatrix[i][i] = cameraSide[i];
	//for (int i = 0; i < 3; ++i)
	//	ModelMatrix[1][i] = cameraUp[i];
	//for (int i = 0; i < 3; ++i)
	//	ModelMatrix[2][i] = cameraFront[i];
	//for (int i = 0; i < 3; ++i)
	//	ModelMatrix[3][i] = cameraPos[i];
	//ModelMatrix[0][3] = ModelMatrix[1][3] = ModelMatrix[2][3] = 0.0f;
	//ModelMatrix[3][3] = 1.0f;*/
	//ModelMatrix[0] = glm::vec4(cameraSide.z,cameraSide.y,cameraSide.x, 0.0f);
	//ModelMatrix[1] = glm::vec4(cameraUp.z,cameraUp.y,cameraUp.x, 0.0f);
	//ModelMatrix[2] = glm::vec4(cameraFront.z,cameraSide.y,cameraFront.x, 0.0f);
	//ModelMatrix[3] = glm::vec4(InitPos, 1.0f);

	//float angleY = glm::angle(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
	//float temp = angleY;
	//angleY -= lastY;
	//lastY = temp;
	//
	//float angleX = glm::angle(cameraFront, glm::vec3(1.0f, 0.0f, 0.0f));
	//if (cameraFront.z > 0)
	//	angleX *= -1;
	//temp = angleX;
	//angleX -= lastX;
	//lastX = temp;

	//ModelMatrix = glm::rotate(ModelMatrix, angleX, glm::vec3(0.0f, 1.0f, 0.0f));
	//ModelMatrix = glm::rotate(ModelMatrix, angleY, glm::vec3(1.0f, 0.0f, 0.0f));

	
	/*xoffset *= 0.1f;
	yoffset *= 0.1f;

	if (lastX + xoffset > 89.0f)
		xoffset = 0;
	if (lastX + xoffset < -89.0f)
		xoffset = 0;
	if (lastY + yoffset > 20.0f)
		yoffset = 0;
	if (lastY + yoffset < -10.0f)
		yoffset = 0;

	lastX += xoffset;
	lastY += yoffset;*/

}
void Player::Translate(glm::vec3 tran)
{
	ModelMatrix[3] += glm::vec4(tran, 0.0f);
	InitPos += tran;
	MinVertex += tran;
	MaxVertex += tran;
	/*glm::mat4 tanslate;
	tanslate = glm::translate(tanslate, tran);*/
	//ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	ObjectCenter += tran;
}
Player::~Player()
{
}


