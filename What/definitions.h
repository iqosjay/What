#ifndef WHAT_DEFINITIONS_H_
#define WHAT_DEFINITIONS_H_

#include <string.h>

#define MEMZERO(O) do { memset(&O, 0, sizeof(O)); } while (0)

#define HOTKEY_ID_REMOVE_BORDER 0x2000
#define HOTKEY_ID_RESUME_BORDER 0x2001
#define HOTKEY_ID_RESIZE_WINDOW 0x2002

extern HINSTANCE ghInstance;
extern PWSTR     gpCmdLine;
extern int       gnCmdShow;

#endif // !WHAT_DEFINITIONS_H_

