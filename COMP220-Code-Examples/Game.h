#pragma once

#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <math.h>
#include <list>

#include "Vertex.h"
#include "Texture.h"
#include "Model.h"
#include "Mesh.h"
#include "ActorBase.h"
#include "Actor.h"
#include "Camera.h"
#include "Water.h"
#include "Material.h"


class Game
{
public:
	~Game();
	int init(int WindowWidth, int WindowHeight);
	void update(double deltaTime);
	void render();
	void exit();

	bool running = true;

	std::list<Actor> gameActors;

private:

	//Game
	SDL_Window* window = nullptr;
	SDL_GLContext gl_Context;
	Camera* gameCamera = new Camera(glm::vec3(0,6,0),glm::vec3(0,-90,0));
	double dt = 0;
	void GenScenery();

	//Mouse, Keyboard, Joystick
	const bool INVERT_MOUSE = true;
	bool JOYSTICK = false;
	const float JOYSTICK_DEAD_ZONE = 0.1f;
	const float rotateSpeed = 0.02f;
	const float moveSpeed = 0.01f;

	SDL_Joystick* gGameController;
	void updatePosition(SDL_Event ev);

	//std::list<Actor*> sceneActors;
	//Water* water = nullptr;

	Actor* LightHouse = nullptr;
	Actor* Ground = nullptr;
	Water* Sea = nullptr;

	Material* blinnPhong = nullptr;
	Material* waterMat = nullptr;



};

