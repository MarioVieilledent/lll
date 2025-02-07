#include <math.h>
#include <windows.h>

#define PI 3.14159265358979323846
#define CUBE_SIZE 100
#define SCREEN_DEPTH 400

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawRotatingCube(HDC hdc, int width, int height);

double angle = 0.0;  // Rotation angle

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "CubeWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);

    HWND hwnd = CreateWindow("CubeWindowClass", "3D Rotating Cube (GDI)",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             600, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

void RotatePoint(double *x, double *y, double *z, double ax, double ay,
                 double az) {
    double rx, ry, rz;

    // Rotate around X-axis
    ry = *y * cos(ax) - *z * sin(ax);
    rz = *y * sin(ax) + *z * cos(ax);
    *y = ry;
    *z = rz;

    // Rotate around Y-axis
    rx = *x * cos(ay) + *z * sin(ay);
    *z = -*x * sin(ay) + *z * cos(ay);
    *x = rx;

    // Rotate around Z-axis
    rx = *x * cos(az) - *y * sin(az);
    ry = *x * sin(az) + *y * cos(az);
    *x = rx;
    *y = ry;
}

void ProjectPoint(double x, double y, double z, int width, int height, int *px,
                  int *py) {
    double factor = SCREEN_DEPTH / (SCREEN_DEPTH - z);
    *px = (int)(width / 2 + x * factor);
    *py = (int)(height / 2 - y * factor);
}

void DrawRotatingCube(HDC hdc, int width, int height) {
    double vertices[8][3] = {{-CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
                             {CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE},
                             {CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE},
                             {-CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE},
                             {-CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE},
                             {CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE},
                             {CUBE_SIZE, CUBE_SIZE, CUBE_SIZE},
                             {-CUBE_SIZE, CUBE_SIZE, CUBE_SIZE}};

    int edges[12][2] = {{0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 5}, {5, 6},
                        {6, 7}, {7, 4}, {0, 4}, {1, 5}, {2, 6}, {3, 7}};

    int projected[8][2];

    // Rotate and project each vertex
    for (int i = 0; i < 8; i++) {
        double x = vertices[i][0], y = vertices[i][1], z = vertices[i][2];
        RotatePoint(&x, &y, &z, angle, angle, angle);
        ProjectPoint(x, y, z, width, height, &projected[i][0],
                     &projected[i][1]);
    }

    // Draw edges
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    for (int i = 0; i < 12; i++) {
        MoveToEx(hdc, projected[edges[i][0]][0], projected[edges[i][0]][1],
                 NULL);
        LineTo(hdc, projected[edges[i][1]][0], projected[edges[i][1]][1]);
    }

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    angle += 0.05;  // Increase rotation angle for animation
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam,
                         LPARAM lParam) {
    static UINT_PTR timer = 0;

    switch (message) {
        case WM_CREATE:
            timer = SetTimer(hwnd, 1, 16, NULL);  // Set timer for animation
            break;

        case WM_TIMER:
            InvalidateRect(hwnd, NULL, TRUE);  // Force repaint
            printf("Repainting");
            break;

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            DrawRotatingCube(hdc, rect.right, rect.bottom);
            EndPaint(hwnd, &ps);
            break;
        }

        case WM_DESTROY:
            KillTimer(hwnd, 1);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
