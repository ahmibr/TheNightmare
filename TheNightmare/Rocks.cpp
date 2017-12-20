#include "Rocks.h"

Model* Rocks::RocksModel = NULL;

Rocks::Rocks()
{
	MinVertex = RocksModel->MinVertex;
	MaxVertex = RocksModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	Environment::InitalizeEnvironmentPosition();
}

void Rocks::Draw(Shader*ourShader)
{
	move();
	ourShader->setMat4("model", ModelMatrix);
	RocksModel->Draw(*ourShader);
}

void Rocks::throwRock(float speed, float angle) {
	Vo = speed;
	theta = angle;
	intialPos = GetCenter();
	inAir = true;
}

void Rocks::move() {
	if (!inAir)
		return;

	int d = int(round(pow(Vo, 2) * sin(2 * theta * PI / 180) / G));
	glm::vec3 center = GetCenter();
	float r = sqrt(pow((center.x - intialPos.x), 2) + pow((center.y - intialPos.y), 2) + pow((center.z - intialPos.z), 2));
	float y = center.y - intialPos.y;
	float u = sqrt(r*r - y*y);

	if (d == int(round(u))) {
		glm::vec3 correction = glm::vec3(center.x, intialPos.y, center.z);
		Translate(-center);
		Translate(correction);
		intialPos = GetCenter();
		inAir = !inAir;
	}

	u = u + 0.1;
	float a = tan(theta * PI / 180);
	float b = G / (2 * pow(Vo, 2) * pow(cos(theta * PI / 180), 2));
	float dy = (a - 2 * b * u) * 0.1;
	Translate(-center);
	Translate(glm::vec3(-0.1f, dy, 0.0f));
	Translate(center);
}

void Rocks::LoadRocksModel()
{
	RocksModel = new Model("../resources/objects/Rocks/Rocks.obj");
}


Rocks::~Rocks()
{
}