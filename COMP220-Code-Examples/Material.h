#pragma once
#include <GL\glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <SDL_opengl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <list>
#include<iostream>

#include "Shaders.h"

class Material
{
	/*
	//Light properties
	glm::vec4 ambientLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 diffuseLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specularLightColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, 1.0f);


	glm::vec4 ambientMaterialColour = glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
	glm::vec4 diffuseMaterialColour = glm::vec4(0.8f, 0.0f, 0.0f, 1.0f);
	glm::vec4 specularMaterialColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float specularMaterialPower = 25.0f;

	//Get the uniforms from the shader
	GLuint modelMatrixUniformLocation;
	GLuint viewMatrixUniformLocation;
	GLuint projectionMatrixUniformLocation;
	GLint baseTextureLocation;

	GLint ambientLightColourLocation;
	GLint diffuseLightColourLocation;
	GLint specularLightColourLocation;

	GLint lightDirectionLocation;
	GLint cameraPositionLocation;


	GLint ambientMaterialColourLocation;
	GLint diffuseMaterialColourLocation;
	GLint specularMaterialColourLocation;
	GLint specularMaterialPowerLocation;
	void blinnPhong()
	{
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
	}*/

	std::string SHADER_FOLDER = "Shaders/";
public:
	Material(std::string vertex_file_path, std::string fragment_file_path);
	~Material();
	GLuint programID = 0;

};

