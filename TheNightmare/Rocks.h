#pragma once
#include "Environment.h"

class Rocks : public Environment
{
	static Model*RocksModel;
public:
	Rocks();
	static void LoadRocksModel();
	void Draw(Shader*ourShader);
	~Rocks();
};

