#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm/gtc/quaternion.hpp> 
#include <glm/gtx/quaternion.hpp>

class ActorBase
{
public:
	ActorBase(glm::vec3 _position, glm::vec3 _rotation);
	ActorBase();
	~ActorBase();
	const glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 translationMatrix();
	glm::mat4 rotationMatrix();
	glm::mat4 scaleMatrix();
	virtual glm::mat4 modelMatrix();
};

