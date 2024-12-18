#include "springmeshcube.h"

using namespace glm;

SpringMeshCube::SpringMeshCube(int size, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger):
    SpringMesh{cubePoints, cubeSprings, cubeFaces, colliders, logger}, size{size}, coordPoints{}, adjacencyMap{} {
        initPoints();
        initSprings();
        initFaces();
        logger.logToFile(stringify());
    }

void SpringMeshCube::initPoints() {
    for (int i = 0; i <= size; i++) {
        coordPoints.push_back(std::vector<std::vector<Point>>());
        for (int j = 0; j <= size; j++) {
            coordPoints[i].push_back(std::vector<Point>());
            for (int k = 0; k <= size; k++) {
                bool draw = i == 0 || i == size || j == 0 || j == size || k == 0 || k == size;
                Point p{1, vec3{i, j, k}, draw, colliders, logger};
                coordPoints[i][j].push_back(p);
                cubePoints.push_back(p);
            }
        }
    }
}

void SpringMeshCube::initSprings() {
    int structuralNeighbours[6][3] = {{-1, 0, 0}, {0, -1, 0}, {0, 0, -1}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    int shearNeighbours[20][3] = {{1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, {-1, 1, 0}, {1, 0, 1}, {1, 0, -1}, {-1, 0, -1}, {-1, 0, 1}, {0, 1, 1}, {0, 1, -1}, {0, -1, -1}, {0, -1, 1}, {1, 1, 1}, {1, 1, -1}, {1, -1, 1}, {1, -1, -1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1}};

    for (int i = 0; i <= size; i++) {
        for (int j = 0; j <= size; j++) {
            for (int k = 0; k <= size; k++) {
                // Structural springs
                for (auto n: structuralNeighbours) {
                    int ni = i + n[0], nj = j + n[1], nk = k + n[2];
                    createSpring(i, j, k, ni, nj, nk);
                }

                // Shearing springs
                for (auto n: shearNeighbours) {
                    int ni = i + n[0], nj = j + n[1], nk = k + n[2];
                    createSpring(i, j, k, ni, nj, nk);
                }
            }
        }
    }
}

void SpringMeshCube::initFaces() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // Back face
            cubeFaces.emplace_back(coordPoints[i][j][0], coordPoints[i][j + 1][0], coordPoints[i + 1][j + 1][0]);
            cubeFaces.emplace_back(coordPoints[i][j][0], coordPoints[i + 1][j + 1][0], coordPoints[i + 1][j][0]);

            // Front face
            cubeFaces.emplace_back(coordPoints[i][j][size], coordPoints[i][j + 1][size], coordPoints[i + 1][j + 1][size]);
            cubeFaces.emplace_back(coordPoints[i][j][size], coordPoints[i + 1][j + 1][size], coordPoints[i + 1][j][size]);

            // Left face
            cubeFaces.emplace_back(coordPoints[0][i][j], coordPoints[0][i + 1][j], coordPoints[0][i + 1][j + 1]);
            cubeFaces.emplace_back(coordPoints[0][i][j], coordPoints[0][i + 1][j + 1], coordPoints[0][i][j + 1]);

            // Right face
            cubeFaces.emplace_back(coordPoints[size][i][j], coordPoints[size][i + 1][j], coordPoints[size][i + 1][j + 1]);
            cubeFaces.emplace_back(coordPoints[size][i][j], coordPoints[size][i + 1][j + 1], coordPoints[size][i][j + 1]);

            // Bottom face
            cubeFaces.emplace_back(coordPoints[i][0][j], coordPoints[i][0][j + 1], coordPoints[i + 1][0][j + 1]);
            cubeFaces.emplace_back(coordPoints[i][0][j], coordPoints[i + 1][0][j + 1], coordPoints[i + 1][0][j]);

            // Top face
            cubeFaces.emplace_back(coordPoints[i][size][j], coordPoints[i][size][j + 1], coordPoints[i + 1][size][j + 1]);
            cubeFaces.emplace_back(coordPoints[i][size][j], coordPoints[i + 1][size][j + 1], coordPoints[i + 1][size][j]);
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

    adjacencyMap[coordStr1].insert(coordStr2);
    adjacencyMap[coordStr2].insert(coordStr1);
    
    bool draw = (i1 == i2 && (i1 == size || i1 == 0)) || (j1 == j2 && (j1 == size || j1 == 0)) || (k1 == k2 && (k1 == size || k1 == 0));
    cubeSprings.emplace_back(1.f, 0.7f, 1.f, coordPoints[i1][j1][k1], coordPoints[i2][j2][k2], draw);
}

bool SpringMeshCube::isInBounds(int i, int j, int k) {
    return 0 <= i && i <= size && 0 <= j && j <= size && 0 <= k && k <= size;
}
