#include "helper.h"

#include <Windows.h>

#include "definitions.h"

static inline HWND find_warcraft_hwnd() {
	LPCWSTR kWndClz = TEXT("Warcraft III");
	return FindWindow(kWndClz, NULL);
}

void UpdateBorderVisibility(BOOL visible)
{
	HWND hwnd;
	LONG style1, style2;
	hwnd = find_warcraft_hwnd();
	if (NULL == hwnd)
		return;

	style1 = GetWindowLong(hwnd, GWL_STYLE);
	style2 = visible ? (style1 | WS_OVERLAPPEDWINDOW) : (style1 & ~WS_OVERLAPPEDWINDOW);
	if (style1 == style2)
		return;

	SetWindowLong(hwnd, GWL_STYLE, style2);
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
}

void ResizeWindow()
{
	HWND hwnd;
	RECT rect;
	LONG x, y, w, h;
	hwnd = find_warcraft_hwnd();
	if (NULL == hwnd || !GetWindowRect(hwnd, &rect))
		return;

	x = rect.left;
	y = rect.top;
	w = rect.right - x;
	h = rect.bottom - y;
	MoveWindow(hwnd, x + 1, y + 1, w - 2, h - 2, FALSE);
	MoveWindow(hwnd, x,     y,     w,     h,     TRUE);
}
