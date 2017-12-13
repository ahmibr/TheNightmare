#pragma once
#include "Environment.h"

class Sky : public Environment
{
	Model SkyModel;
public:
	Sky();
	void Draw(Shader*ourShader);
	~Sky();
};

