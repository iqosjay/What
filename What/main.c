#include "handler.h"

HINSTANCE g_hInstance    = NULL;
PWSTR     g_CmdLine      = NULL;
int       g_CmdShow      = 0;
int       g_ScreenWidth  = 0;
int       g_ScreenHeight = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpCmdLine, int nCmdShow) {
    LPCWSTR kWndClz = TEXT("Warcraft III Helper");
    const int kWndW = 480;
    const int kWndH = 320;
    HWND hWnd;
    WNDCLASS wc;
    MSG msg;

    g_hInstance    = hInstance;
    g_CmdLine      = lpCmdLine;
    g_CmdShow      = nCmdShow;
    g_ScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
    g_ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    MEMZERO(wc);
    MEMZERO(msg);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = kWndClz;
    if (!RegisterClass(&wc)) {
        return 1;
    }
    hWnd = CreateWindowEx(WS_EX_DLGMODALFRAME,
        kWndClz, TEXT("Warcraft III ×ÖÌåĞŞ¸´¹¤¾ß"), WS_OVERLAPPEDWINDOW,
        (g_ScreenWidth - kWndW) >> 1, (g_ScreenHeight - kWndH) >> 1, kWndW, kWndH,
        NULL, NULL, hInstance, NULL
    );
    if (NULL == hWnd) {
        return 2;
    }
    ShowWindow(hWnd, nCmdShow);
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
