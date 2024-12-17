#ifndef _PARTICLE_
#define _PARTICLE_

#include "object3d.h"
#include "glm/vec3.hpp"

class Particle : public Object3D {
	float density;
	float pressureGrad;
	glm::vec3 diffusion;
	glm::vec3 force; // Net external force
	glm::vec3 normal; // For surface tension and reconstruction
public:
	Particle(glm::vec3 pos, glm::vec3 vel, float density, float pressureGrad, glm::vec3 diffusion, glm::vec3 force, glm::vec3 normal, std::vector<std::unique_ptr<Collider>>& colliders, FileLogger& logger);
	std::vector<glm::vec3> F(const std::vector<glm::vec3>& S, float timestep) override;
	
	void update(float deltaTime) override;
	void draw() override;
	std::string stringify() override;

	friend class Fluid;
};

#endif