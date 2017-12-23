#include "GameManager.h"

Camera camera(glm::vec3(0, 10, 0)); //up in y front in x
Player* GamePlayer;
glm::vec3 CameraGunOffset = glm::vec3(0.0f, 0.25f, 0.0f);
float lastX;
float lastY;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int GameManager::Menus = 0;

GameManager::GameManager()
{
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

	srand(time(NULL)); //Randomize seed initialization
	TimeLeft = rand() % 40 + 150;

	NumberOfTotalEnemies = 0;
	Menus = 701;

	for (int i = 0; i < 4; i++)
		MenusArray[i] = NULL;
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void GameManager::processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
		GamePlayer->Translate(glm::vec3(0, 0, camera.Position.z - GamePlayer->GetCenter().z - CameraGunOffset.z));
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
		GamePlayer->Translate(glm::vec3(0, 0, camera.Position.z - GamePlayer->GetCenter().z - CameraGunOffset.z));
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && shootingDelay <= 0) {
		shootingDelay = 100;
		int topIndex = -1;
		float topValue = 100.0f;
		if (EnemyList.size() > 0) {
			Ray bullet(camera.Position - glm::vec3(0, 5, 0), camera.Front);
			for (int i = 0; i < EnemyList.size(); ++i) {

				if (EnemyList[i]->rayCast(bullet)) {
					if (EnemyList[i]->getMaxX() < topValue) {
						topIndex = i;
						topValue = EnemyList[i]->getMaxX();
					}
					/*EnemyList.erase(EnemyList.begin() + i);
					--i;*/
				}
			}
		}
		if (topIndex != -1)
			EnemyList.erase(EnemyList.begin() + topIndex);
	}
}

void GameManager::LoadAllModels()
{
	GamePlayer = new Player;
	GameSky = new Sky;
	GameFloor = new Floor;
	GameWall = new Wall;
	GamePortal = new Portal;
	MenusArray[0] = new Model("../resources/objects/Menus/mainmenu.obj");
	MenusArray[1] = new Model("../resources/objects/Menus/Loading.obj");
	MenusArray[2] = new Model("../resources/objects/Menus/YouWin.obj");
	MenusArray[3] = new Model("../resources/objects/Menus/GameOver.obj");
	Rocks::LoadRocksModel();
	Tree::LoadTreeModel();
	Rocks::LoadRocksModel();

	for (int i = 0; i < 12; i += 2)
	{
		ObstaclesList.push_back(new Tree);
		ObstaclesList[ObstaclesList.size() - 1]->Translate(glm::vec3(-10 + 4 * i, 0, 25));
		ObstaclesList.push_back(new Tree);
		ObstaclesList[ObstaclesList.size() - 1]->Translate(glm::vec3(-10 + 4 * i, 0, -25));
	}
	MinAvaliableSpace = glm::vec3(-10, 0, -25);
	MinAvaliableSpace.z += (ObstaclesList[0]->GetMaxVertex().z - ObstaclesList[0]->GetMinVertex().z) / 2;
	MaxAvaliableSpace = glm::vec3(30, 0, 25);
	MaxAvaliableSpace.z -= (ObstaclesList[0]->GetMaxVertex().z - ObstaclesList[0]->GetMinVertex().z) / 2;
	Cacodemon::LoadCacodemonModel();
	Raiden::LoadRaidenModel();
	Pika::LoadPikaModel();
	Alien::LoadAlienModel();
	Dounat::LoadDounatModel();
	GrimReaper::LoadGrimModel();
	Light::LoadLightModel();
	LightArray = new Light[3];
	LightArray[0].Translate(glm::vec3(0.0f, 0.0f, 10.0f));
	LightArray[1].Translate(glm::vec3(0.0f, 0.0f, -10.0f));
	LightArray[2].Translate(glm::vec3(-10.0f, 0.0f, 0.0f));

	GenerateObstacles();

}

void GenerateRocks(int numRocks) {
	srand(time(NULL));
	float r;

	for (int i = 0; i < numRocks; i++)
	{
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	}
}

