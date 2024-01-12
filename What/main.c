#include "handler.h"

HINSTANCE ghInstance = NULL;
PWSTR     gpCmdLine  = NULL;
int       gnCmdShow  = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	LPCWSTR kWndClz = TEXT("What");
	HWND hwnd;
	WNDCLASS wc;
	MSG msg;
	
	ghInstance = hInstance;
	gpCmdLine  = pCmdLine;
	gnCmdShow  = nCmdShow;

	MEMZERO(wc);
	MEMZERO(msg);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = kWndClz;

	if (!RegisterClass(&wc))
		return 1;

	hwnd = CreateWindowEx(
		0, kWndClz, L"What", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 280, 200,
		NULL, NULL, hInstance, NULL
	);

	if (NULL == hwnd)
		return 2;

	ShowWindow(hwnd, nCmdShow);

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
