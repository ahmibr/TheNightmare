//#pragma once
#ifndef GO_H
#define GO_H
#include "../include/learnopengl/model.h"

//
//enum objecttype {
//	Sky, Tree, Tree, Gun, Tree, rock, Portal, Pika, Grim, Raiden, Donut, Tree, Cacodemon, EndofObjects
//};

class GameObject
{
protected:
	glm::mat4 ModelMatrix;
	//glm::vec3 IniPos;
	//glm::vec3 IniScale;
	glm::vec3 ObjectCenter;
	glm::vec3 MinVertex;
	glm::vec3 MaxVertex;
	static 	vector<vector<vector<pair<GameObject*,int>>>> SceneGraph;
	int Gz;
	int Gy;
	int index;
	glm::vec3 lasttrans; //to check for its validity and if not valid, reverse it
	//int NumberOfInstances;
	static float skyradius;
	float Myradius;

public:
	GameObject();
	//void AddInstance(int NumberOfAddedInstances =1);
	//glm::mat4 GetModelMatrix(int index);
	glm::vec3 GetCenter();
	glm::vec3 GetMinVertex();
	glm::vec3 GetMaxVertex();
	virtual void Draw(Shader*ourShader) = 0;
	virtual void Move();
	void Translate(glm::vec3 tran);
	void Rotate(glm::vec3 RotationAxes, float degree);
	virtual ~GameObject()=0;

	static void AddToSceneG(GameObject* o, int rock=0); //rock=1, tree=2
	static void InitializeScene();
	void CalculateGraphIndex();
	void CheckMoveValidity();
	bool CheckCollision(GameObject* o,float &r);
	static void RemoveFromSG(GameObject*o);
	static void SetSR(glm::vec3 diff);

};
#endif


