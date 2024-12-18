#include "Particle.h"

using namespace glm;

Particle::Particle(glm::vec3 pos, glm::vec3 vel, float density, float pressureGrad, glm::vec3 diffusion, glm::vec3 force, glm::vec3 normal, std::vector<std::unique_ptr<Collider>>& colliders, FileLogger& logger):
	Object3D{std::vector<vec3>{pos, vel}, colliders, logger}, density{density}, pressureGrad{pressureGrad}, diffusion{diffusion}, force{force}, normal{normal} { }

std::vector<glm::vec3> Particle::F(const std::vector<glm::vec3>& S, float timestep) {
	return std::vector<glm::vec3>();
}

void Particle::update(float deltaTime) {

}

void Particle::draw() {

}

std::string Particle::stringify() {
	return std::string();
}
