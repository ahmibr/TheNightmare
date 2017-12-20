#include "Light.h"

Model* Light::LightModel = NULL;

Light::Light()
{
	MinVertex = LightModel->MinVertex;
	MaxVertex = LightModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	//Environment::InitalizeEnvironmentPosition();
	GameObject::Translate(glm::vec3(0.0f, 15.0f, 0.0f));
}

void Light::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	LightModel->Draw(*ourShader);
}

void Light::LoadLightModel()
{
	LightModel = new Model("../resources/objects/Light/Light.obj");
}


Light::~Light()
{
}