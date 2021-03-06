#pragma once
#include "ActorBase.h"

#include <GL\glew.h>
#include <iostream>

#include "Material.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "Camera.h"

class Actor :
	public ActorBase
{
public:
	Actor();
	Actor(std::string meshName, Material* mat, glm::vec3 _position, glm::vec3 _rotation);


	~Actor();

	// Create and compile our GLSL program from the shaders
	GLuint programID = 0;

	//Load Mesh
	const char* MODELS_FOLDER = "Models/";
	MeshCollection* mesh = new MeshCollection();
	GLuint textureID;

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

	void render(Camera* cam);
};

