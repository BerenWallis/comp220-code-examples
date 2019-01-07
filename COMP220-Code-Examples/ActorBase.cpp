#include "ActorBase.h"



ActorBase::ActorBase()
{
}


ActorBase::ActorBase(glm::vec3 _position, glm::vec3 _rotation)
{
	position = _position;
	rotation = _rotation;
}

ActorBase::~ActorBase()
{
}


glm::mat4 ActorBase::translationMatrix()
{
	return glm::translate(position);
}

glm::mat4 ActorBase::rotationMatrix()
{
	return glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
		*glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f))
		*glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::mat4 ActorBase::scaleMatrix()
{
	return glm::scale(scale);
}

glm::mat4 ActorBase::modelMatrix()
{
	return translationMatrix() * rotationMatrix() * scaleMatrix();
}