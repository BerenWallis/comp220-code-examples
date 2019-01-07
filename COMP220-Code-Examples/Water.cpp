#include "Water.h"


Water::Water(std::string meshName, Material * mat, glm::vec3 _position, glm::vec3 _rotation) : Actor(meshName, mat, _position, _rotation)
{
	wavesLocation = glGetUniformLocation(programID, "waves");
	timeLocation = glGetUniformLocation(programID, "time");
}

Water::~Water()
{}

void Water::render(Camera *cam,float dt)
{
	glUseProgram(programID);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//send the uniforms across
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix()));
	glUniformMatrix4fv(viewMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cam->viewMatrix()));
	glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(cam->projectionMatrix));
	glUniform1i(baseTextureLocation, 0);

	glUniform4fv(ambientMaterialColourLocation, 1, glm::value_ptr(ambientMaterialColour));
	glUniform4fv(diffuseMaterialColourLocation, 1, glm::value_ptr(diffuseMaterialColour));
	glUniform4fv(specularMaterialColourLocation, 1, glm::value_ptr(specularMaterialColour));

	glUniform4fv(ambientLightColourLocation, 1, glm::value_ptr(ambientLightColour));
	glUniform4fv(diffuseLightColourLocation, 1, glm::value_ptr(diffuseLightColour));
	glUniform4fv(specularLightColourLocation, 1, glm::value_ptr(specularLightColour));
	glUniform1f(specularMaterialPowerLocation, specularMaterialPower);

	glUniform3fv(lightDirectionLocation, 1, glm::value_ptr(lightDirection));
	glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(cam->position));

	waves = glm::vec3(1, rand() % 3, 1);
	time += dt/1000;
	glUniform3fv(wavesLocation,1, glm::value_ptr(waves));
	glUniform1f(timeLocation, time);

	mesh->render();
	
}
