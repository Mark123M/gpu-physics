#include "plane.h"

Plane::Plane(glm::vec3 origin, glm::vec3 dir1, glm::vec3 dir2, float width, float height): width{width}, height{height}, origin{origin}, v1{origin + width * dir1},
    v2{v1 + height * dir2}, v3{origin + height * dir2}, normal{glm::normalize(glm::cross(dir2, dir1))} {}

void Plane::draw() {
    // Front side
    /*DrawTriangle3D(v3, v1, origin, MYGREEN);
    DrawTriangle3D(v3, v2, v1, MYGREEN);
    
    // Back side
    DrawTriangle3D(v1, v3, origin, MYBLUE);
    DrawTriangle3D(v1, v2, v3, MYBLUE); */

    // Generate VBO and EBO
    // Generate VAO for buffers and configurations

}

std::string Plane::stringify()
{
    return std::string();
}
