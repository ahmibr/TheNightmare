#pragma once
#include "Environment.h"

class Wall : public Environment
{
	Model WallModel;
public:
	Wall();
	void Draw(Shader*ourShader);
	~Wall();
};

