#include "PrismEngine.h"
#include "SDL.h"


int main(int argc, char* argv[])
{
    PRISM_Matrix_4X4 m;
    m.m[0][0] = 52.f;
    PRISM_Triangle t = { { 0.0f, 0.0f, 0.0f }, { 0.5f, 0.0f, 0.0f },{ 1.0f, 0.0f, 0.0f } };
    PRISM_Mesh mesh = {};
    PRISM_Color c = {255, 0, 120};
    PRISM_Light light{ {}, {255, 0, 52} };
    PRISM_RenderMode rm;
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

