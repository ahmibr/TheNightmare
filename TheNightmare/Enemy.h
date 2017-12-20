#pragma once
#include "GameObject.h"
#define ShootingTime 500
class Enemy : public GameObject
{
	float Health;
	bool Moving;
	const glm::vec3 PortalPos;
	virtual void Move() = 0;
protected:
	void InitalizeEnemyPosition();
	float Objectheight;
	bool Direction;
	int Shooting;
	int HorizontalDistance;
public:
	Enemy();
	void StartShooting();
	virtual ~Enemy()=0;
};

