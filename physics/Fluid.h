#ifndef _MYFLUID_
#define _MYFLUID_

#include "Particle.h"

class Fluid {
	std::vector<Particle> particles;
	void computeFieldValues();

	int gridW, gridH, cellSize;
	bool drawGrid;
	std::vector<std::vector<std::vector<Particle*>>> grid;
};



#endif