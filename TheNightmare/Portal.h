#pragma once
#include "Environment.h"

class Portal : public Environment
{
	Model PortalModel;
public:
	Portal();
	void Draw(Shader*ourShader);
	~Portal();
};