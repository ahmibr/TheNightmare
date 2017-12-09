#include "Enemy.h"
#include <time.h>
int TimeLeft;

Enemy::Enemy(string const & path, glm::vec3 IniPos, glm::vec3 IniScale, bool gamma):GameObject(path,glm::vec3(35,0,0),IniScale,gamma)
{
	srand(time(NULL)); //Randomize seed initialization
	TimeLeft=rand() % 40 + 150;
}

void Enemy::Move()
{
	
}

int Enemy::GenerateEnemies()
{
	TimeLeft--;
	if (TimeLeft == 0)
	{
		TimeLeft = rand()%4000+1000;
		return rand() % 6;
	}
	else
		return -1;
}

Enemy::~Enemy()
{
}