void GameManager::GenerateEnemies()
{
	TimeLeft--;
	bool Ok = false;
	int Loops = 0;
	if (TimeLeft == 0)
	{
		TimeLeft = rand() % 400 + 225;
		while (!Ok)
		{
			switch (rand() % 6)
			{
			case 0:
				if (Alien::GetNumberOfAliens() == 0 || ((EnemyList.size() / 2) <= EnemyList.size() / Alien::GetNumberOfAliens() && PreviousEnemy != 0 && PrevPreviousEnemy != 0))
				{
					Ok = true;
					EnemyList.push_back(new Alien);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 0;
				}
				else
					Loops++;
				break;
			case 1:
				if (Dounat::GetNumberOfDounats() == 0 || ((EnemyList.size() / 2) <= EnemyList.size() / Dounat::GetNumberOfDounats() && PreviousEnemy != 1 && PrevPreviousEnemy != 1))
				{
					Ok = true;
					EnemyList.push_back(new Dounat);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 1;
				}
				else
					Loops++;
				break;
			case 2:
				if (GrimReaper::GetNumberOfGrims() == 0 || ((EnemyList.size() / 2) <= EnemyList.size() / GrimReaper::GetNumberOfGrims() && PreviousEnemy != 2 && PrevPreviousEnemy != 2))
				{
					Ok = true;
					EnemyList.push_back(new GrimReaper);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 2;
				}
				else
					Loops++;
				break;
			case 3:
				if (Pika::GetNumberOfPikas() == 0 || ((EnemyList.size() / 2) <= EnemyList.size() / Pika::GetNumberOfPikas() && PreviousEnemy != 3 && PrevPreviousEnemy != 3))
				{
					Ok = true;
					EnemyList.push_back(new Pika);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 3;
				}
				else
					Loops++;
				break;
			case 4:
				if (Raiden::GetNumberOfRaidens() == 0 || ((EnemyList.size() / 2) <= EnemyList.size() / Raiden::GetNumberOfRaidens() && PreviousEnemy != 4 && PrevPreviousEnemy != 4))
				{
					Ok = true;
					EnemyList.push_back(new Raiden);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 4;
				}
				else
					Loops++;
				break;
			case 5:
				if (Cacodemon::GetNumberOfCacodemons() == 0 || ((EnemyList.size() / 2) <= EnemyList.size() / Cacodemon::GetNumberOfCacodemons() && PreviousEnemy != 5 && PrevPreviousEnemy != 5))
				{
					Ok = true;
					EnemyList.push_back(new Cacodemon);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 5;
				}
				else
					Loops++;
				break;
			default:
				break;
			}
			if (Loops == 50)
			{
				switch (rand() % 6)
				{
				case 0:
					EnemyList.push_back(new Alien);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 0;
					break;
				case 1:
					EnemyList.push_back(new Dounat);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 1;
					break;
				case 2:
					EnemyList.push_back(new GrimReaper);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 2;
					break;
				case 3:
					EnemyList.push_back(new Pika);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 3;
					break;
				case 4:
					EnemyList.push_back(new Raiden);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 4;
					break;
				case 5:
					EnemyList.push_back(new Cacodemon);
					PrevPreviousEnemy = PreviousEnemy;
					PreviousEnemy = 5;
					break;
				}

				Ok = true;
			}

		}
		NumberOfTotalEnemies++;
		//ObstaclesList.erase(ObstaclesList.begin() + 14);
		//GenerateObstacles();
	}

}

