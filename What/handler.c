#include "handler.h"

#include "helper.h"

static void RegisterHotkeys(HWND hwnd);
static void OnHotkey(HWND hwnd, WPARAM wp);
static void UnregisterHotkeys(HWND hwnd);
static void OnPaint(HWND hwnd);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  switch (msg) {
    case WM_CREATE:
      RegisterHotkeys(hwnd);
      break;
    case WM_DESTROY:
      UnregisterHotkeys(hwnd);
      Helper_UpdateTaskbarState(TRUE);
      PostQuitMessage(0);
      return 0;
    case WM_HOTKEY:
      OnHotkey(hwnd, wp);
      break;
    case WM_PAINT:
      OnPaint(hwnd);
      return 0;
  }
  return DefWindowProc(hwnd, msg, wp, lp);
}

static void RegisterHotkeys(HWND hwnd) {
  RegisterHotKey(hwnd, HOTKEY_ID_HIDE_BORDER,     MOD_CONTROL | MOD_SHIFT,  'O');
  RegisterHotKey(hwnd, HOTKEY_ID_SHOW_BORDER,     MOD_CONTROL,              'O');
  RegisterHotKey(hwnd, HOTKEY_ID_LOCK_CURSOR,     MOD_CONTROL | MOD_SHIFT,  'L');
  RegisterHotKey(hwnd, HOTKEY_ID_RELEASE_CURSOR,  MOD_CONTROL,              'L');
  RegisterHotKey(hwnd, HOTKEY_ID_FULLSCREEN,      MOD_CONTROL | MOD_SHIFT,  'F');
  RegisterHotKey(hwnd, HOTKEY_ID_INVALIDATE_WND,  MOD_CONTROL | MOD_SHIFT,  'Z');
}

static void OnHotkey(HWND hwnd, WPARAM wp) {
  switch (wp) {
    case HOTKEY_ID_SHOW_BORDER:
      Helper_UpdateBorderVisibility(TRUE);
      break;
    case HOTKEY_ID_HIDE_BORDER:
      Helper_UpdateBorderVisibility(FALSE);
      break;
    case HOTKEY_ID_LOCK_CURSOR:
      Helper_UpdateCursorLockState(TRUE);
      break;
    case HOTKEY_ID_RELEASE_CURSOR:
      Helper_UpdateCursorLockState(FALSE);
      break;
    case HOTKEY_ID_FULLSCREEN:
      Helper_OpenFullscreen();
      break;
    case HOTKEY_ID_INVALIDATE_WND:
      Helper_InvalidateWnd();
      break;
  }
}

static void UnregisterHotkeys(HWND hwnd) {
  UnregisterHotKey(hwnd, HOTKEY_ID_HIDE_BORDER);
  UnregisterHotKey(hwnd, HOTKEY_ID_SHOW_BORDER);
  UnregisterHotKey(hwnd, HOTKEY_ID_FULLSCREEN);
  UnregisterHotKey(hwnd, HOTKEY_ID_LOCK_CURSOR);
  UnregisterHotKey(hwnd, HOTKEY_ID_RELEASE_CURSOR);
  UnregisterHotKey(hwnd, HOTKEY_ID_INVALIDATE_WND);
}


static void OnPaint(HWND hwnd) {
  PAINTSTRUCT ps;
  RECT text_area;
  HFONT h_font;
  HDC hdc;
  hdc = BeginPaint(hwnd, &ps);
  FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
  SetTextColor(hdc, RGB(0, 0, 0)); 
  SetBkMode(hdc, TRANSPARENT);
  LPCWSTR kUsage = L"以窗口模式运行 War3\n"
    L"CTRL + SHIFT + O 去除 War3 边框\n"
    L"CTRL + SHIFT + L 窗口模式鼠标锁定\n"
    L"CTRL + O 恢复 War3 边框\n"
    L"CTRL + L 解除窗口鼠标锁定\n"
    L"CTRL + SHIFT + Z 会刷新 War 窗口\n"
    L"只要出现字体重叠就 CTRL + SHIFT + Z";
                  
  h_font = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
    VARIABLE_PITCH, TEXT("微软雅黑"));
  SelectObject(hdc, h_font);
  text_area.left   = 64;
  text_area.top    = 48;
  text_area.right  = 480;
  text_area.bottom = 320;
  DrawTextW(hdc, kUsage, -1, &text_area, DT_LEFT | DT_WORDBREAK);
  EndPaint(hwnd, &ps);
}