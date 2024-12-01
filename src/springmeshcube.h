#include "springmesh.h"
#include <unordered_set>
#include <unordered_map>

class SpringMeshCube: public SpringMesh {
protected:
    // Passed by reference into springmesh constructor after initialization
    std::vector<Point> cpoints;
    std::vector<Spring> csprings;
    std::vector<Face> cfaces;
    std::unordered_map<std::string, std::unordered_set<std::string>> adjacencyMap;
    int size;
public:
    SpringMeshCube(int size, std::vector<Plane> &colliders, FileLogger &logger);
    void initSprings();
    void createSpring(int i1, int j1, int k1, int i2, int j2, int k2);
    bool canCreateSpring(int i1, int j1, int k1, int i2, int j2, int k2);
    bool isInBounds(int i, int j, int k);
};
