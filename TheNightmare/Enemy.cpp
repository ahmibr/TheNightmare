#include "Enemy.h"


Enemy::Enemy():PortalPos(glm::vec3(35.0f,0.0f,0.0f))
{
	
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
