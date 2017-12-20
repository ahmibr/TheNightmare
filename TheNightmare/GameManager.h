#ifndef GM_H
#define GM_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>
#include "Enemy.h"

#include <iostream>
#include <time.h>
#include "Allincludes.h"


class GameManager
{
	Sky*GameSky;
	Floor*GameFloor;
	Wall*GameWall;
	Portal*GamePortal;
	vector<Environment*>ObstaclesList;
	glm::vec3 MinAvaliableSpace;
	glm::vec3 MaxAvaliableSpace;

	vector<Enemy*> EnemyList;
	int NumberOfTotalEnemies;
	int PreviousEnemy = 0, PrevPreviousEnemy = 1;
	Shader *ourShader;
	GLFWwindow* window;
	Rocks *rock;
	
	static int Menus;
	Model*MenusArray[4];
	Light*LightArray;

	int shootingDelay = 0;
	int TimeLeft;
	//void moveRock(Rocks*& rock, glm::vec3 intialPos, float Vo, float theta);

	// settings
	const unsigned int SCR_WIDTH = 1500;
	const unsigned int SCR_HEIGHT = 800;

public:
	GameManager();
	~GameManager();
	bool Start();
	void GameLoop();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void processInput(GLFWwindow *window);
	void LoadAllModels(); 
	void SetLighting();
	void GenerateEnemies();
	void GenerateObstacles();
	void GenerateRocks(int numRocks);
};
#endif
