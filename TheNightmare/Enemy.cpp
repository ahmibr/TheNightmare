#include "Enemy.h"
#include <time.h>


Enemy::Enemy():PortalPos(glm::vec3(35.0f,0.0f,0.0f))
{
	srand(time(NULL));
	Direction = rand() % 2;
	HorizontalDistance = rand() % 500 + 700 + rand()%600;
}

void Enemy::InitalizeEnemyPosition()
{
	GameObject::Translate(-ObjectCenter);
	float Objectheight = 0;
	Objectheight = ((abs(MinVertex.y) + abs(MaxVertex.y)) / 2.0f)/**IniScale.x*/;
	GameObject::Translate(glm::vec3(0.0f, Objectheight + 0.3 , 0.0f));
	GameObject::Translate(PortalPos);	
}

Enemy::~Enemy()
{
}
