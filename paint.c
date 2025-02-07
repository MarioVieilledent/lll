#include "paint.h"

#include <stdio.h>
#include <windows.h>
#define SQUARE 16

// void rect(HWND hWnd, PAINTSTRUCT ps, HPEN hpen, HBRUSH hbrush, int left,
//           int top, int right, int bottom, int r, int g, int b) {
//     // Draw rectangle
//     Rectangle(ps.hdc, left, top, right, bottom);
// }

void render(HWND hWnd, HDC hdc, int right, int bottom) {
    // Save the original object
    HGDIOBJ original = NULL;
    original = SelectObject(hdc, GetStockObject(DC_PEN));

    HPEN hpen;
    HBRUSH hbrush;

    hpen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
    hbrush = CreateSolidBrush(RGB(100, 100, 100));
    SelectObject(hdc, hpen);
    SelectObject(hdc, hbrush);

    Rectangle(hdc, 0, 0, right, bottom);

    hpen = CreatePen(PS_SOLID, 1, RGB(50, 150, 200));
    hbrush = CreateSolidBrush(RGB(50, 150, 200));
    SelectObject(hdc, hpen);
    SelectObject(hdc, hbrush);

    for (int x = 0; x <= right / SQUARE; x++) {
        for (int y = 0; y <= bottom / SQUARE; y++) {
            Rectangle(hdc, SQUARE * x, SQUARE * y, SQUARE * (x + 1),
                      SQUARE * (y + 1));
        }
    }

    DeleteObject(hpen);
    DeleteObject(hbrush);

    // MoveToEx(hdc, 20, 80, NULL);
    // LineTo(hdc, 200, 200);

    // Restore the original object
    SelectObject(hdc, original);
}

void paintWithGDI(HWND hWnd) {
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    RECT clientRect;
    RECT textRect;
    HRGN bgRgn;
    HBRUSH hBrush;
    HPEN hPen;

    hdc = BeginPaint(hWnd, &ps);

    // Fill the client area with a brush
    GetClientRect(hWnd, &clientRect);
    bgRgn = CreateRectRgnIndirect(&clientRect);
    hBrush = CreateSolidBrush(RGB(200, 200, 200));
    FillRgn(hdc, bgRgn, hBrush);

    hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
    SelectObject(hdc, hPen);
    SetBkColor(hdc, RGB(0, 0, 0));
    Rectangle(hdc, 10, 10, 200, 200);

    // Text caption
    SetBkColor(hdc, RGB(255, 255, 255));
    SetRect(&textRect, 10, 210, 200, 200);
    DrawText(hdc, TEXT("PS_DOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);

    hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 255, 255));
    SelectObject(hdc, hPen);
    SetBkColor(hdc, RGB(255, 0, 0));
    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0)));
    Rectangle(hdc, 210, 10, 400, 200);

    // Text caption
    SetBkColor(hdc, RGB(255, 200, 200));
    SetRect(&textRect, 210, 210, 400, 200);
    DrawText(hdc, TEXT("PS_DASHDOTDOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);

    hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
    SelectObject(hdc, hPen);
    SetBkColor(hdc, RGB(255, 255, 0));
    SelectObject(hdc, CreateSolidBrush(RGB(100, 200, 255)));
    Rectangle(hdc, 410, 10, 600, 200);

    // Text caption
    SetBkColor(hdc, RGB(200, 255, 200));
    SetRect(&textRect, 410, 210, 600, 200);
    DrawText(hdc, TEXT("PS_DASHDOT"), -1, &textRect, DT_CENTER | DT_NOCLIP);

    // When fnPenStyle is PS_SOLID, nWidth may be more than 1.
    // Also, if you set the width of any pen to be greater than 1, then it will
    // draw a solid line, even if you try to select another style.
    hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
    SelectObject(hdc, hPen);
    // Setting the background color doesn't matter
    // when the style is PS_SOLID
    SetBkColor(hdc, RGB(255, 255, 255));
    SelectObject(hdc, CreateSolidBrush(RGB(200, 100, 50)));
    Rectangle(hdc, 10, 300, 200, 500);

    // Text caption
    SetBkColor(hdc, RGB(200, 200, 255));
    SetRect(&textRect, 10, 510, 200, 500);
    DrawText(hdc, TEXT("PS_SOLID"), -1, &textRect, DT_CENTER | DT_NOCLIP);

    hPen = CreatePen(PS_DASH, 1, RGB(0, 255, 0));
    SelectObject(hdc, hPen);
    SetBkColor(hdc, RGB(0, 0, 0));
    SelectObject(hdc, CreateSolidBrush(RGB(200, 200, 255)));
    Rectangle(hdc, 210, 300, 400, 500);

    // Text caption
    SetBkColor(hdc, RGB(255, 255, 200));
    SetRect(&textRect, 210, 510, 400, 200);
    DrawText(hdc, TEXT("PS_DASH"), -1, &textRect, DT_CENTER | DT_NOCLIP);

    hPen = CreatePen(PS_NULL, 1, RGB(0, 255, 0));
    SelectObject(hdc, hPen);
    // Setting the background color doesn't matter
    // when the style is PS_NULL
    SetBkColor(hdc, RGB(0, 0, 0));
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255)));
    Rectangle(hdc, 410, 300, 600, 500);

    // Text caption
    SetBkColor(hdc, RGB(200, 255, 255));
    SetRect(&textRect, 410, 510, 600, 500);
    DrawText(hdc, TEXT("PS_NULL"), -1, &textRect, DT_CENTER | DT_NOCLIP);

    // Clean up
    DeleteObject(bgRgn);
    DeleteObject(hBrush);
    DeleteObject(hPen);

    GetStockObject(WHITE_BRUSH);
    GetStockObject(DC_PEN);

    EndPaint(hWnd, &ps);
}