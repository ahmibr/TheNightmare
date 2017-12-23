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

void Rocks::throwRock(glm::vec3 campos) {
	intialPos = GetCenter();
	inAir = true;
	computeIntialVilocity(campos);
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



void Rocks::computeIntialVilocity(glm::vec3 campos) {
	theta = 30.0f; //choose any angle you want it doesn't matter i choose 30 becuase i like this angle xD
	float x = campos.x; //replace zeros with values you have for both x and y
	float y = campos.y;

	Vo = sqrt((9.8 * abs(x*x)) / (2 * (tan(theta * PI / 180) * abs(x) - y) * pow(cos(theta * PI / 180), 2)));
}

void Rocks::LoadRocksModel()
{
	RocksModel = new Model("../resources/objects/Rocks/Rocks.obj");
}

bool Rocks::CheckForHit(glm::vec3 campos)
{
	glm::vec3 diff = abs(ObjectCenter - campos);
	glm::vec3 sumofcenters = (abs(ObjectCenter - MaxVertex) + glm::vec3(1, 1, 1));

	if (diff.x <= sumofcenters.x&&diff.z <= sumofcenters.z&&diff.y <= sumofcenters.y)
	{
		cout << "ROCK HIT MEEEE";
		return true;

	}

	return false;

}
float Rocks::GetRadius()
{
	return RocksModel->radius;
}


Rocks::~Rocks()
{
}