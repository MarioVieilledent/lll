#ifndef UNICODE
#define UNICODE

#endif

#include <stdio.h>
#include <windows.h>

#include "paint.h"

#define RECT_COUNT 10
#define FRAME_RATE 60

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const COLORREF rgbRed = 0x000000FF;
const COLORREF rgbGreen = 0x0000FF00;
const COLORREF rgbBlue = 0x00FF0000;
const COLORREF rgbBlack = 0x00000000;
const COLORREF rgbWhite = 0x00FFFFFF;

RECT rects[RECT_COUNT];
HDC hMemDC;
HBITMAP hBmp;
HWND hWnd;
HINSTANCE hInst;

int left = 0;
int top = 0;
int right = 0;
int bottom = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine,
                   int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0,                    // Optional window styles.
                               CLASS_NAME,           // Window class
                               L"lll",               // Window text
                               WS_OVERLAPPEDWINDOW,  // Window style

                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                               CW_USEDEFAULT,

                               NULL,       // Parent window
                               NULL,       // Menu
                               hInstance,  // Instance handle
                               NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam,
                            LPARAM lParam) {
    static UINT_PTR timer = 0;
    static PAINTSTRUCT ps;
    static HDC hdc;

    switch (message) {
        case WM_CREATE:
            timer = SetTimer(hWnd, 1, 16, NULL);  // Set timer for animation

            break;

        case WM_TIMER:
            InvalidateRect(hWnd, NULL, TRUE);  // Force repaint
            break;

        case WM_PAINT: {
            // paintWithGDI(hWnd);
            hdc = BeginPaint(hWnd, &ps);

            // Render Scene onto Offscreen Buffer
            render(hWnd, hMemDC, right, bottom);

            // Blit from Offscreen Buffer to Window DC
            BitBlt(hdc, 0, 0, right, bottom, hMemDC, 0, 0, SRCCOPY);

            EndPaint(hWnd, &ps);
            break;
        }

        case WM_SIZE: {
            // Obtain the size of the drawing area.
            RECT rc;
            GetClientRect(hWnd, &rc);
            left = rc.left;
            top = rc.top;
            right = rc.right;
            bottom = rc.bottom;

            hdc = GetDC(hWnd);

            // Create Memory DC and Compatible Bitmap
            hMemDC = CreateCompatibleDC(hdc);
            hBmp = CreateCompatibleBitmap(hdc, right, bottom);
            SelectObject(hMemDC, hBmp);

            ReleaseDC(hWnd, hdc);

            break;
        }

        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        default: {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}