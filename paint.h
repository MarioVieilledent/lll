#ifndef PAINT_H
#define PAINT_H

#include <windows.h>

#include "paint.h"

void render(HWND hWnd, HDC hdc, int right, int bottom);
void paintWithGDI(HWND hWnd);

#endif