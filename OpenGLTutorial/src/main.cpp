#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/model.h"
#include "graphics/light.h"

#include "graphics/models/cube.hpp"
#include "graphics/models/lamp.hpp"
#include "graphics/models/gun.hpp"


#include "io/keyboard.h"
#include "io/mouse.h"
#include "io/screen.h"
#include "io/camera.h"



void processInput(double deltaTime);

float mixVal = 0.5f;

Screen screen;

Camera Camera::defaultCamera(glm::vec3(0.0f, 0.0f, 0.0f));

double deltaTime = 0.0f; // time between frames
double lastFrame = 0.0f; // time of last frame

bool flashLightOn = false;
Model m;

int main() {

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
	Gun g;
	g.loadModel("assets/models/m4a1/scene.gltf");

	//Model m;
	//m = Model(glm::vec3(0.65f, 1.8f, -6.0f), glm::vec3(0.05f), true);
	//m.loadModel("assets/models/lotr_troll/scene.gltf");


	// LIGHTS _______________________________________________ 
	DirLight dirLight = { glm::vec3(-0.2f, -1.0f, -0.3), glm::vec4(0.1f, 0.1f, 0.1f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f) };


	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f, 2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};

	Lamp lamps[4];
	for (unsigned int i = 0; i < 4; i++) {
		lamps[i] = Lamp(glm::vec3(1.0f),
			glm::vec4(0.05f, 0.05f, 0.05f, 1.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), glm::vec4(0.0f),
			1.0f, 0.07f, 0.032f,
			pointLightPositions[i], glm::vec3(0.2f));
		lamps[i].init();
	};

	SpotLight s = {
		Camera::defaultCamera.cameraPos, Camera::defaultCamera.cameraFront,
		glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(20.0f)),
		1.0f, 0.07f, 0.032f,
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), glm::vec4(1.0f), glm::vec4(1.0f)
	};

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

		shader.set3Float("viewPos", Camera::defaultCamera.cameraPos);

		dirLight.render(shader);

		for (unsigned int i = 0; i < 4; i++) {
			lamps[i].pointLight.render(shader, i);
		}

		shader.setInt("noPointsLights", 4);

		if (flashLightOn) {
			s.position = Camera::defaultCamera.cameraPos;
			s.direction = Camera::defaultCamera.cameraFront;
			s.render(shader, 0);
			shader.setInt("noSpotLights", 1);
		}
		else {
			shader.setInt("noSpotLights", 0);
		}

		// create transformation 
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		view = Camera::defaultCamera.getViewMatrix();
		projection = glm::perspective(
			glm::radians(Camera::defaultCamera.zoom),
			(float)Screen::SCR_WIDTH / (float)Screen::SCR_HEIGHT, 0.1f, 100.0f);

		shader.setMat4("view", view);
		shader.setMat4("projection", projection);

		g.render(shader);
		m.render(shader);

		lampShader.activate();
		lampShader.setMat4("view", view);
		lampShader.setMat4("projection", projection);

		for (unsigned int i = 0; i < 4; i++) {
			lamps[i].render(lampShader);
		};

		// send new frame  to window
		screen.newFrame();
		glfwPollEvents();
	}
	g.cleanup();
	//m.cleanup();


	for (unsigned int i = 0; i < 4; i++) {
		lamps[i].cleanup();
	};

	glfwTerminate();
	return 0;
}


void processInput(double deltaTime) {
	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		screen.setShouldClose(true);
	}

	if (Keyboard::keyWentDown(GLFW_KEY_L)) {
		flashLightOn = !flashLightOn;
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





