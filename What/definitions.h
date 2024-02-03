#ifndef WHAT_DEFINITIONS_H_
#define WHAT_DEFINITIONS_H_

#include <Windows.h>

#define MEMZERO(O) do { memset(&O, 0, sizeof(O)); } while (0)

#define HOTKEY_ID_SHOW_BORDER    0x2000
#define HOTKEY_ID_HIDE_BORDER    0x2001
#define HOTKEY_ID_FULLSCREEN     0x2002
#define HOTKEY_ID_LOCK_CURSOR    0x2003
#define HOTKEY_ID_RELEASE_CURSOR 0x2004
#define HOTKEY_ID_INVALIDATE_WND 0x2005

extern HINSTANCE g_hInstance;
extern PWSTR     g_CmdLine;
extern int       g_CmdShow;
extern int       g_ScreenWidth;
extern int       g_ScreenHeight;

#endif // !WHAT_DEFINITIONS_H_

