#pragma once
#include "Environment.h"

class Light : public Environment
{
	static Model*LightModel;
public:
	Light();
	static void LoadLightModel();
	void Draw(Shader*ourShader);
	~Light();
};

