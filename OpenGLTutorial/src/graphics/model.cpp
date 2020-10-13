#include "model.h"

Model::Model() {}

void Model::render(Shader shader) {
	mesh.render(shader);
}

void Model::init() {};

void Model::cleanup() {
	mesh.cleanup();
}