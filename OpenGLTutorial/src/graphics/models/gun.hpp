#include "../model.h"
#include "../../io/camera.h"
#include "../../io/keyboard.h"
class Gun: public Model {
public:
	Gun()
		: Model(glm::vec3(0.0f), glm::vec3(0.05f), true) {}


	void render(Shader shader, bool setModel = false) {
		glm::mat4 model = glm::mat4(1.0f);

		// set position
		// multiply offset by unit in 2 directions
		pos = Camera::defaultCamera.cameraPos + glm::vec3(Camera::defaultCamera.cameraFront * 8.0f) - glm::vec3(Camera::defaultCamera.cameraUp * 3.15f);
		model = glm::translate(model, pos);

		// rotate around camera right using dot product
		float theta = acos(glm::dot(Camera::defaultCamera.worldUp, Camera::defaultCamera.cameraFront) /
			glm::length(Camera::defaultCamera.cameraUp) / glm::length(Camera::defaultCamera.cameraFront));
		// offset by pi/2 radians bc angles
		model = glm::rotate(model, glm::radians(90.0f) - theta, Camera::defaultCamera.cameraRight);

		//rotate around cameraUp using dot product
		glm::vec2 front2d = glm::vec2(Camera::defaultCamera.cameraFront.x, Camera::defaultCamera.cameraFront.z);
		theta = acos(glm::dot(glm::vec2(1.0f, 0.0f), front2d) / glm::length(front2d));
		model = glm::rotate(model, Camera::defaultCamera.cameraFront.z < 0 ? theta : -theta, Camera::defaultCamera.worldUp);

		// scale 
		model = glm::scale(model, size);
		shader.setMat4("model", model);
		Model::render(shader, false);

	}

};