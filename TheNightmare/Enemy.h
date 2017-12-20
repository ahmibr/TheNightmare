#pragma once
#include "GameObject.h"
class Enemy : public GameObject
{
	float Health;
	bool Moving;
	const glm::vec3 PortalPos;
	virtual void Move() = 0;
protected:
	void InitalizeEnemyPosition();
	bool Direction;
	int HorizontalDistance;
public:
	Enemy();
	virtual Ray attack()=0;
	//void throwRock(GameObject* rock);
	virtual ~Enemy()=0;

};

