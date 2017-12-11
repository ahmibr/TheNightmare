#include "Tree.h"

Model* Tree::TreeModel = NULL;

Tree::Tree()
{
	MinVertex = TreeModel->MinVertex;
	MaxVertex = TreeModel->MaxVertex;
	ObjectCenter = (MinVertex + MaxVertex) / glm::vec3(2);
	Environment::InitalizeEnvironmentPosition();
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