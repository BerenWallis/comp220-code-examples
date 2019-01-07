#pragma once
#include "ActorBase.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

class Camera :
	public ActorBase
{
public:
	Camera(glm::vec3 position, glm::vec3 rotation);
	~Camera();

	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)640, 0.1f, 1000.0f);
	
	void addRotation(float x, float y, float z);

private:
	glm::vec3 cameraUp = WORLD_UP;
	glm::vec3 cameraRight;
	glm::vec3 cameraFront;
	
};

