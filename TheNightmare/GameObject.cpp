#include "GameObject.h"
#include "../include/learnopengl/model.h"

GameObject::GameObject(string const &path, glm::vec3 IniPos, glm::vec3 IniScale, bool gamma)
	:Model(path, gamma)
{
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	NumberOfInstances = 0;
	this->IniPos = IniPos;
	this->IniScale = IniScale;
}

void GameObject::AddInstance(int NumberOfAddedInstances)
{
	float Objectheight = 0;
	ObjectOCenter.push_back(ObjectCenter);
	MinOVertex.push_back(MinVertex);
	MaxOVertex.push_back(MaxVertex);
	NumberOfInstances += NumberOfAddedInstances;
	for (int i = 0; i < NumberOfAddedInstances; i++)
	{
		glm::mat4 AddedModel;
		AddedModel = glm::translate(AddedModel, -ObjectOCenter[NumberOfInstances -1]);
		AddedModel = glm::scale(AddedModel, IniScale);
		Objectheight = ((MinVertex.y + MaxVertex.y) / 2)*IniScale.x;
		MinOVertex[NumberOfInstances - 1] += -ObjectOCenter[NumberOfInstances - 1];
		MaxOVertex[NumberOfInstances - 1] += -ObjectOCenter[NumberOfInstances - 1];
		MinOVertex[NumberOfInstances - 1] *= IniScale.x;
		MaxOVertex[NumberOfInstances - 1] *= IniScale.x;
		AddedModel = glm::translate(AddedModel, glm::vec3(0.0f, Objectheight, 0.0f));
		MinOVertex[NumberOfInstances - 1] += glm::vec3(0.0f, Objectheight, 0.0f);
		MaxOVertex[NumberOfInstances - 1] += glm::vec3(0.0f, Objectheight, 0.0f);
		AddedModel = glm::translate(AddedModel, IniPos);
		MinOVertex[NumberOfInstances - 1] += IniPos;
		MaxOVertex[NumberOfInstances - 1] += IniPos;
		ModelMatrix.push_back(AddedModel);
		ObjectOCenter[NumberOfInstances - 1] = (MinOVertex[NumberOfInstances - 1] + MaxOVertex[NumberOfInstances - 1]) / glm::vec3(2);
	}
}


glm::mat4 GameObject::GetModelMatrix(int index)
{
	return ModelMatrix[index];
	
}

void GameObject::Translate(glm::vec3 tran, int index)
{
	ModelMatrix[index]= glm::translate( ModelMatrix[index], tran);
	MinOVertex[index] += tran;
	MaxOVertex[index] += tran;
	ObjectOCenter[index] = (MinOVertex[index] + MaxOVertex[index]) / glm::vec3(2);
}

GameObject::~GameObject()
{
}
