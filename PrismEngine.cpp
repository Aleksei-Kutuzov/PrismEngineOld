#include "src/math/vector3D.h"
#include "src/math/matrix.h"
#include "src/math/other.h"
#include "SDL.h"


int main(int argc, char* argv[])
{
    PRISM_Matrix_4X4 m;
    m.m[0][0] = 52.f;
    PRISM_Triangle t = { { 0.0f, 0.0f, 0.0f }, { 0.5f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } };
    Mesh mesh = {};
    Color c = {255, 0, 120};
    Light light{ {}, {255, 0, 52} };
    RenderMode rm;
    PRISM_Vector3d h = { 1.0f, 0.6f, 1.7f };
    h.print();
    m.print();
    t.print();
    mesh.print();
    c.print();
    light.print();
    rm.print();
    return(0);
}

