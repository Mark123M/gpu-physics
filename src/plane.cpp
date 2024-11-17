#include "plane.h"

#define MYGREEN      CLITERAL(Color){ 0, 228, 48, 100 }
#define MYBLUE       CLITERAL(Color){ 0, 121, 241, 100 }  

Plane::Plane(Vector3 origin, Vector3 dir1, Vector3 dir2, float width, float height): width{width}, height{height}, origin{origin}, v1{Vector3Add(origin, Vector3Scale(dir1, width))},
    v2{Vector3Add(v1, Vector3Scale(dir2, height))}, v3{Vector3Add(origin, Vector3Scale(dir2, height))}, normal{Vector3Normalize(Vector3CrossProduct(dir2, dir1))} {}

void Plane::draw() {
    //front-side
    DrawTriangle3D(v3, v1, origin, MYGREEN);
    DrawTriangle3D(v3, v2, v1, MYGREEN);
    
    // back-side
    DrawTriangle3D(v1, v3, origin, MYBLUE);
    DrawTriangle3D(v1, v2, v3, MYBLUE);
}
