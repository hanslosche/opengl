#ifndef LIGHT_H
#define LIGHT_H


#include <glm/glm.hpp>
#include "shader.h"

struct DirLight {

	glm::vec3 direction;

	// light values
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	void render(Shader shader);
};

struct PointLight {

	glm::vec3 position;

	// attenuation constants
	float k0;
	float k1;
	float k2;

	// light values
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	void render(Shader shader, int idx);
};

struct SpotLight {

	glm::vec3 position;
	glm::vec3 direction;

	float cutOff;
	float outerCutOff;	
	
	// attenuation constants
	float k0;
	float k1;
	float k2;

	// light value
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	void render(Shader shader, int idx);
};

#endif