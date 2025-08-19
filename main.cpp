#include <windows.h>
#include <stdio.h>
#include "KWnd.h"


// Левая клавиша мыши
int ClickLeftMouseButton()
{
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    return 0;
}


// Правая клавиша мыши
int ClickRightMouseButton()
{
    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
    return 0;
}


// Прототип оконной процедуры
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    KWnd mainWnd("Виртуальная мышка", hInstance, nCmdShow, WndProc, NULL, 100, 100,
        250, 85);

    MessageBox(NULL, "Виртуальная мышка включена. Нажмите ENTER, чтобы продолжить.",
               "Внимание", MB_OK | MB_ICONASTERISK);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
    WPARAM wParam, LPARAM lParam)
{
    static int xPos = 200, yPos = 200;
    PAINTSTRUCT ps;
    HDC hDC;
    char text[100];
    char text1[100];
    RECT rect;
    RECT rect1;
    SetRect(&rect, 10, 0, 200, 30); // Прямоугольник 200x30, x = 10, y = 0
    SetRect(&rect1, 10, 20, 200, 45); // Прямоугольник1 200x45, x = 10, y = 20

    switch (uMsg)
    {
    case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        sprintf(text, "Координаты курсора мыши:");
        sprintf(text1, "xPos = %d, yPos = %d", xPos, yPos);
        DrawText(hDC, text, -1, &rect, DT_LEFT);
        DrawText(hDC, text1, -1, &rect1, DT_LEFT);
        EndPaint(hWnd, &ps);
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            xPos = xPos - 5;
            InvalidateRect(hWnd, NULL, TRUE);  // Запрос перерисовки окна
            break;
        case VK_RIGHT:
            xPos = xPos + 5;
            InvalidateRect(hWnd, NULL, TRUE);  // Запрос перерисовки окна
            break;
        case VK_UP:
            yPos = yPos - 5;
            InvalidateRect(hWnd, NULL, TRUE); // Запрос перерисовки окна
            break;
        case VK_DOWN:
            yPos = yPos + 5;
            InvalidateRect(hWnd, NULL, TRUE); // Запрос перерисовки окна
            break;
        case VK_RETURN: // Клавиша ENTER - ЛЕВАЯ КНОПКА МЫШИ
            ClickLeftMouseButton();
            break;
        case VK_SPACE: // Клавиша ПРОБЕЛ - ПРАВАЯ КНОПКА МЫШИ
            ClickRightMouseButton();
            break;
            }
            SetCursorPos(xPos, yPos); // Перемещаем курсор мыши
            break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
