#pragma once
#include "GameObject.h"

class Enemy :public GameObject
{
public:
	Enemy(string const &path, glm::vec3 IniPos = PortalPos, glm::vec3 IniScale = glm::vec3(1.0f, 1.0f, 1.0f), bool gamma = false);
	virtual void Move();
	static int GenerateEnemies();
	~Enemy();
};

