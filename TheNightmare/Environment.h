#pragma once
#include "GameObject.h"
class Environment : public GameObject
{
protected:
	void InitalizeEnvironmentPosition();
public:
	Environment();
	virtual bool CheckForHit(glm::vec3 campos);
	virtual float GetRadius();
	virtual void throwRock(glm::vec3 campos);
	~Environment();

};