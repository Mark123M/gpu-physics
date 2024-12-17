#ifndef _SPATIALGRID_
#define _SPATIALGRID_

#include <memory.h>
#include <vector>
#include "Particle.h"

// Uniform spatial grid for collision testing
class SpatialGrid {
	int gridW, gridH, cellSize;
	std::vector<std::vector<std::vector<Particle*>>> grid;

	void draw();
};

#endif