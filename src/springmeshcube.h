#include "springmesh.h"
#include <unordered_set>
#include <unordered_map>

class SpringMeshCube: public SpringMesh {
protected:
    // Passed by reference into springmesh constructor after initialization
    std::vector<Point> cubePoints;
    std::vector<Spring> cubeSprings;
    std::vector<Face> cubeFaces;

    int size;
    std::vector<std::vector<std::vector<Point>>> coordPoints;
    std::unordered_map<std::string, std::unordered_set<std::string>> adjacencyMap;
public:
    SpringMeshCube(int size, std::vector<std::unique_ptr<Collider>> &colliders, FileLogger &logger);
    void initSprings();
    void initFaces();
    bool canCreateSpring(int i1, int j1, int k1, int i2, int j2, int k2);
    bool isInBounds(int i, int j, int k);
};