void GameManager::GenerateObstacles()
{
	float x, z, MaxX, MinX, MinZ, MaxZ;
	while (ObstaclesList.size() != 22)
	{
		cout << "Generate" << endl;
		x = (rand() % (int)MaxAvaliableSpace.x)*((rand() % 2) ? 1 : -1);
		z = (rand() % (int)MaxAvaliableSpace.z)*((rand() % 2) ? 1 : -1);
		int i = 0;
		for (i = 0; i < EnemyList.size(); i++)
		{
			MaxX = EnemyList[i]->GetCenter().x + (EnemyList[i]->GetMaxVertex().x - EnemyList[i]->GetMinVertex().x) / 2.0f;
			MinX = EnemyList[i]->GetCenter().x - (EnemyList[i]->GetMaxVertex().x - EnemyList[i]->GetMinVertex().x) / 2.0f;
			MaxZ = EnemyList[i]->GetCenter().z + (EnemyList[i]->GetMaxVertex().z - EnemyList[i]->GetMinVertex().z) / 2.0f;
			MinZ = EnemyList[i]->GetCenter().z - (EnemyList[i]->GetMaxVertex().z - EnemyList[i]->GetMinVertex().z) / 2.0f;
			if (!((x > MinX || x<MaxX) && (z>MinZ || z < MaxZ)))
				break;
		}
		int j = 12;
		for (j = 12; j < ObstaclesList.size(); j++)
		{
			MaxX = ObstaclesList[j]->GetCenter().x + (ObstaclesList[j]->GetMaxVertex().x - ObstaclesList[j]->GetMinVertex().x) / 2.0f;
			MinX = ObstaclesList[j]->GetCenter().x - (ObstaclesList[j]->GetMaxVertex().x - ObstaclesList[j]->GetMinVertex().x) / 2.0f;
			MaxZ = ObstaclesList[j]->GetCenter().z + (ObstaclesList[j]->GetMaxVertex().z - ObstaclesList[j]->GetMinVertex().z) / 2.0f;
			MinZ = ObstaclesList[j]->GetCenter().z - (ObstaclesList[j]->GetMaxVertex().z - ObstaclesList[j]->GetMinVertex().z) / 2.0f;
			if (!((x > MinX || x<MaxX) && (z>MinZ || z < MaxZ)))
				break;
		}


		if (i == EnemyList.size() && j == ObstaclesList.size())
		{
			ObstaclesList.push_back(new Rocks);
			ObstaclesList[ObstaclesList.size() - 1]->Translate(glm::vec3(x, 0, z));
		}
	}
	cout << "New "<<ObstaclesList.size() << endl;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void GameManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void GameManager::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	if (Menus == 0)
	{
		GamePlayer->moveWithCursor(camera.GetViewMatrix());
		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void GameManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


bool GameManager::Start()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit(); //initialize GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Set Version 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	//window = glfwCreateWindow(mode->width, mode->height, "TheNightmare", monitor, NULL);
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "TheNightmare", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window); //Set Current context to window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Set funtion to call when change happens to framebuffer
	glfwSetCursorPosCallback(window, mouse_callback); //change in cursor
	glfwSetScrollCallback(window, scroll_callback); // change when scroll

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers --- depeds on os
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	ourShader = new Shader("../shaders/1.model_loading.vs", "../shaders/Lighting.fs");

	// load models
	LoadAllModels();

	rock = new Rocks();
	rock->Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	//Set up Camera Position depending on GUN
	/////////////////////
	camera.SetCameraPosition(GamePlayer->GetCenter() + CameraGunOffset);
	//Declare camera moving space limits, Tree length
	/////////////////////
	camera.MinSpace = GameWall->GetMinVertex().z + 1;
	camera.MaxSpace = GameWall->GetMaxVertex().z - 1;
	ourShader->use();
	ourShader->setInt("material.diffuse", 0);
	ourShader->setInt("material.specular", 1);

	//rock->throwRock(camera.Position);
	return true;

}

