#include "helper.h"

static inline HWND find_war3_hwnd() {
    LPCWSTR kWndClz = TEXT("Warcraft III");
    return FindWindow(kWndClz, NULL);
}

void Helper_OpenFullscreen() {
    HWND hWnd;
    hWnd = find_war3_hwnd();
    if (NULL != hWnd) {
        MoveWindow(hWnd, 0, 0, g_screenWidth, g_screenHeight, TRUE);
    }
}

void Helper_UpdateCursorLockState(BOOL lock) {
    HWND hWnd;
    RECT rect;
    LONG style;
    BOOL hasBorder;
    hWnd = find_war3_hwnd();
    if (NULL == hWnd || !lock || !GetWindowRect(hWnd, &rect)) {
        ClipCursor(NULL);
        return;
    }
    style = GetWindowLong(hWnd, GWL_STYLE);
    hasBorder = 0 != (WS_OVERLAPPEDWINDOW & style);
    if (hasBorder) {
        rect.top    += 32;
        rect.left   += 8;
        rect.right  -= 8;
        rect.bottom -= 8;
    }
    ClipCursor(&rect);
}

void Helper_UpdateBorderVisibility(BOOL visible) {
    HWND hWnd;
    LONG style1, style2;
    hWnd = find_war3_hwnd();
    if (NULL == hWnd) {
        return;
    }
    style1 = GetWindowLong(hWnd, GWL_STYLE);
    style2 = visible ? (WS_OVERLAPPEDWINDOW | style1) : (~WS_OVERLAPPEDWINDOW & style1);
    if (style1 == style2) {
        return;
    }
    SetWindowLong(hWnd, GWL_STYLE, style2);
    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}

void Helper_InvalidateWnd() {
    HWND hWnd;
    RECT rect;
    LONG x, y, w, h;
    hWnd = find_war3_hwnd();
    if (NULL == hWnd || !GetWindowRect(hWnd, &rect)) {
        return;
    }
    x = rect.left;
    y = rect.top;
    w = rect.right - x;
    h = rect.bottom - y;
    Helper_UpdateTaskbarState(FALSE);
    MoveWindow(hWnd, x + 1, y + 1, w - 2, h - 2, FALSE);
    MoveWindow(hWnd, x,     y,     w,     h, TRUE);
    Helper_UpdateTaskbarState(TRUE);
}

void Helper_UpdateTaskbarState(BOOL visible) {
    HWND hWnd = FindWindow(TEXT("Shell_TrayWnd"), NULL);
    if (NULL != hWnd) {
        ShowWindow(hWnd, visible ? SW_SHOW : SW_HIDE);
    }
}
