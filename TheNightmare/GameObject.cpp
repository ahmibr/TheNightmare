#include "GameObject.h"
#include "../include/learnopengl/model.h"

GameObject::GameObject()
{
	/*ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);*/
	/*NumberOfInstances = 0;
	this->IniPos = IniPos;
	this->IniScale = IniScale;*/
}

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

//void GameObject::AddInstance(int NumberOfAddedInstances)
//{
//	float Objectheight = 0;
//	NumberOfInstances += NumberOfAddedInstances;
//	for (int i = 0; i < NumberOfAddedInstances; i++)
//	{
//		glm::mat4 AddedModel;
//		AddedModel = glm::translate(AddedModel, -ObjectCenter);
//		AddedModel = glm::scale(AddedModel, IniScale);
//		Objectheight = ((MinVertex.y + MaxVertex.y) / 2)*IniScale.x;
//		MinVertex += -ObjectCenter;
//		MaxVertex += -ObjectCenter;
//		AddedModel = glm::translate(AddedModel, glm::vec3(0.0f, Objectheight, 0.0f));
//		MinVertex += glm::vec3(0.0f, Objectheight, 0.0f);
//		MaxVertex += glm::vec3(0.0f, Objectheight, 0.0f);
//		AddedModel = glm::translate(AddedModel, IniPos);
//		MinVertex += IniPos;
//		MaxVertex += IniPos;
//		ModelMatrix.push_back(AddedModel);
//		ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
//	}
//}


//glm::mat4 GameObject::GetModelMatrix(int index)
//{
//	return ModelMatrix[index];
//	
//}

void GameObject::Move()
{
}

void GameObject::Translate(glm::vec3 tran)
{
	ModelMatrix= glm::translate( ModelMatrix, tran);
	MinVertex += tran;
	MaxVertex += tran;
	/*glm::mat4 tanslate;
	tanslate = glm::translate(tanslate, tran);*/
	//ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	ObjectCenter += tran;
}


GameObject::~GameObject()
{
}
