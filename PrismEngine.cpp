#include "src/PrismEngine.h"



void main_() {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    SDL_Texture* texture;
    int done;
    SDL_Event event;


    if (SDL_CreateWindowAndRenderer(800, 480, SDL_WINDOW_FULLSCREEN_DESKTOP, &window, &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
            "SDL_CreateWindowAndRenderer() failed: %s", SDL_GetError());
        return;
    }

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init() failed :%s", SDL_GetError());
        SDL_Quit();
        return;
    }

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }

    //PRISM_Render PrismRender(renderer);


    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    SDL_SetWindowSize(window, 480, 800);
    AbstractCamera3D MainCamera(0.1, 1000.0f, 90.0f,
        mode.w, mode.h);
    MainCamera.SetPosition({ 0, 1, -30 }, { 0, 0, 0 }, { 0, 0, 1 });
    struct PRISM_Vector3d vectcube = { 0, 0, 8 };
    AbstractObject3D Obj1(vectcube, { 0, 0, 180 }, { 1, 1, 1 }, MainCamera);
    AbstractObject3D Obj2({ 0, 0, 8 }, { 0, 0, 180 }, { 1, 1, 1 }, MainCamera);
    PRISM_Mesh meshObj1;
    meshObj1.tris = {
        // SOUTH
        { {0.0f, 0.0f, 0.0f},    {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 0.0f} },
        { {0.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },

        // EAST
        { {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f} },
        { {1.0f, 0.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 0.0f, 1.0f} },

        // NORTH
        { {1.0f, 0.0f, 1.0f},    {1.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 1.0f} },
        { {1.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 0.0f, 1.0f} },

        // WEST
        { {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 1.0f},    {0.0f, 1.0f, 0.0f} },
        { {0.0f, 0.0f, 1.0f},    {0.0f, 1.0f, 0.0f},    {0.0f, 0.0f, 0.0f} },

        // TOP
        { {0.0f, 1.0f, 0.0f},    {0.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 1.0f} },
        { {0.0f, 1.0f, 0.0f},    {1.0f, 1.0f, 1.0f},    {1.0f, 1.0f, 0.0f} },

        // BOTTOM
        { {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f} },
        { {1.0f, 0.0f, 1.0f},    {0.0f, 0.0f, 0.0f},    {1.0f, 0.0f, 0.0f} },
    };
    //    Obj1.SetMesh(meshObj1);
    Obj1.DownloadFromOBJ("hause2.obj");
    //    Obj2.DownloadFromOBJ("hause2.obj");
    std::vector<Joystick> joysticks(2); // Для двух джойстиков
    InitJoystick(joysticks[0], 300, mode.h - 300, 300, 150, renderer); // Инициализация первого джойстика
    InitJoystick(joysticks[1], mode.w - 300, mode.h - 300, 300, 150, renderer); // Инициализация второго джойстика

    //PrismRender.AddInRender(Obj1);
    //PrismRender.AddInRender(Obj2);

    ToggleButton DisplayTriangleContours;
    ToggleButton DisplayDimming1;
    ToggleButton DisplayDimming2;
    ToggleButton Zbuffer;

    InitToggleButton(DisplayDimming1, 650, 50, 370, 80, true, renderer);
    InitToggleButton(DisplayDimming2, 1040, 50, 370, 80, false, renderer);
    InitToggleButton(DisplayTriangleContours, 50, 50, 580, 80, false, renderer);
    InitToggleButton(Zbuffer, 1435, 50, 260, 80, true, renderer);

    SetToggleButtonText(DisplayDimming1, "DisplayDimming1",
        "fonts/Bartina Semibold.ttf", { 155, 155, 1, 255 }, 64);
    SetToggleButtonText(DisplayDimming2, "DisplayDimming2",
        "fonts/Bartina Semibold.ttf", { 155, 155, 1, 255 }, 64);
    SetToggleButtonText(DisplayTriangleContours, "DisplayTriangleContours",
        "fonts/Bartina Semibold.ttf", { 155, 155, 1, 255 }, 64);
    SetToggleButtonText(Zbuffer, "Zbuffer",
        "fonts/Bartina Semibold.ttf", { 155, 155, 1, 255 }, 64);

    int ftimeline = 1;
    done = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
            {
                done = 1;
            }
            //			HandleInput(event, joysticks, mode.w, mode.h); // Обработка событий для всех джойстиков
            ToggleButtonInput(DisplayDimming1, event);
            ToggleButtonInput(DisplayDimming2, event);
            ToggleButtonInput(DisplayTriangleContours, event);
            ToggleButtonInput(Zbuffer, event);

            const Uint8* state = SDL_GetKeyboardState(NULL);


            if (state[SDL_SCANCODE_ESCAPE]) {
                ;
            }

            if (state[SDL_SCANCODE_UP]) {
                MainCamera.Coordinate.z += 1;
            }

            if (state[SDL_SCANCODE_DOWN]) {
                MainCamera.Coordinate.z -= 1;
            }

            if (state[SDL_SCANCODE_LEFT]) {
                MainCamera.Coordinate.x -= 1;
            }

            if (state[SDL_SCANCODE_RIGHT]) {
                MainCamera.Coordinate.x += 1;
            }

            if (state[SDL_SCANCODE_W]) {
                MainCamera.Coordinate.y -= 1;
            }

            if (state[SDL_SCANCODE_S]) {
                MainCamera.Coordinate.y += 1;
            }

            if (state[SDL_SCANCODE_A]) {
                MainCamera.Rotation.y += 0.1;
            }

            if (state[SDL_SCANCODE_D]) {
                MainCamera.Rotation.y -= 0.1;
            }

            if (state[SDL_SCANCODE_4]) {
                Obj1.Rotation.z -= 1;
            }

            if (state[SDL_SCANCODE_6]) {
                Obj1.Rotation.z += 1;
            }

            if (state[SDL_SCANCODE_8]) {
                Obj1.Rotation.y += 1;
            }

            if (state[SDL_SCANCODE_2]) {
                Obj1.Rotation.y += 1;
            }
            Obj1.SetRotateXYZ(Obj1.Rotation);
            MainCamera.SetPosition(MainCamera.Coordinate, MainCamera.Rotation, { 0, 0, 1 });


        }
        clock_t start = clock();
        //        ftimeline ++;
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        SDL_RenderClear(renderer);
        //		Obj1.Rotation.y += {0, 1, 0};
        //		Obj1.Rotation.z += {0, 0, 0};
        //        Obj1.SetRotateXYZ(Obj1.Rotation);


        //		MainCamera.SetPosition(vectrotcube, {0, 0, 0}, {0, 0, 1});

        //		Obj2.Rotation.y -= vectrotcube.y;
        //		Obj2.Rotation.z -= vectrotcube.z;
        //        Obj2.SetRotateXYZ(Obj2.Rotation);

        //		Normal - {t,f,f,t,f,t,5}
        //        Obj1.DrawMeshTriangles(renderer, {DisplayDimming1.active, DisplayDimming2.active, DisplayTriangleContours.active, Zbuffer.active, false, true, 5});
        //		Obj2.DrawMeshTriangles(renderer, {DisplayDimming1.active, DisplayDimming2.active, DisplayTriangleContours.active, Zbuffer.active, false, true, 5});
        //
        //PrismRender.RenderFrameSurfase(mode.w, mode.h, { DisplayDimming1.active, DisplayDimming2.active, DisplayTriangleContours.active, Zbuffer.active, false, true, 5 });


        RenderToggleButton(DisplayDimming1);
        RenderToggleButton(DisplayDimming2);
        RenderToggleButton(DisplayTriangleContours);
        RenderToggleButton(Zbuffer);


        MainCamera.ClearZ_Buffer(renderer);
        //			SDL_RenderPresent(renderer);

        SDL_Delay(10);

        clock_t end = clock();
        float seconds = (float)(end - start) / CLOCKS_PER_SEC * 1000;
        SDL_Log("Seconds RAN FUNK time ran ms: %f", seconds);
    }

    SDL_Quit();
}


