#include "Tree.h"

Model* Tree::TreeModel = NULL;

Tree::Tree()
{
	MinVertex = TreeModel->MinVertex;
	MaxVertex = TreeModel->MaxVertex;
	glm::vec3 diff = (MinVertex - MaxVertex) / glm::vec3(2);
	Myradius = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	Environment::InitalizeEnvironmentPosition();
	CalculateGraphIndex();
	AddToSceneG(this);
}

void Tree::Draw(Shader*ourShader)
{
	ourShader->setMat4("model", ModelMatrix);
	TreeModel->Draw(*ourShader);
}

void Tree::LoadTreeModel()
{
	TreeModel = new Model("../resources/objects/Tree/Tree.obj");
}


Tree::~Tree()
{
}