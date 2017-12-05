//#pragma once
#ifndef GO_H
#define GO_H
#include "../include/learnopengl/model.h"

enum objecttype {
	Sky, Floor, Wall, Gun, Tree, rock, Portal, Pika, Grim, Raiden, Donut, Alien, Wizard, EndofObjects
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

public:
	GameObject(string const &pathmaimaimaimai, glm::vec3 IniPos=PortalPos,glm::vec3 IniScale=glm::vec3(1.0f,1.0f,1.0f), bool gamma = false );
	void AddInstance(int NumberOfAddedInstances =1);
	glm::mat4 GetModelMatrix(int index);
	void Translate(glm::vec3 tran);
	 ~GameObject();
};
#endif


