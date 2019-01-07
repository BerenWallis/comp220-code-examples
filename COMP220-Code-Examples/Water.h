#pragma once
#include "Actor.h"

#include <GL\glew.h>

class Water :
	public Actor
{

private:

public:
	Water(std::string meshName, Material* mat, glm::vec3 _position, glm::vec3 _rotation);
	~Water();
	glm::vec3 waves = glm::vec3(1,3,1);
	GLint wavesLocation;

	float time = 0.0f;
	GLint timeLocation;


	void render(Camera* cam, float dt);
};


