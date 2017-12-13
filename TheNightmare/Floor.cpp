#include "Floor.h"

Floor::Floor():FloorModel("../resources/Objects/Floor/Floor.obj")
{
	MinVertex = FloorModel.MinVertex;
	MaxVertex = FloorModel.MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / 2.0f;
	GameObject::Translate(-ObjectCenter);
}

void Floor::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	FloorModel.Draw(*ourShader);
}


Floor::~Floor()
{
}