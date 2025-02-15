#include "src/PrismEngine.h"
#include <cstdlib>
#include <crtdbg.h>
#include "Test_1.cpp"
#include "Test_2.cpp"
#include "Test_3.cpp"

int main(int argc, char* argv[]) {
    return test_3();
}

class AbstractObject3D_demo {
private:
    //TRANSFORM
    struct PRISM_Vector3d Translate = {0, 0, 0};
    struct PRISM_Vector3d Rotation = { 0, 0, 0 };
    struct PRISM_Vector3d Scale = { 1, 1, 1 };

    //MESH
    struct PRISM_Mesh mesh;
public:
    AbstractObject3D_demo(int i) {}


    PRISM_Vector3d getCoordinate() {
        return Translate;
    }
    float getCoordinate(char cordChar) {
        if (cordChar == 'X' || cordChar == 'x') {
            return getCoordinate().x;
        }
        else if (cordChar == 'Y' || cordChar == 'y') {
            return getCoordinate().y;
        }
        else if (cordChar == 'Z' || cordChar == 'z') {
            return getCoordinate().z;
        }
        else if (cordChar == 'W' || cordChar == 'w') {
            return getCoordinate().w;
        }
        else {
            SDL_Log("the 'Coordinate' field does not have the '%c' component called", cordChar);
        }
    }

    void setCoordinate(PRISM_Vector3d v) {
        // @@@
        Translate = v;
    }

    void setCoordinate(char cordChar, float v) {
        if (cordChar == 'X' || cordChar == 'x') {
            setCoordinate({ v, Translate.y, Translate.z });
        }
        else if (cordChar == 'Y' || cordChar == 'y') {
            setCoordinate({ Translate.x, v, Translate.z });
        }
        else if (cordChar == 'Z' || cordChar == 'z') {
            setCoordinate({ Translate.x, Translate.y, v });
        }
        else if (cordChar == 'W' || cordChar == 'w') {
            setCoordinate({ Translate.x, Translate.y, Translate.z, v });
        }
        else {
            SDL_Log("the 'Coordinate' field does not have the '%c' component called", cordChar);
        }
    }


    PRISM_Vector3d getRotation() {
        return Rotation;
    }
    float getRotation(char rotChar) {
        if (rotChar == 'X' || rotChar == 'x') {
            return getRotation().x;
        }
        else if (rotChar == 'Y' || rotChar == 'y') {
            return getRotation().y;
        }
        else if (rotChar == 'Z' || rotChar == 'z') {
            return getRotation().z;
        }
        else if (rotChar == 'W' || rotChar == 'w') {
            return getRotation().w;
        }
        else {
            SDL_Log("the 'Rotation' field does not have the '%c' component called", rotChar);
        }
    }
    void setRotation(PRISM_Vector3d v) {
        // @@@
        Rotation = v;
    }
    void setRotation(char cordChar, float v) {
        if (cordChar == 'X' || cordChar == 'x') {
            setRotation({ v, Rotation.y, Rotation.z });
        }
        else if (cordChar == 'Y' || cordChar == 'y') {
            setRotation({ Rotation.x, v, Rotation.z });
        }
        else if (cordChar == 'Z' || cordChar == 'z') {
            setRotation({ Rotation.x, Rotation.y, v });
        }
        else if (cordChar == 'W' || cordChar == 'w') {
            setRotation({ Rotation.x, Rotation.y, Rotation.z, v });
        }
        else {
            SDL_Log("the 'Rotation' field does not have the '%c' component called", cordChar);
        }
    }

    PRISM_Vector3d getScale() {
        return Scale;
    }
    float getScale(char sclChar) {
        if (sclChar == 'X' || sclChar == 'x') {
            return getScale().x;
        }
        else if (sclChar == 'Y' || sclChar == 'y') {
            return getScale().y;
        }
        else if (sclChar == 'Z' || sclChar == 'z') {
            return getScale().z;
        }
        else if (sclChar == 'W' || sclChar == 'w') {
            return getScale().w;
        }
        else {
            SDL_Log("the 'Scale' field does not have the '%c' component called", sclChar);
        }
    }
    void setScale(PRISM_Vector3d v) {
        // @@@
        Scale = v;
    }
    void setScale(char cordChar, float v) {
        if (cordChar == 'X' || cordChar == 'x') {
            setScale({ v, Scale.y, Scale.z });
        }
        else if (cordChar == 'Y' || cordChar == 'y') {
            setScale({ Scale.x, v, Scale.z });
        }
        else if (cordChar == 'Z' || cordChar == 'z') {
            setScale({ Scale.x, Scale.y, v });
        }
        else if (cordChar == 'W' || cordChar == 'w') {
            setScale({ Scale.x, Scale.y, Scale.z, v });
        }
        else {
            SDL_Log("the 'Scale' field does not have the '%c' component called", cordChar);
        }
    }

