#ifndef _HGFX_H_
#define _HGFX_H_

///Author: s10172747k
///Description: This is a console graphics library
///             to prevent my ctrl, c and v keys
///             from dropping off due to overuse.

#include <_mingw.h>

#include <windows.h>

#ifndef _WINDOWS_H || _WINDOWS_
#error [HGFX] Missing windows.h
#endif

#ifndef _RGBI_DEFINED
#define _RGBI_DEFINED
typedef  struct  {
    int R;
    int G;
    int B;
    int I;
  } RGBI;
#else
#warning [HGFX] RGBI (Type: Struct) is already defined

#endif

#define fdefault 0x1|0x2|0x4
#define bdefault 0

#define cRed 0x4
#define cBlue 0x1
#define cGreen 0x2
#define cGrey 0x8

#define clRed 0x4|0x8
#define clBlue 0x1|0x8
#define clGreen 0x2|0x8
#define clGrey 0x1|0x2|0x4

#define cYellow 0x2|0x4
#define cCyan 0x1|0x2
#define cMagenta 0x4|0x1

#define clYellow 0x2|0x4|0x8
#define clCyan 0x1|0x2|0x8
#define clMagenta 0x4|0x1|0x8

#define cWhite 0x1|0x2|0x4|0x8
#define cBlack 0

///////////////////////////////////////////////////////////////////////////////////////////////
/*
#define cRed {1,0,0,0}
#define cBlue {0,0,1,0}
#define cGreen {0,1,0,0}
#define cGrey {0,0,0,1}

#define clRed {1,0,0,1}
#define clBlue {0,0,1,1}
#define clGreen {0,1,0,1}
#define clGrey {1,1,1,0}

#define cYellow {1,1,0,0}
#define cCyan {0,1,1,0}
#define cMagenta {1,0,1,0}

#define clYellow {1,1,0,1}
#define clCyan {0,1,1,1}
#define clMagenta {1,0,1,1}

#define cWhite {1,1,1,1}
#define cBlack {0,0,0,0}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////


#define PAD_RIGHT 1
#define PAD_ZERO 2

#define PRINT_BUF_LEN 12

extern int cprint2(RGBI foreground, RGBI background, const char *format, ...);
extern int cprint(short, short, const char *format, ...);
extern void FillScreen(short primary, short secondary, int xmax, int ymax, char unit);
extern void PointCursor(int x, int y);
void print_char(char **str, int c);

WORD set_colour(RGBI foreground , RGBI  background);
WORD set_colour_bitwise(short foreground , short  background);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* End _HCOLOURS_H_ */


















