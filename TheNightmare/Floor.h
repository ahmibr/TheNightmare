#pragma once
#include "Environment.h"

class Floor : public Environment
{
	Model FloorModel;
public:
	Floor();
	void Draw(Shader*ourShader);
	~Floor();
};