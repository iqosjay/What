#include "handler.h"

#include "helper.h"

static void RegisterHotkeys(HWND hwnd);
static void OnHotkey(HWND hwnd, WPARAM wParam);
static void UnregisterHotkeys(HWND hwnd);
static void OnPaint(HWND hwnd);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		RegisterHotkeys(hwnd);
		break;
	case WM_DESTROY:
		UnregisterHotkeys(hwnd);
		PostQuitMessage(0);
		return 0;
	case WM_HOTKEY:
		OnHotkey(hwnd, wParam);
		break;
	case WM_PAINT:
		OnPaint(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

static void RegisterHotkeys(HWND hwnd)
{
	RegisterHotKey(hwnd, HOTKEY_ID_RESIZE_WINDOW, MOD_CONTROL | MOD_SHIFT, 'Z');
	RegisterHotKey(hwnd, HOTKEY_ID_REMOVE_BORDER, MOD_CONTROL | MOD_SHIFT, 'O');
	RegisterHotKey(hwnd, HOTKEY_ID_RESUME_BORDER, MOD_CONTROL,             'O');
}

static void OnHotkey(HWND hwnd, WPARAM wParam)
{
	switch (wParam)
	{
	case HOTKEY_ID_RESIZE_WINDOW:
		ResizeWindow();
		break;
	case HOTKEY_ID_REMOVE_BORDER:
		UpdateBorderVisibility(FALSE);
		break;
	case HOTKEY_ID_RESUME_BORDER:
		UpdateBorderVisibility(TRUE);
		break;
	}
}

static void UnregisterHotkeys(HWND hwnd)
{
	UnregisterHotKey(hwnd, HOTKEY_ID_RESIZE_WINDOW);
	UnregisterHotKey(hwnd, HOTKEY_ID_REMOVE_BORDER);
	UnregisterHotKey(hwnd, HOTKEY_ID_RESUME_BORDER);
}


static void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC hdc;
	hdc = BeginPaint(hwnd, &ps);
	FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
	EndPaint(hwnd, &ps);
}