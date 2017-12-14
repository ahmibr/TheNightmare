#include "GameObject.h"
#include "../include/learnopengl/model.h"

GameObject::GameObject()
{ }

glm::vec3 GameObject::GetCenter()
{
	return ObjectCenter;
}

glm::vec3 GameObject::GetMinVertex()
{
	return MinVertex;
}

glm::vec3 GameObject::GetMaxVertex()
{
	return MaxVertex;
}

void GameObject::Move()
{ }

void GameObject::Translate(glm::vec3 tran)
{
	ModelMatrix= glm::translate( ModelMatrix, tran);
	MinVertex += tran;
	MaxVertex += tran;
	ObjectCenter += tran;
}

void GameObject::Rotate(glm::vec3 RotationAxes, float degree)
{
	ModelMatrix=glm::rotate(ModelMatrix, glm::radians(degree), RotationAxes);
	//glm::rotate(ObjectCenter, glm::radians(degree), RotationAxes);
}


GameObject::~GameObject()
{ }
