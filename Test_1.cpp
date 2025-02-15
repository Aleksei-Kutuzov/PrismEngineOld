#include "src/PrismEngine.h"


static int test_1() {


    // Создаем окно
    PRISM_Window window(600, 400, u8"♦PRISME♦|TEST 1");

    // Проверяем, удалось ли создать окно
    if (!window.isRunning()) {
        return -1;
    }

    // Главный цикл
    while (window.isRunning()) {

        // Обработка событий
        window.handleEvents();
        PRISM_Painter painter;

        //Отрисовка сцены
        window.clear();


        // Фон (небо и трава)
        painter.DrawRectangle(&window, 1, 1, -1, 0, 135, 206, 235); // Небо (голубой)
        painter.DrawRectangle(&window, 1, 0, -1, -1, 30, 130, 30);  // Трава (зелёный)

        // Солнце
        painter.DrawRectangle(&window, 0.8, 0.8, 0.6, 0.6, 255, 223, 0); // Жёлтый круг (солнце)

        // Облака
        painter.DrawRectangle(&window, -0.8, 0.7, -0.5, 0.6, 255, 255, 255); // Белое облако
        painter.DrawRectangle(&window, -0.5, 0.8, -0.2, 0.7, 255, 255, 255); // Белое облако
        painter.DrawRectangle(&window, 0.2, 0.7, 0.5, 0.6, 255, 255, 255);  // Белое облако

        // Домик
        painter.DrawRectangle(&window, 0.5, 0.5, -0.5, -0.5, 210, 180, 140); // Стены (бежевый)
        painter.DrawTriangle(&window, -0.5, 0.5, 0, 0.9, 0.5, 0.5, 139, 69, 19); // Крыша (коричневая)
        painter.DrawRectangle(&window, 0.125, 0.3, -0.125, -0.4, 139, 69, 19);       // Дверь (коричневая)
        painter.DrawRectangle(&window, 0.4, 0.2, 0.3, 0.0, 173, 216, 230);      // Окно (голубое)
        painter.DrawRectangle(&window, -0.4, 0.2, -0.3, 0.0, 173, 216, 230);    // Окно (голубое)

        // Деревья
        painter.DrawRectangle(&window, -0.8, -0.2, -0.7, -0.5, 139, 69, 19);   // Ствол дерева (коричневый)
        painter.DrawTriangle(&window, -0.9, -0.2, -0.75, 0.2, -0.6, -0.2, 34, 139, 34); // Крона дерева (зелёная)
        painter.DrawRectangle(&window, 0.7, -0.2, 0.8, -0.5, 139, 69, 19);     // Ствол дерева (коричневый)
        painter.DrawTriangle(&window, 0.6, -0.2, 0.75, 0.2, 0.9, -0.2, 34, 139, 34);   // Крона дерева (зелёная)

        // Дорожка к дому
        painter.DrawRectangle(&window, 0.0, -0.5, -0.1, -1, 192, 192, 192); // Серая дорожка

        
       


        window.update();
        Sleep(1);

    }

    return 0;
}