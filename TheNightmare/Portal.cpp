#include "Portal.h"

Portal::Portal() :PortalModel("../resources/objects/Portal/Portal.obj")
{
	MinVertex = PortalModel.MinVertex;
	MaxVertex = PortalModel.MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	Environment::InitalizeEnvironmentPosition();
	GameObject::Translate(glm::vec3(40.0f, 0.0f, 0.0f));
}

void Portal::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	PortalModel.Draw(*ourShader);
}


Portal::~Portal()
{
}