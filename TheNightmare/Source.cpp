#include <iostream>
#include "GameManager.h"


int main()
{
	GameManager TheNightmare;


	if(!TheNightmare.Start())
		return -1;

	TheNightmare.GameLoop();

	return 0;
}
