#include "helper.h"

static inline HWND find_warcraft_hwnd() {
  LPCWSTR kWndClz = TEXT("Warcraft III");
  return FindWindow(kWndClz, NULL);
}

void Helper_OpenFullscreen() {
  HWND hwnd;
  hwnd = find_warcraft_hwnd();
  if (NULL != hwnd) {
    MoveWindow(hwnd, 0, 0, g_screen_w_, g_screen_h_, TRUE);
  }
}

void Helper_UpdateCursorLockState(BOOL lock) {
  HWND hwnd;
  RECT rect;
  LONG style;
  BOOL fullscreen;
  hwnd = find_warcraft_hwnd();
  if (NULL == hwnd) {
    return;
  }
  if (!lock || !GetWindowRect(hwnd, &rect)) {
    ClipCursor(NULL);
    return;
  }
  style = GetWindowLong(hwnd, GWL_STYLE);
  fullscreen = 0 == (style & WS_OVERLAPPEDWINDOW);
  rect.top += fullscreen ? 0 : 32;
  rect.left += 8;
  rect.right -= 8;
  rect.bottom -= 8;
  ClipCursor(&rect);
}

void Helper_UpdateBorderVisibility(BOOL visible) {
  HWND hwnd;
  LONG style1, style2;
  hwnd = find_warcraft_hwnd();
  if (NULL == hwnd) {
    return;
  }
  style1 = GetWindowLong(hwnd, GWL_STYLE);
  style2 = visible ? (style1 | WS_OVERLAPPEDWINDOW) : (style1 & ~WS_OVERLAPPEDWINDOW);
  if (style1 == style2) {
    return;
  }
  SetWindowLong(hwnd, GWL_STYLE, style2);
  SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}

void Helper_InvalidateWnd() {
  HWND hwnd;
  RECT rect;
  LONG x, y, w, h;
  hwnd = find_warcraft_hwnd();
  if (NULL == hwnd || !GetWindowRect(hwnd, &rect)) {
    return;
  }
  x = rect.left;
  y = rect.top;
  w = rect.right - x;
  h = rect.bottom - y;
  MoveWindow(hwnd, x + 1, y + 1, w - 2, h - 2, FALSE);
  MoveWindow(hwnd, x, y, w, h, TRUE);
}
