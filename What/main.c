#include "handler.h"

HINSTANCE g_hInstance    = NULL;
PWSTR     g_lpCmdLine    = NULL;
int       g_nCmdShow     = 0;
int       g_screenWidth  = 0;
int       g_screenHeight = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    LPCWSTR kWndClz = TEXT("Warcraft III Helper");
    const int kWndW = 480;
    const int kWndH = 320;
    WNDCLASS wc;
    HWND hWnd;
    MSG msg;

    g_hInstance    = hInstance;
    g_lpCmdLine    = lpCmdLine;
    g_nCmdShow     = nCmdShow;
    g_screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    g_screenHeight = GetSystemMetrics(SM_CYSCREEN);

    MEMZERO(wc);
    MEMZERO(msg);

    wc.lpfnWndProc   = OnWndProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = kWndClz;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, TEXT("无法注册窗口类"), TEXT("错误"), MB_OK);
        return 1;
    }
    hWnd = CreateWindowEx(WS_EX_DLGMODALFRAME,
        kWndClz, TEXT("Warcraft III 字体修复工具"), WS_OVERLAPPEDWINDOW,
        (g_screenWidth - kWndW) >> 1, (g_screenHeight - kWndH) >> 1, kWndW, kWndH,
        NULL, NULL, hInstance, NULL
    );
    if (NULL == hWnd) {
        MessageBox(NULL, TEXT("窗口创建失败"), TEXT("错误"), MB_OK);
        return 2;
    }
    ShowWindow(hWnd, nCmdShow);
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
