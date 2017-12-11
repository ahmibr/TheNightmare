#include "Environment.h"

Environment::Environment()
{

}

void Environment::InitalizeEnvironmentPosition()
{
	GameObject::Translate(-ObjectCenter);
	float Objectheight = 0;
	Objectheight = ((abs(MinVertex.y) + abs(MaxVertex.y)) / 2.0f)/**IniScale.x*/;
	GameObject::Translate(glm::vec3(0.0f, Objectheight + 0.3, 0.0f));
}

Environment::~Environment()
{
}
