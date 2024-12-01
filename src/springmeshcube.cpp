#include "springmeshcube.h"

SpringMeshCube::SpringMeshCube(int size, std::vector<Plane> &colliders, FileLogger &logger):
    SpringMesh{cpoints, csprings, cfaces, colliders, logger}, size{size}, adjacencyMap{} {
        initSprings();
    }

void SpringMeshCube::initSprings() {
    // adjacency list idea? 
    // n ^ 3 * 22 
    // "3,2,1" -> {"2,1,0": true}
    //std::vector< adjacencySet[size + 1][size + 1][size + 1];
    int structuralNeighbours[6][3] = {{-1, 0, 0}, {0, -1, 0}, {0, 0, -1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int shearNeighbours[16][3] = {{}}; 

    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            for (int k = 0; k <= size; k++) {
                Point p{1, Vector3{i, j, k}, colliders, logger};

                // Structural springs
                for (auto n: structuralNeighbours) {
                    int ni = i + n[0], nj = j + n[1], nk = k + n[2];

                }

                // Shearing springs
            }
        }
    }
}

std::string coordsToString(int i, int j, int k) {
    return std::to_string(i) + "," + std::to_string(j) + "," + std::to_string(k);
}

void SpringMeshCube::createSpring(int i1, int j1, int k1, int i2, int j2, int k2) {
    std::string coordStr1 = coordsToString(i1, j1, k1);
    std::string coordStr2 = coordsToString(i2, j2, k2);

    if (!isInBounds(i2, j2, k2) || (adjacencyMap.find(coordStr1) != adjacencyMap.end() && adjacencyMap[coordStr1].find(coordStr2) != adjacencyMap[coordStr1].end())) {
        return;
    }

    csprings.push_back(Spring{1, 0.7, 1, p, np});
    adjacencyMap[coordStr1].insert(coordStr2);
}

bool SpringMeshCube::canCreateSpring(int i1, int j1, int k1, int i2, int j2, int k2) {
    std::string coordStr1 = coordsToString(i1, j1, k1);
    std::string coordStr2 = coordsToString(i2, j2, k2);

    if (!isInBounds(i2, j2, k2) || (adjacencyMap.find(coordStr1) != adjacencyMap.end() && adjacencyMap[coordStr1].find(coordStr2) != adjacencyMap[coordStr1].end())) {
        return false;
    }

    adjacencyMap[coordStr1].insert(coordStr2);
    adjacencyMap[coordStr2].insert(coordStr1);
    return true;
}

bool SpringMeshCube::isInBounds(int i, int j, int k) {
    return 0 <= i && i <= size && 0 <= j && j <= size && 0 <= k && k <= size;
}
