#pragma once
#include "GameObject.h"
#define ShootingTime 500
class Enemy : public GameObject
{
	float Health;
	bool Moving;
	const glm::vec3 PortalPos;

protected:
	void InitalizeEnemyPosition();
	float Objectheight;
	bool Direction;
	int Shooting;
	int HorizontalDistance;
	glm::vec3 LastMove;
public:
	Enemy();
	virtual void Move() = 0;
	void StartShooting();
	virtual Ray attack() = 0;
	virtual ~Enemy()=0;
	virtual glm::vec3 GetLastMove();
	virtual float GetRadius() = 0;
};

