#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/model.h"

#include "graphics/models/cube.hpp"
#include "graphics/models/lamp.hpp"


#include "io/keyboard.h"
#include "io/mouse.h"
#include "io/screen.h"
#include "io/camera.h"


void processInput(double deltaTime);

float mixVal = 0.5f;

Screen screen;

Camera Camera::defaultCamera(glm::vec3(0.0f, 0.0f, 3.0f));

double deltaTime = 0.0f;
double lastFrame = 0.0f;

int main() {
	int success;
	char infoLog[512];

	std::cout << "Hello, openGL!" << std::endl;

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	if (!screen.init()) {
		std::cout << "Could not open window" << std::endl;
		glfwTerminate();
		return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	screen.setParameters();

	// SHADER _______________________________________________
	Shader shader("assets/object.vs", "assets/object.fs");
	Shader lampShader("assets/object.vs", "assets/lamp.fs");

	// MODELS _______________________________________________
	glm::vec3 cubePositions[] = {
		 glm::vec3(0.0f,  0.0f,  0.0f),
		 glm::vec3(2.0f,  5.0f, -15.0f),
		 glm::vec3(-1.5f, -2.2f, -2.5f),
		 glm::vec3(-3.8f, -2.0f, -12.3f),
		 glm::vec3(2.4f, -0.4f, -3.5f),
		 glm::vec3(-1.7f,  3.0f, -7.5f),
		 glm::vec3(1.3f, -2.0f, -2.5f),
		 glm::vec3(1.5f,  2.0f, -2.5f),
		 glm::vec3(1.5f,  0.2f, -1.5f),
		 glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Cube cubes[10];
	for (unsigned int i = 0; i < 10; i++) {
		cubes[i] = Cube(cubePositions[i], glm::vec3(1.0f));
		cubes[i].init();
	}

	Lamp lamp(glm::vec3(1.0f), glm::vec3(0.1), glm::vec3(0.8f), glm::vec3(1.0f), glm::vec3(-1.0f, -0.5f, 0.5f), glm::vec3(0.25f));
	//lamp.init();

	while (!screen.shouldClose()) {
		// calculate dt
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		// process input
		processInput(deltaTime);

		// render 
		screen.update();

		// draw shapes
		shader.activate();

		// set light position
		shader.set3Float("light.position", Camera::defaultCamera.cameraPos);
		shader.set3Float("light.direction",Camera::defaultCamera.cameraFront);
		shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
		shader.set3Float("viewPos", Camera::defaultCamera.cameraPos);

		// set light strengths
		shader.set3Float("light.ambient", lamp.ambient);
		shader.set3Float("light.diffuse", lamp.diffuse);
		shader.set3Float("light.specular", lamp.specular);
		shader.setFloat("light.k0", 1.0f);
		shader.setFloat("light.k1", 0.07f);
		shader.setFloat("light.k2", 0.032f);



		// create transformation 
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = Camera::defaultCamera.getViewMatrix();
		projection = glm::perspective(
			glm::radians(Camera::defaultCamera.zoom),
			(float)Screen::SCR_WIDTH / (float)Screen::SCR_HEIGHT, 0.1f, 100.0f);

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		for (unsigned int i = 0; i < 10; i++){
			cubes[i].render(shader);
		};

		//lampShader.activate();
		//lampShader.setMat4("view", view);
		//lampShader.setMat4("projection", projection);
		//lamp.render(lampShader);

		// send new frame to window
		screen.newFrame();
		glfwPollEvents();
	}
	for (unsigned int i = 0; i < 10; i++) {
		cubes[i].cleanup();
	};

	//lamp.cleanup();

	glfwTerminate();
	return 0;
}


void processInput(double deltaTime) {
	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		screen.setShouldClose(true);
	}

	if (Keyboard::key(GLFW_KEY_UP)) {
		mixVal += .05f;
		if (mixVal > 1) {
			mixVal = 1.0f;
		}
	}
	if (Keyboard::key(GLFW_KEY_DOWN)) {
		mixVal -= .05f;
		if (mixVal < 0) {
			mixVal = 0.0f;
		}
	}

	if (Keyboard::key(GLFW_KEY_W)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::FORWARD, deltaTime);;
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::BACKWARD, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::RIGHT, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_A)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::LEFT, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_SPACE)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::UP, deltaTime);
	}
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
		Camera::defaultCamera.updateCameraPos(CameraDirection::DOWN, deltaTime);
	}

}





