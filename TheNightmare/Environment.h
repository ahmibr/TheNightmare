#pragma once
#include "GameObject.h"
class Environment : public GameObject
{
protected:
	void InitalizeEnvironmentPosition();
public:
	Environment();
	~Environment();
};