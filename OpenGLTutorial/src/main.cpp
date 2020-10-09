#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

	glfwInit();

	// openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Tutorial", NULL, NULL);
	if (window == NULL) {
		std::cout << "Could not create window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
		  

	// SHADER ++++++++++++++++++++++++++++++++++++++++
	Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");


	float vertices[] = {
		// positions         // colors
	 -0.5f,  0.5f, 1.0f,  1.0f, 1.0f, 0.5f,   // bottom right
	  0.5f,  0.5f, 0.0f,  0.5f, 1.0f, 0.75f,   // top left  left
	  0.5f, -0.5f, 0.0f,  0.0f, 0.6f, 1.0f,   //bottom right
     -0.5f, -0.5f, 1.0f,  1.0f, 0.2f, 1.0f   // top right
	};
	unsigned int indices[] = {
		0, 1, 2,	// first triangle
		2, 3, 0		// second triangle
	};

	// VBO & VAO
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind VBO & VAO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,  GL_STATIC_DRAW);

	// put index array in EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// set attributes pointers
	// position 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));

	shader.activate();
	shader.setMat4("transform", trans);

	
	while (!glfwWindowShouldClose(window)) {
		// process input
		processInput(window);

		// render 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		shader.activate();

		// set color 
		float timeValue = glfwGetTime();
		float blueValue = (sin(timeValue) / 2.0f) + 0.5f;
		shader.set4Float("ourColor", 0.0f, 0.0f, blueValue, 1.0f);
		trans = glm::rotate(trans, glm::radians(timeValue / 250), glm::vec3(0.1f, 0.1f, 0.1f));
		shader.setMat4("transform", trans);


		// draw elements
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
		shader.setMat4("transform", trans);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));
		shader.setMat4("transform", trans);

		glBindVertexArray(0);

		// send new frame to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;

}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