void GameManager::GameLoop()
{

	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//enable shader before setting uniforms
		ourShader->use();

		shootingDelay--;
		SetLighting();

		// view/projection transformations
		if (GamePlayer->Dead())(camera.resetCamera());
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader->setMat4("projection", projection);
		ourShader->setMat4("view", view);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------

		if (Menus > 0)
		{
			ourShader->setInt("la", 1);
			glm::mat4 modelmatrix;
			modelmatrix = glm::translate(modelmatrix, glm::vec3(0.3f, 0.0f, 0.0f));
			ourShader->setMat4("model", modelmatrix);
			if (Menus >= 700)
				MenusArray[0]->Draw(*ourShader);

			if (Menus == 701)
			{
				mciSendString("open \"../resources/sounds/MainMenu.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
				mciSendString("play mp3 repeat", NULL, 0, NULL);
				Menus--;
			}

			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				//mciSendString("stop mp3", NULL, 0, NULL);
				Menus--;
			}
			else
				if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
					return;
			if (Menus < 700)
			{
				MenusArray[1]->Draw(*ourShader);
				Menus--;
			}

			if (Menus == 0)
			{
				delete MenusArray[1];
				delete MenusArray[0];
			}
		}
		else if (GamePlayer->Dead())
		{
			ourShader->setInt("la", 1);
			glm::mat4 modelmatrix;
			ourShader->setMat4("model", modelmatrix);
			MenusArray[3]->Draw(*ourShader);
			Menus--;
			if (Menus == -10000)
				return;
		}
		else if (NumberOfTotalEnemies == 20 && EnemyList.empty())
		{
			ourShader->setInt("la", 1);
			glm::mat4 modelmatrix;
			ourShader->setMat4("model", modelmatrix);
			MenusArray[2]->Draw(*ourShader);
			Menus--;
			if (Menus == -10000)
				return;
		}
		else
		{
			ourShader->setInt("la", 0);

			GameSky->Draw(ourShader);
			GamePlayer->Draw(ourShader);
			GameFloor->Draw(ourShader);
			GameWall->Draw(ourShader);
			GamePortal->Draw(ourShader);
			//rock->Draw(ourShader);
			float playerHit = 0.0f;
			for (int i = 0; i < EnemyList.size(); i++) {
				if (GameWall->rayCast(EnemyList[i]->attack()))
					playerHit += 0.01f;
				if (GamePlayer->rayCast(EnemyList[i]->attack()))
					playerHit += 0.1f;
			}
			
			//if (!GamePlayer->reduceHealth(playerHit)) {
			//	cout << "game over!!!" << endl;
				//return;
			//}

			LightArray[0].Draw(ourShader);
			LightArray[1].Draw(ourShader);
			LightArray[2].Draw(ourShader);

			rock->CheckForHit(camera.Position);

			for (int i = 0; i < ObstaclesList.size(); i++)
			{
				ObstaclesList[i]->Draw(ourShader);
				if (ObstaclesList[i]->CheckForHit(camera.Position))
				{
					GamePlayer->reducehealth(40);
					ObstaclesList.erase(ObstaclesList.begin() + i);
					cout << ObstaclesList.size() << endl;
					GenerateObstacles();
				}

			}

			if (NumberOfTotalEnemies < 20)
				GenerateEnemies();

			for (int i = 0; i < EnemyList.size(); i++)
			{
				EnemyList[i]->Move();
				EnemyList[i]->Draw(ourShader);
				CollisionDetection(EnemyList[i], i);

			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void GameManager::SetLighting()
{
	// be sure to activate shader when setting uniforms/drawing objects
	ourShader->use();
	ourShader->setVec3("viewPos", camera.Position);
	ourShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	ourShader->setFloat("material.shininess", 64.0f);
	//Set Directional Lighting-------------------------------------------------
	ourShader->setVec3("dirLight.direction", 0, 40, 0);
	ourShader->setVec3("dirLight.ambient", 0.02f, 0.02f, 0.02f);
	ourShader->setVec3("dirLight.diffuse", 0.03f, 0.03f, 0.03f);
	ourShader->setVec3("dirLight.specular", 0.0f, 0.0f, 0.0f);

	ourShader->setVec3("spotLights[0].position", 35, 24, 0);
	ourShader->setVec3("spotLights[0].direction", 0.2, -1, 0);
	ourShader->setFloat("spotLights[0].cutOff", glm::cos(glm::radians(12.5f)));
	ourShader->setFloat("spotLights[0].outerCutOff", glm::cos(glm::radians(17.5f)));
	ourShader->setVec3("spotLights[0].ambient", 0.25f, 0.25f, 0.25f);
	ourShader->setVec3("spotLights[0].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("spotLights[0].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("spotLights[0].constant", 1.0f);
	ourShader->setFloat("spotLights[0].linear", 0.027f);
	ourShader->setFloat("spotLights[0].quadratic", 0.0028f);
	////Set fourth Spot Light---------------------------------------------------- Shooter
	ourShader->setVec3("pointLights[0].position", LightArray[0].GetCenter().x - 0.2, LightArray[0].GetCenter().y - ((LightArray[0].GetMaxVertex() - LightArray[0].GetMinVertex()) / glm::vec3(2)).y, LightArray[0].GetCenter().z);
	ourShader->setVec3("pointLights[0].direction", 0.0, -1, 0);
	ourShader->setVec3("pointLights[0].ambient", 0.25f, 0.25f, 0.25f);
	ourShader->setVec3("pointLights[0].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("pointLights[0].constant", 1.0f);
	ourShader->setFloat("pointLights[0].linear", 0.045f);
	ourShader->setFloat("pointLights[0].quadratic", 0.0075f);
	////Set fourth Spot Light---------------------------------------------------- Shooter
	ourShader->setVec3("pointLights[1].position", LightArray[1].GetCenter().x - 0.2, LightArray[1].GetCenter().y - ((LightArray[1].GetMaxVertex() - LightArray[1].GetMinVertex()) / glm::vec3(2)).y, LightArray[1].GetCenter().z);
	ourShader->setVec3("pointLights[1].direction", 0.0, -1, 0);
	ourShader->setVec3("pointLights[1].ambient", 0.25f, 0.25f, 0.25f);
	ourShader->setVec3("pointLights[1].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("pointLights[1].constant", 1.0f);
	ourShader->setFloat("pointLights[1].linear", 0.045f);
	ourShader->setFloat("pointLights[1].quadratic", 0.0075f);
	////Set fourth Spot Light---------------------------------------------------- Shooter
	ourShader->setVec3("pointLights[2].position", LightArray[2].GetCenter().x - 0.2, LightArray[2].GetCenter().y - ((LightArray[2].GetMaxVertex() - LightArray[2].GetMinVertex()) / glm::vec3(2)).y, LightArray[2].GetCenter().z);
	ourShader->setVec3("pointLights[2].direction", 0.0, -1, 0);
	ourShader->setVec3("pointLights[2].ambient", 0.25f, 0.25f, 0.25f);
	ourShader->setVec3("pointLights[2].diffuse", 0.5f, 0.5f, 0.5f);
	ourShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
	ourShader->setFloat("pointLights[2].constant", 1.0f);
	ourShader->setFloat("pointLights[2].linear", 0.045f);
	ourShader->setFloat("pointLights[2].quadratic", 0.0075f);


}

void  GameManager::CollisionDetection(Enemy* e, int index)
{
	if (!(e->GetLastMove() == glm::vec3(0)))
	{
		bool collide = false;
		for (int i = 0; i < EnemyList.size(); i++)
		{
			if (Collide(e, EnemyList[i]) && i != index&& e->GetCenter().x<35)
			{
				collide = true;
				cout << "collided with enemy, enemy " << endl;
				break;
			}
		}

		if (!collide)
		{
			for (int i = 12; i < ObstaclesList.size(); i++)
			{
				if (Collide(e, ObstaclesList[i]))
				{
					collide = true;
					//ObstaclesList.throwatenemy();
					//ObstaclesList.erase(ObstaclesList.begin() + i);
					e->StartShooting();
					ObstaclesList[i]->throwRock(camera.Position);
					cout << "collided with rock, rock " << i << endl;

					break;
				}
			}
		}
		if (!collide) //check with the wall
		{
			if (e->GetCenter().x <= (GameWall->GetCenter().x + (abs(GameWall->GetMaxVertex().x - GameWall->GetMinVertex().x) * 4)))
			{
				collide = true;
				GamePlayer->reducehealth(0.5);
				cout << "Wall" << endl;
			}

		}

		if (collide)
			e->Translate(-e->GetLastMove());


	}
}



bool GameManager::Collide(GameObject* e1, GameObject* e2)
{
	//glm::vec3 diff = e1->GetCenter() - e2->GetCenter();
	//float m = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	//float r = m - (e1->GetRadius() + e2->GetRadius());
	//return r < 0;
	float MinX, MaxX, MinZ, MaxZ, MaxY, MinY;
	MaxX = /*e2->GetCenter().x + (e2->GetMaxVertex().x - e2->GetMinVertex().x) / 2.0f*/e2->GetMaxVertex().x;
	MinX = /*e2->GetCenter().x - (e2->GetMaxVertex().x - e2->GetMinVertex().x) / 2.0f*/e2->GetMinVertex().x;
	MaxZ = /*e2->GetCenter().z + (e2->GetMaxVertex().z - e2->GetMinVertex().z) / 2.0f*/e2->GetMaxVertex().z;
	MinZ = /*e2->GetCenter().z - (e2->GetMaxVertex().z - e2->GetMinVertex().z) / 2.0f*/e2->GetMinVertex().z;
	MaxY = /*e2->GetCenter().z + (e2->GetMaxVertex().z - e2->GetMinVertex().z) / 2.0f*/e2->GetMaxVertex().y;
	MinY = /*e2->GetCenter().z - (e2->GetMaxVertex().z - e2->GetMinVertex().z) / 2.0f*/e2->GetMinVertex().y;

	//bool checkcenterinboundriesofother = (e1->GetCenter().x > MinX && e1->GetCenter().x < MaxX) && (e1->GetCenter().z > MinZ && e1->GetCenter().z < MaxZ);
	//bool partofenemyinside =((e1->GetMaxVertex().z > MinZ && e1->GetMaxVertex().z < MaxZ) || ((e1->GetMinVertex().z > MinZ && e1->GetMinVertex().z < MaxZ) ))&& ((e1->GetMaxVertex().x > MinX && e1->GetMaxVertex().x < MaxX) || ((e1->GetMinVertex().x > MinX && e1->GetMinVertex().x < MaxX)));
	bool checkoverenemy = (((e1->GetCenter().x - e1->GetLastMove().x) < MinX) && ((e1->GetCenter().x) > MaxX) && (((e1->GetMaxVertex().z > MinZ || e1->GetMaxVertex().z < MaxZ) || ((e1->GetMinVertex().z > MinZ || e1->GetMinVertex().z < MaxZ)))));
	//return ((/*checkcenterinboundriesofother||*/checkoverenemy|| partofenemyinside)) && (e1->GetCenter().y < MaxY) && (e1->GetCenter().y > MinY);


	glm::vec3 diff = glm::vec3(abs(e1->GetCenter().x - e2->GetCenter().x), abs(e1->GetCenter().y - e2->GetCenter().y), abs(e1->GetCenter().z - e2->GetCenter().z));
	glm::vec3 sumofcenters = glm::vec3(abs(e1->GetCenter().x - e1->GetMaxVertex().x) + abs(e2->GetCenter().x - e2->GetMaxVertex().x), abs(e1->GetCenter().y - e1->GetMaxVertex().y) + abs(e2->GetCenter().y - e2->GetMaxVertex().y), abs(e1->GetCenter().z - e1->GetMaxVertex().z) + abs(e2->GetCenter().z - e2->GetMaxVertex().z));

	return ((diff.x <= sumofcenters.x && diff.z <= sumofcenters.z && diff.y <= sumofcenters.y) /*|| checkoverenemy*/);
}



GameManager::~GameManager()
{
	delete GamePlayer;
	glfwTerminate();
}
