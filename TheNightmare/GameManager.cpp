#include "GameManager.h"
Camera camera(glm::vec3(0, 10, 0)); //up in y front in x
glm::vec3 CameraGunOffset = glm::vec3(0.0f, 0.25f, 0.0f);
 float lastX;
 float lastY;
 bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

GameManager::GameManager() 
{
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
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
		Mai[Gun]->Translate(camera.Position - Mai[Gun]->ObjectCenter - CameraGunOffset);
	}

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
		Mai[Gun]->Translate(camera.Position- Mai[Gun]->ObjectCenter- CameraGunOffset);
	}
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

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void GameManager::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}


void GameManager::LoadAllModels()
{ 
	Mai.resize(EndofObjects);
	//Load and add instances of fixed objects
	Mai[Sky] = new GameObject("../resources/objects/0/0.obj", glm::vec3(0.0f, 0.0f, 0.0f));
	Mai[Sky]->AddInstance();
	Mai[Floor] = new GameObject("../resources/objects/1/1.obj");
	Mai[Floor]->AddInstance();
	Mai[Wall] = new GameObject("../resources/objects/2/2.obj", glm::vec3(-35.0f, 0.0f, 0.0f));
	Mai[Wall]->AddInstance();
	Mai[Gun] = new GameObject("../resources/objects/3/3.obj", glm::vec3(-35.0f, 4.5f, 0.0f));
	Mai[Gun]->AddInstance();
	Mai[Tree] = new GameObject("../resources/objects/10/tree.obj", glm::vec3(-10.0f, 0.0f, 15.0f));
	Mai[Tree]->AddInstance();
	Mai[rock] = new GameObject("../resources/objects/11/11.obj", glm::vec3(-10.0f, 0.0f, -15.0f));
	Mai[rock]->AddInstance();
	Mai[Portal] = new GameObject("../resources/objects/9/portal/portal.obj", glm::vec3(40.0f, 0.0f, 0.0f));
	Mai[Portal]->AddInstance();
	////////////////////////////////////////////////////
	//Load Rest of objects
	Mai[Pika] = new GameObject("../resources/objects/4/4.obj", glm::vec3(-15.0f, 0.0f, 5.0f));
	Mai[Grim] = new GameObject("../resources/objects/5/5.obj", glm::vec3(10.0f, 0.0f, 10.0f));
	Mai[Raiden] = new GameObject("../resources/objects/6/6.obj", glm::vec3(0.0f, 0.0f, -10.0f));
	Mai[Donut] = new GameObject("../resources/objects/7/7.obj", glm::vec3(0.0f, 0.0f, 10.0f));
	Mai[Alien] = new GameObject("../resources/objects/8/8.obj", glm::vec3(0.01f, 0.01f, 0.01f)/*,glm::vec3(0.05f,0.05f,0.05f)*/);
	Mai[Wizard] = new GameObject("../resources/objects/12/13.obj", glm::vec3(-10.0f, 10.0f, -15.0f));
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
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window); //Set Current context to window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Set funtion to call when change happens to framebuffer
	glfwSetCursorPosCallback(window, mouse_callback); //change in cursor
	glfwSetScrollCallback(window,scroll_callback); // change when scroll

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
	ourShader=new Shader("../shaders/1.model_loading.vs", "../shaders/1.model_loading.fs");

	// load models

	LoadAllModels();

	//Set up Camera Position depending on GUN
	camera.SetCameraPosition(Mai[Gun]->ObjectCenter+ CameraGunOffset);
	//Declare camera moving space limits, Wall length
	camera.MinSpace = Mai[Wall]->MinVertex.z+1;
	camera.MaxSpace = Mai[Wall]->MaxVertex.z-1;
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

		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		ourShader->setMat4("projection", projection);
		ourShader->setMat4("view", view);

		//For Phase1 will add an instance of all enemies
		for (int i = Pika; i < EndofObjects; i++)
		{
			Mai[i]->AddInstance();
		}

		//Drawww whole thing
		for (int i = 0; i < EndofObjects; i++)
		{
			ourShader->setMat4("model", Mai[i]->GetModelMatrix(0));
			Mai[i]->Draw(*ourShader);
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}
GameManager::~GameManager()
{
	glfwTerminate();
}
