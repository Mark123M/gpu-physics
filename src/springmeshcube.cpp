#include "springmeshcube.h"

SpringMeshCube::SpringMeshCube(int size, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    SpringMesh{cubePoints, cubeSprings, cubeFaces, colliders, logger}, size{size}, coordPoints{}, adjacencyMap{} {
        initSprings();
        initFaces();
    }

void SpringMeshCube::initSprings() {
    for (int i = 0; i <= size; i++) {
        coordPoints.push_back(std::vector<std::vector<Point>>());
        for (int j = 0; j <= size; j++) {
            coordPoints[i].push_back(std::vector<Point>());
            for (int k = 0; k <= size; k++) {
                Point p{1, Vector3{i, j, k}, colliders, logger};
                coordPoints[i][j].push_back(p);
                cubePoints.push_back(p);
            }
        }
    }

    int structuralNeighbours[6][3] = {{-1, 0, 0}, {0, -1, 0}, {0, 0, -1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int shearNeighbours[20][3] = {{1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, {-1, 1, 0}, {1, 0, 1}, {1, 0, -1}, {-1, 0, -1}, {-1, 0, 1}, {0, 1, 1}, {0, 1, -1}, {0, -1, -1}, {0, -1, 1}, {1, 1, 1}, {1, 1, -1}, {1, -1, 1}, {1, -1, -1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1}};

    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            for (int k = 0; k <= size; k++) {
                // Structural springs
                for (auto n: structuralNeighbours) {
                    int ni = i + n[0], nj = j + n[1], nk = k + n[2];
                    
                    if (canCreateSpring(i, j, k, ni, nj, nk)) {
                        cubeSprings.emplace_back(1, 0.7, 1, coordPoints[i][j][k], coordPoints[ni][nj][nk]);
                    }
                }

                // Shearing springs
                for (auto n: shearNeighbours) {
                    int ni = i + n[0], nj = j + n[1], nk = k + n[2];

                    if (canCreateSpring(i, j, k, ni, nj, nk)) {
                        cubeSprings.emplace_back(1, 0.7, 1, coordPoints[i][j][k], coordPoints[ni][nj][nk]);
                    }
                }
            }
        }
    }
}

void SpringMeshCube::initFaces() {
    
}

std::string coordsToString(int i, int j, int k) {
    return std::to_string(i) + "," + std::to_string(j) + "," + std::to_string(k);
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
