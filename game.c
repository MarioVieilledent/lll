#ifndef UNICODE
#define UNICODE
#endif

#include <stdio.h>
#include <windows.h>

#include "paint.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

const COLORREF rgbRed = 0x000000FF;
const COLORREF rgbGreen = 0x0000FF00;
const COLORREF rgbBlue = 0x00FF0000;
const COLORREF rgbBlack = 0x00000000;
const COLORREF rgbWhite = 0x00FFFFFF;

int val = 17;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine,
                   int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0,           // Optional window styles.
                               CLASS_NAME,  // Window class
                               L"Learn to Program Windows",  // Window text
                               WS_OVERLAPPEDWINDOW,          // Window style

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
    switch (message) {
        case WM_PAINT: {
            paintWithGDI(hWnd);
            break;
        }

            // case WM_PAINT: {
            //     paintWithDirect2d(hWnd);
            //     break;
            // }

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

/*
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
        case WM_SIZE: {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            // HBRUSH myHBrush = CreateSolidBrush(rgbRed);
            FillRect(hdc, &ps.rcPaint, (HBRUSH)());

            EndPaint(hwnd, &ps);
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
*/