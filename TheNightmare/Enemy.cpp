#include "Enemy.h"
#include <time.h>


Enemy::Enemy():PortalPos(glm::vec3(35.0f,0.0f,0.0f))
{
	srand(time(NULL));
	Direction = rand() % 2;
	HorizontalDistance = rand() % 6;
	switch (HorizontalDistance)
	{
	case 0:
		HorizontalDistance = 100;
		break;
	case 1:
		HorizontalDistance = 150;
		break;
	case 2:
		HorizontalDistance = 200;
		break;
	case 3:
		HorizontalDistance = 250;
		break;
	case 4:
		HorizontalDistance = 350;
		break;
	case 5:
		HorizontalDistance = 400;
		break;

	default:
		break;
	}
	Shooting = 0;
}

void Enemy::StartShooting()
{
	Shooting = ShootingTime;
}

void Enemy::InitalizeEnemyPosition()
{
	GameObject::Translate(-ObjectCenter);
	Objectheight = ((abs(MinVertex.y) + abs(MaxVertex.y)) / 2.0f)/**IniScale.x*/;
	GameObject::Translate(glm::vec3(0.0f, Objectheight + 0.3 , 0.0f));
	GameObject::Translate(PortalPos);	
}

Enemy::~Enemy()
{
}
