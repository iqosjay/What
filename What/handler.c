#include "handler.h"

static void  RegisterHotkeys(HWND hWnd);
static void  OnHotkey(HWND hWnd, WPARAM wParam);
static void  UnregisterHotkeys(HWND hWnd);
static void  OnPaint(HWND hWnd);
static HFONT Font();

LRESULT CALLBACK OnWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CREATE:
            RegisterHotkeys(hWnd);
            break;
        case WM_DESTROY:
            UnregisterHotkeys(hWnd);
            Helper_UpdateTaskbarState(TRUE);
            PostQuitMessage(0);
            return 0;
        case WM_HOTKEY:
            OnHotkey(hWnd, wParam);
            break;
        case WM_PAINT:
            OnPaint(hWnd);
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

static void RegisterHotkeys(HWND hWnd) {
    RegisterHotKey(hWnd, HOTKEY_ID_HIDE_BORDER,     MOD_CONTROL | MOD_SHIFT, 'O');
    RegisterHotKey(hWnd, HOTKEY_ID_FULLSCREEN,      MOD_CONTROL | MOD_SHIFT, 'F');
    RegisterHotKey(hWnd, HOTKEY_ID_LOCK_CURSOR,     MOD_CONTROL | MOD_SHIFT, 'L');
    RegisterHotKey(hWnd, HOTKEY_ID_SHOW_BORDER,     MOD_CONTROL | MOD_ALT,   'O');
    RegisterHotKey(hWnd, HOTKEY_ID_RELEASE_CURSOR,  MOD_CONTROL | MOD_ALT,   'L');
    RegisterHotKey(hWnd, HOTKEY_ID_INVALIDATE_WND,  MOD_CONTROL | MOD_SHIFT, 'Z');
}

static void OnHotkey(HWND hWnd, WPARAM wParam) {
    switch (wParam) {
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

static void UnregisterHotkeys(HWND hWnd) {
    UnregisterHotKey(hWnd, HOTKEY_ID_HIDE_BORDER);
    UnregisterHotKey(hWnd, HOTKEY_ID_SHOW_BORDER);
    UnregisterHotKey(hWnd, HOTKEY_ID_FULLSCREEN);
    UnregisterHotKey(hWnd, HOTKEY_ID_LOCK_CURSOR);
    UnregisterHotKey(hWnd, HOTKEY_ID_RELEASE_CURSOR);
    UnregisterHotKey(hWnd, HOTKEY_ID_INVALIDATE_WND);
}

static HFONT Font() {
    static HFONT hFont = NULL;
    if (NULL == hFont) {
        hFont = CreateFont(0, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            VARIABLE_PITCH, TEXT("微软雅黑"));
    }
    return hFont;
}


static void OnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    RECT textArea;
    HDC hdc;
    MEMZERO(textArea);
    hdc = BeginPaint(hWnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT);
    LPCWSTR kUsage = TEXT("以窗口模式运行 War3\n")
        TEXT("去除窗口边框：CTRL + SHIFT + O\n")
        TEXT("窗口全屏展示：CTRL + SHIFT + F\n")
        TEXT("窗口模式锁鼠：CTRL + SHIFT + L\n")
        TEXT("恢复窗口边框：CTRL + ALT + O\n")
        TEXT("解除鼠标锁定：CTRL + ALT + L\n")
        TEXT("强制刷新窗口：CTRL + SHIFT + Z\n")
        TEXT("只要字体重叠就按 CTRL + SHIFT + Z";)
    SelectObject(hdc, Font());
    textArea.left   = 64;
    textArea.top    = 48;
    textArea.right  = 480;
    textArea.bottom = 320;
    DrawText(hdc, kUsage, -1, &textArea, DT_LEFT | DT_WORDBREAK);
    EndPaint(hWnd, &ps);
}