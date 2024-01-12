#include "handler.h"

HINSTANCE g_instance_ = NULL;
PWSTR     g_cmd_line_ = NULL;
int       g_cmd_show_ = 0;
int       g_screen_w_ = 0;
int       g_screen_h_ = 0;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE _, PWSTR cmd_line, int cmd_show) {
  LPCWSTR kWndClz = TEXT("Warcraft III Helper");
  const int kWndW = 480;
  const int kWndH = 320;
  HWND hwnd;
  WNDCLASS wc;
  MSG msg;

  g_instance_ = instance;
  g_cmd_line_ = cmd_line;
  g_cmd_show_ = cmd_show;
  g_screen_w_ = GetSystemMetrics(SM_CXSCREEN);
  g_screen_h_ = GetSystemMetrics(SM_CYSCREEN);

  MEMZERO(wc);
  MEMZERO(msg);
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = instance;
  wc.lpszClassName = kWndClz;
  if (!RegisterClass(&wc)) {
    return 1;
  }
  hwnd = CreateWindowEx(WS_EX_DLGMODALFRAME,
    kWndClz, L"×ÖÌåÖØµşĞŞ¸´",
    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
    (g_screen_w_ - kWndW) >> 1, (g_screen_h_ - kWndH) >> 1, kWndW, kWndH,
    NULL, NULL, instance, NULL
  );
  if (NULL == hwnd) {
    return 2;
  }
  ShowWindow(hwnd, cmd_show);
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}
