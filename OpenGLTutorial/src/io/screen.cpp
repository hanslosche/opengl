#include "screen.h"

#include "keyboard.h"
#include "mouse.h"

unsigned int Screen::SCR_WIDTH = 800;
unsigned int Screen::SCR_HEIGHT = 600;


void Screen::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

Screen::Screen()
	: window(nullptr){}

bool Screen::init() {
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "openGL", NULL, NULL);
	if (window == NULL) {
		// window not created;
		return false;
	}
	glfwMakeContextCurrent(window);

	return true;
}

void Screen::setParameters() {
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, Screen::framebufferSizeCallback);

	// mouse & keyboard callback
	glfwSetKeyCallback(window, Keyboard::keyCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // disable cursor
	glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
	glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
	glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

	glEnable(GL_DEPTH_TEST);
}

// main loop
void Screen::update() {
	glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::newFrame() {
	glfwSwapBuffers(window);
}

// window closing 
bool Screen::shouldClose() {
	return glfwWindowShouldClose(window);
}
void Screen::setShouldClose(bool shouldClose) {
	glfwSetWindowShouldClose(window, shouldClose);
}