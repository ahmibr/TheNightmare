#pragma once
#include "Environment.h"

class Tree : public Environment
{
	static Model*TreeModel;
public:
	Tree();
	static void LoadTreeModel();
	void Draw(Shader*ourShader);
	~Tree();
};