class AbstractObject3D_demo {
private:
    //TRANSFORM
    struct PRISM_Vector3d Coordinate = {0, 0, 0};
    struct PRISM_Vector3d Rotation = { 0, 0, 0 };
    struct PRISM_Vector3d Scale = { 1, 1, 1 };

    //MESH
    struct PRISM_Mesh mesh;
public:
    AbstractObject3D_demo(int i) {}


    PRISM_Vector3d getCoordinate() {
        return Coordinate;
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
        Coordinate = v;
    }

    void setCoordinate(char cordChar, float v) {
        if (cordChar == 'X' || cordChar == 'x') {
            setCoordinate({ v, Coordinate.y, Coordinate.z });
        }
        else if (cordChar == 'Y' || cordChar == 'y') {
            setCoordinate({ Coordinate.x, v, Coordinate.z });
        }
        else if (cordChar == 'Z' || cordChar == 'z') {
            setCoordinate({ Coordinate.x, Coordinate.y, v });
        }
        else if (cordChar == 'W' || cordChar == 'w') {
            setCoordinate({ Coordinate.x, Coordinate.y, Coordinate.z, v });
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


int main(int argc, char* argv[])
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
    PRISM_Window window(600, 400, u8"♦PRISME♦");

    // Проверяем, удалось ли создать окно
    if (!window.isRunning()) {
        return -1;
    }

    Scene scene;
    AbstractCamera3D MainCamera(0.1, 1000.0f, 90.0f,
        window.GetW(), window.GetH());
    MainCamera.SetPosition({ 0, 0, -5 }, { 0, 0, 0 }, { 0, 0, 1 });
    AbstractObject3D object({0, 0, 0}, {0, 0, 0}, {1, 1, 1}, MainCamera);
    object.DownloadFromOBJ("Sphere.obj");
    
    object.materialAmbient = { 0.247f, 0.199f, 0.074f }; //золото
    object.kSpecular = 0.1f;
    scene.AddObject(&object);
    scene.SetCamera(&MainCamera);

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
        object.Rotation.x += 0.1;
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
