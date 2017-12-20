#pragma once
#include "Environment.h"

#define PI 3.141592653589793
#define G 9.8

class Rocks : public Environment
{
	static Model*RocksModel;
	glm::vec3 intialPos = GetCenter();
	float Vo;
	float theta;
	bool inAir = false;
	void move();
public:
	Rocks();
	static void LoadRocksModel();
	void throwRock(glm::vec3 campos);
	void Draw(Shader*ourShader);
	bool CheckForHit(glm::vec3 campos);
	void computeIntialVilocity(glm::vec3 campos);
	~Rocks();
};

