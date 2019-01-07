#include "Camera.h"



glm::mat4 Camera::viewMatrix()
{
	return glm::lookAt(position, position + cameraFront, cameraUp);
}


void Camera::addRotation(float Pitch, float Yaw, float Roll)
{
	rotation.y += Pitch;
	rotation.x += Yaw;
	rotation.z += Roll;

	rotation.x = glm::clamp(rotation.x, -80.0f,80.0f);

	cameraFront.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
	cameraFront.y = sin(glm::radians(rotation.x));
	cameraFront.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));

	cameraFront = glm::normalize(cameraFront);
	cameraRight = glm::normalize(glm::cross(cameraFront, WORLD_UP));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}




Camera::Camera(glm::vec3 _position, glm::vec3 _rotation)
{
	position = _position;
	rotation = _rotation;
	addRotation(0, 0, 0);
}


Camera::~Camera()
{
}
