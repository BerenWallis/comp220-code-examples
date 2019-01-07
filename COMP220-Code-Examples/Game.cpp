#include "Game.h"

Game::~Game(){}

int Game::init(int WindowWidth, int WindowHeight)
{
	//Initialises the SDL Library, passing in SDL_INIT_VIDEO to only initialise the video subsystems
	//https://wiki.libsdl.org/SDL_Init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		//Display an error message box
		//https://wiki.libsdl.org/SDL_ShowSimpleMessageBox
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_Init failed", SDL_GetError(), NULL);
		return 1;
	}

	//Create a window, note we have to free the pointer returned using the DestroyWindow Function
	//https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Checks to see if the window has been created, the pointer will have a value of some kind
	if (window == nullptr)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateWindow failed", SDL_GetError(), NULL);
		//Close the SDL Library
		//https://wiki.libsdl.org/SDL_Quit
		SDL_Quit();
		return 1;
	}

	//Request 3.2 Core OpenGL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	gl_Context = SDL_GL_CreateContext(window);
	if (gl_Context == nullptr)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL_CreateContext Failed", SDL_GetError(), NULL);

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	//init GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Show error
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "GLEW Initialisation Failed", (char*)glewGetErrorString(err), NULL);
		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	

	//Initialize SDL
	if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL No Joystick! SDL Error: %s\n", SDL_GetError());
		gGameController = SDL_JoystickOpen(0);
		if (gGameController == NULL)
		{
			printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			JOYSTICK = true;
		}
		
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//glCullFace(GL_FRONT_AND_BACK);
	// Create Scenery
	GenScenery();
	return 0;
}

void Game::GenScenery()
{
	blinnPhong = new Material("baseVert.glsl", "blinnPhongFrag.glsl");
	waterMat = new Material("waterVert.glsl", "waterFrag.glsl");
	LightHouse = new Actor("Lighhouse.fbx", blinnPhong, glm::vec3(4, 1, 0), glm::vec3(0, 0, 0));

	LightHouse->ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	LightHouse->diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	LightHouse->specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	LightHouse->lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	LightHouse->ambientMaterialColour = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
	LightHouse->diffuseMaterialColour = glm::vec4(0.8f, 0.0f, 0.0f, 1.0f);
	LightHouse->specularMaterialColour = glm::vec4(1.0f, 0.5f, 0.5f, 1.0f);

	Ground = new Actor("Ground.fbx", blinnPhong, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));

	Ground->ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Ground->diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Ground->specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Ground->lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	Ground->ambientMaterialColour = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
	Ground->diffuseMaterialColour = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
	Ground->specularMaterialColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	Sea = new Water("sea.fbx", waterMat, glm::vec3(0, 6, 0), glm::vec3(0, 0, 0));
	Sea->scale = glm::vec3(80.0f, 1.0f, 50.0f);
	Sea->ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Sea->diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Sea->specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	Sea->lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	Sea->ambientMaterialColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	Sea->diffuseMaterialColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
	Sea->specularMaterialColour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

void Game::update(double deltaTime)
{
	dt = deltaTime;
	SDL_Event ev;
	//Poll for the events which have happened in this frame
	//https://wiki.libsdl.org/SDL_PollEvent
	while (SDL_PollEvent(&ev))
	{
		if (JOYSTICK)
		{
			if (ev.jaxis.axis == 0)
			{
				//Left of dead zone
				if (ev.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					gameCamera->addRotation(-1 * rotateSpeed / deltaTime, 0, 0);
				}
				//Right of dead zone
				else if (ev.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					gameCamera->addRotation(1 * rotateSpeed / deltaTime, 0, 0);
				}
				//Y axis motion
				else if (ev.jaxis.axis == 1)
				{
					//Below of dead zone
					if (ev.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						gameCamera->addRotation(0, -1 * rotateSpeed / deltaTime, 0);
					}
					//Above of dead zone
					else if (ev.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						gameCamera->addRotation(0, 1 * rotateSpeed / deltaTime, 0);
					}
				}
			}
		}
		else
		{
			if (ev.type == SDL_MOUSEMOTION)
			{
				gameCamera->addRotation(ev.motion.xrel * rotateSpeed * deltaTime,
					ev.motion.yrel * -INVERT_MOUSE  *rotateSpeed * deltaTime, 0);
			}
		}
		updatePosition(ev);
	}
}


void Game::updatePosition(SDL_Event ev)
{
	switch (ev.type)
	{
		//QUIT Message, usually called when the window has been closed
	case SDL_QUIT:
		running = false;
		break;
		//KEYDOWN Message, called when a key has been pressed down
	case SDL_KEYDOWN:
		//Check the actual key code of the key that has been pressed
		switch (ev.key.keysym.sym)
		{
			//Escape key
		case SDLK_ESCAPE:
			running = false;
			break;
		case SDLK_a:
			gameCamera->position.x += glm::sin(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			gameCamera->position.z -= glm::cos(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			break;
		case SDLK_d:
			gameCamera->position.x -= glm::sin(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			gameCamera->position.z += glm::cos(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			break;
		case SDLK_w:
			gameCamera->position.x += glm::cos(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			gameCamera->position.z -= glm::sin(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			break;
		case SDLK_s:
			gameCamera->position.x -= glm::cos(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			gameCamera->position.z += glm::sin(glm::radians(gameCamera->rotation.y)) * moveSpeed * dt;
			break;
		case SDLK_SPACE:
			gameCamera->position.y += 1;
			break;
		case SDLK_LCTRL:
			gameCamera->position.y -= 1;
			break;
		}
	}
}

void Game::render()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Do rendering here!
	
	LightHouse->render(gameCamera);
	Ground->render(gameCamera);
	Sea->render(gameCamera,dt);

	SDL_GL_SwapWindow(window);
}

void Game::exit()
{
	if (JOYSTICK)
	{
		SDL_JoystickClose(gGameController);
	}
	//delete LightHouse;
	//Delete Context
	SDL_GL_DeleteContext(gl_Context);
	//Destroy the window and quit SDL2, NB we should do this after all cleanup in this order!!!
	//https://wiki.libsdl.org/SDL_DestroyWindow
	SDL_DestroyWindow(window);
	//https://wiki.libsdl.org/SDL_Quit
	SDL_Quit();
}
