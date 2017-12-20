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
	void throwRock(float speed, float angle);
	void Draw(Shader*ourShader);
	~Rocks();
};

