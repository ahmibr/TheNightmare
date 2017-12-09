//#pragma once
#ifndef GO_H
#define GO_H
#include "../include/learnopengl/model.h"

enum objecttype {
	Sky, Floor, Wall, Gun, Tree, Portal, rock,  Pika, Grim, Raiden, Donut, Alien, Wizard, EndofObjects
};
const glm::vec3 PortalPos = glm::vec3(0, 0, 0);

class GameObject: public Model
{
	vector<glm::mat4> ModelMatrix;

	glm::vec3 IniPos;
	glm::vec3 IniScale;
public:
	glm::vec3 ObjectCenter;
	int NumberOfInstances;
	vector<glm::vec3> ObjectOCenter;
	vector<glm::vec3> MinOVertex;
	vector<glm::vec3> MaxOVertex;

public:
	GameObject(string const &path, glm::vec3 IniPos=PortalPos,glm::vec3 IniScale=glm::vec3(1.0f,1.0f,1.0f), bool gamma = false );
	void AddInstance(int NumberOfAddedInstances =1);
	glm::mat4 GetModelMatrix(int index);
	void Translate(glm::vec3 tran,int index=0);
	virtual void Move();
	 ~GameObject();
};
#endif