    void SetMesh(struct PRISM_Mesh m) {
        mesh = m;
    }

    PRISM_Mesh GetMesh() {
        return mesh;
    }

};


int __main(int argc, char* argv[])
{

    //test_Zbuff();
    //main_();
    AbstractObject3D_demo t(1);
    t.setCoordinate({ 1, 1, 1 });
    t.setCoordinate('X', 52);
    t.setRotation({ 2, 2, 2 });
    t.setRotation('Y', 52);
    t.setScale({ 3, 3, 3 });
    t.setScale('Z', 52);
    t.getCoordinate().print();
    t.getRotation().print();
    t.getScale().print();
    SDL_Log("==========================");
    SDL_Log("X %f", t.getScale('X'));
    SDL_Log("Y %f", t.getScale('y'));
    SDL_Log("Z %f", t.getScale('z'));

    t.SetMesh({ { { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} }, PRISM_Triangle(),    PRISM_Triangle() } });
    t.GetMesh().print();
    SDL_Log("==========================");
    AbstractCamera3D cam(0.1, 1000.0f, 90.0f, 1, 1);
    AbstractObject3D o({ 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 }, cam);

    Scene c = Scene();
    c.PrintInfo();
    c.AddObject(&o);
    c.PrintInfo();
    c.DelObject(&o);
    SDL_Log("==========================");
    c.PrintInfo();

    // Создаем окно
    PRISM_Window window(600, 400, u8"♦PRISME♦|IT IS TEST");

    // Проверяем, удалось ли создать окно
    if (!window.isRunning()) {
        return -1;
    }

    Scene scene;
    AbstractCamera3D MainCamera(0.1, 1000.0f, 90.0f,
        window.GetW(), window.GetH());
    MainCamera.SetPosition({ 0, 0, -4 }, { 0, 0, 0 }, { 0, 0, 1 });
    
    AbstractObject3D object{ {0,0,0},{0,0,0},{1,1,1},MainCamera };

    object.SetMesh(MeshLoader::LoadOBJ("test_res/objs/sphere.obj", MainCamera));
    //object.SetMesh(MeshLoader::LoadOBJ("test_res/objs/planet.obj", MainCamera));
    
    //object.mesh.print();

    scene.AddObject(&object);
    scene.SetCamera(&MainCamera);

    //ShaderManager shm;
    //shm.initShaders();

    clock_t start, end;
    // Главный цикл
    while (window.isRunning()) {
        clock_t start, end;
        start = clock();
        // Обработка событий
        window.handleEvents();
        PRISM_Painter painter;
        
         //Отрисовка сцены
        window.clear();
        scene.Render(&window);
        object.Rotation.y += 0.1;
        object.SetRotateXYZ(object.Rotation);
        //painter.DrawTriangle3D(&window,
        //    0, 100, 0, 
        //    100, 200, 0,
        //    200, 100, 0.2f, 1.0f, 0.0f, 0.0f);  // Красный
        //painter.DrawTriangle3D(&window,
        //    0, 40, 0.1,
        //    60, 400, 0.1,
        //    140, 80, 0.1, 0.0f, 1.0f, 0.0f);  // Зеленый
        //painter.DrawRectangle(&window, 0, 0, 100, 100);

        end = clock();
        double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
        SDL_Log("Time taken by program is : %f sec", time_taken);

        window.update();
        Sleep(1);
        
    }

    return 0;

    // GL_test();
    return(0);
}

int _main(int argc, char* argv[])
{
    // Создаем окно
    PRISM_Window window(600, 400, u8"♦PRISME♦");

    // Проверяем, удалось ли создать окно
    if (!window.isRunning()) {
        return -1;
    }
    
    PRISM_Painter painter;
    
    // Главный цикл
    while (window.isRunning()) {
        // Обработка событий
        window.handleEvents();

        //Отрисовка сцены
        window.clear();
        //window.shaderManager.render();

        painter.DrawTriangle3D(&window, -0.2f, -0.4f, 0.f,
                                         -0.1f, 0.5f, 0.f,
                                         0.5f, -0.5f, 0.2f, 255, 0, 0);
        painter.DrawTriangle3D(&window, { { -0.7f, 0.5f, 0.1f},
                                          {0.f, 0.8f, 0.1f},
                                          {0.6f, -0.5f, 0.1f} }, 255, 255, 100 );
        painter.DrawThickLine(&window, -1.f, -1.f, 1.f, 1.f, 25, 0, 0, 255);
        painter.DrawRectangle(&window, -0.5f, -0.5f, 0.5f, 0.2f, 255, 0, 255);
        painter.DrawPoint(&window, -0.6f, -0.1f, 0, 255, 255);
        window.update();
        Sleep(10);

    }

    return 0;
}
