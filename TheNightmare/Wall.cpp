#include "Wall.h"

Wall::Wall():WallModel("../resources/Objects/Wall/Wall.obj")
{
	MinVertex = WallModel.MinVertex;
	MaxVertex = WallModel.MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	Environment::InitalizeEnvironmentPosition();
	GameObject::Translate(glm::vec3(-35.0f, -0.3f, 0.0f));
}

void Wall::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	WallModel.Draw(*ourShader);
}


Wall::~Wall()
{
}