//#pragma once
#ifndef GO_H
#define GO_H
#include "../include/learnopengl/model.h"
#define EPSILON 0.00001
//
//enum objecttype {
//	Sky, Tree, Tree, Gun, Tree, rock, Portal, Pika, Grim, Raiden, Donut, Tree, Cacodemon, EndofObjects
//};

struct Ray {
	glm::vec3 lo;
	glm::vec3 dir;
	Ray(glm::vec3 lo, glm::vec3 dir) {
		this->lo = lo;
		this->dir = dir;
	}
};

class GameObject
{
protected:
	glm::mat4 ModelMatrix;
	//glm::vec3 IniPos;
	//glm::vec3 IniScale;
	glm::vec3 ObjectCenter;
	glm::vec3 MinVertex;
	glm::vec3 MaxVertex;
	bool intersectPlaneX(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float x, Ray bullet);
	bool intersectPlaneY(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float y, Ray bullet);
	bool intersectPlaneZ(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, float z, Ray bullet);
	bool intersectPlane(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d, int flag, float value, Ray bullet);
	//int NumberOfInstances;

public:
	GameObject();
	//void AddInstance(int NumberOfAddedInstances =1);
	//glm::mat4 GetModelMatrix(int index);
	glm::vec3 GetCenter();
	glm::vec3 GetMinVertex();
	glm::vec3 GetMaxVertex();
	bool rayCast(Ray bullet);
	virtual void Draw(Shader*ourShader) = 0;
	virtual void Move();
	void Translate(glm::vec3 tran);
	void Rotate(glm::vec3 RotationAxes, float degree);
	virtual ~GameObject()=0;
};
#endif


