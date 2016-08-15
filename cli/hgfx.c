#include <windows.h>
#include "hgfx.h"

extern int cprint(short foreground, short background, const char *format, ...)
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, set_colour_bitwise(foreground, background));

        va_list args;
        va_start( args, format );
        return print( 0, format, args );
}

extern int cprint2(RGBI foreground, RGBI background, const char *format, ...)
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, set_colour(foreground, background));

        va_list args;
        va_start( args, format );
        return print( 0, format, args );
}

extern void FillScreen(short primary, short secondary, int xmax, int ymax, char unit)
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, set_colour_bitwise(primary, secondary));
            int i, j;

            for (i=0; i<=xmax; i++)
            {
                    for (j=0; j<=ymax; j++)
                    {
                        printf("%c",unit);
                    }
            }

            for (i=0; i<=xmax+54; i++)
            {
                cprint(primary, secondary, "%c",unit);
            }

            PointCursor(0,0);


}

extern void Backdrop(short primary,int xmax, int ymax)
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, set_colour_bitwise(0, primary));
            int i, j;

            for (i=0; i<=xmax; i++)
            {
                    for (j=0; j<=ymax; j++)
                    {
                        printf(" ");
                    }
            }
            PointCursor(0,0);
}

extern void PointCursor(int x, int y)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursor_coords;
    cursor_coords.X = x;
    cursor_coords.Y = y;
    SetConsoleCursorPosition(hConsole,cursor_coords);
}

extern void HHideCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO console_cursor_info;
    console_cursor_info.dwSize = 1;
    console_cursor_info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &console_cursor_info);
}

extern void HShowCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO console_cursor_info;
    console_cursor_info.dwSize = 25;
    console_cursor_info.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &console_cursor_info);
}

extern void DrawBox(short primary, short secondary, int boxtype,int hollow, int xstart, int ystart ,int xend, int yend)
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, set_colour_bitwise(secondary, primary));
            int i, j, horizontal, vertical, corner_tl, corner_tr, corner_bl, corner_br;

            if (boxtype == 2)
            {
                horizontal = 186;
                vertical = 205;
                corner_tl = 201;
                corner_tr = 187;
                corner_bl = 200;
                corner_br = 188;
            }

            else if (boxtype == 1)
            {
                horizontal = 179;
                vertical = 196;
                corner_tl = 218;
                corner_tr = 191;
                corner_bl = 192;
                corner_br = 217;
            }

            else if (boxtype == 0)
            {
                horizontal = 219;
                vertical = 219;
                corner_tl = 219;
                corner_tr = 219;
                corner_bl = 219;
                corner_br = 219;
            }

            PointCursor(xstart,ystart);
            cprint(primary,secondary,"%c",corner_tl);

            PointCursor(xend,ystart);
            cprint(primary,secondary,"%c",corner_tr);

            PointCursor(xstart,yend);
            cprint(primary,secondary,"%c",corner_bl);

            PointCursor(xend,yend);
            cprint(primary,secondary,"%c",corner_br);

            for (i=ystart + 1; i<=yend - 1; i++)
            {

                PointCursor(xstart,i);
                cprint(primary,secondary,"%c",horizontal);

                for (j=xstart + 1; j<=xend - 1; j++)
                {
                    if (hollow == 0)
                    cprint(primary,secondary," ");
                }

                PointCursor(xend,i);
                cprint(primary,secondary,"%c",horizontal);
            }


            PointCursor(xstart+1,ystart);
            for (j=xstart + 1; j<=xend - 1; j++)
            {
                cprint(primary,secondary,"%c",vertical);
            }

            PointCursor(xstart+1,yend);
            for (j=xstart + 1; j<=xend - 1; j++)
            {
                cprint(primary,secondary,"%c",vertical);
            }

}

extern void DrawBoxTruncate(short primary, short secondary, int boxtype,int hollow, int xstart, int ystart ,int xend, int yend)
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, set_colour_bitwise(secondary, primary));
            int i, j, horizontal, vertical, corner_tl, corner_tr, corner_bl, corner_br;

            if (boxtype == 2)
            {
                vertical = 186;
                horizontal = 205;
                corner_tl = 201;
                corner_tr = 187;
                corner_bl = 200;
                corner_br = 188;
            }

            else if (boxtype == 1)
            {
                vertical = 179;
                horizontal = 196;
                corner_tl = 218;
                corner_tr = 191;
                corner_bl = 192;
                corner_br = 217;
            }

            else if (boxtype == 0)
            {
                vertical = 219;
                horizontal = 219;
                corner_tl = 219;
                corner_tr = 219;
                corner_bl = 219;
                corner_br = 219;
            }

            PointCursor(xstart,ystart);
            cprint(primary,secondary,"%c",corner_tl);

            PointCursor(xend,ystart);
            cprint(primary,secondary,"%c",corner_tr);

            for (i=ystart + 1; i<=yend - 1; i++)
            {

                PointCursor(xstart,i);
                cprint(primary,secondary,"%c",vertical);

                for (j=xstart + 1; j<=xend - 1; j++)
                {
                    if (hollow == 0)
                    cprint(primary,secondary," ");
                }

                PointCursor(xend,i);
                cprint(primary,secondary,"%c",vertical);
            }


            PointCursor(xstart+1,ystart);
            for (j=xstart + 1; j<=xend - 1; j++)
            {
                cprint(primary,secondary,"%c",horizontal);
            }
}

extern void HealBox(short foreground, short background, int medium, int xpos, int ypos)
{
    PointCursor(xpos,ypos);
    cprint( foreground , background, "%c", medium);
}

int print( char **out, const char *format, va_list args)
{
	register int width, pad;
	register int pc = 0;
	char scr[2];

	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = pad = 0;
			if (*format == '\0') break;
			if (*format == '%') goto out;
			if (*format == '-') {
				++format;
				pad = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				pad |= PAD_ZERO;
			}
			for ( ; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
			if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				pc += print_s (out, s?s:"(null)", width, pad);
				continue;
			}
			if( *format == 'd' ) {
				pc += print_i (out, va_arg( args, int ), 10, 1, width, pad, 'a');
				continue;
			}
			if( *format == 'x' ) {
				pc += print_i (out, va_arg( args, int ), 16, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'X' ) {
				pc += print_i (out, va_arg( args, int ), 16, 0, width, pad, 'A');
				continue;
			}
			if( *format == 'u' ) {
				pc += print_i (out, va_arg( args, int ), 10, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'c' ) {
				/* char are converted to int then pushed on the stack */
				scr[0] = (char)va_arg( args, int );
				scr[1] = '\0';
				pc += print_s (out, scr, width, pad);
				continue;
			}
		}
		else {
		out:
			print_char (out, *format);
			++pc;
		}
	}
	if (out) **out = '\0';
	va_end( args );

	return pc;
}

int print_i(char **out, int i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return print_s (out, print_buf, width, pad);
	}
	if (sg && b == 10 && i < 0) {
		neg = 1;
		u = -i;
	}
	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) {
		t = u % b;
		if( t >= 10 )
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}
	if (neg) {
		if( width && (pad & PAD_ZERO) ) {
			print_char (out, '-');
			++pc;
			--width;
		}
		else {
			*--s = '-';
		}
	}
	return pc + print_s (out, s, width, pad);
}

int print_s(char **out, const char *string, int width, int pad)
{
	register int pc = 0, padchar = ' ';
	if (width > 0) {
		register int len = 0;
		register const char *ptr;
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & PAD_ZERO) padchar = '0';
	}
	if (!(pad & PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			print_char (out, padchar);
			++pc;
		}
	}
	for ( ; *string ; ++string) {
		print_char (out, *string);
		++pc;
	}
	for ( ; width > 0; --width) {
		print_char (out, padchar);
		++pc;
	}
	return pc;
}

void print_char(char **str, int c)
{
	extern int putchar(int c);
	if (str) {
		**str = c;
		++(*str);
	}
	else (void)putchar(c);
}


WORD set_colour(RGBI foreground , RGBI  background)
{
    WORD buffer = 0;
    if (!foreground.R == 0)
    buffer = buffer | FOREGROUND_RED;

    if (!foreground.G == 0)
    buffer = buffer | FOREGROUND_GREEN;

    if (!foreground.B == 0)
    buffer = buffer | FOREGROUND_BLUE;

    if (!foreground.I == 0)
    buffer = buffer | FOREGROUND_INTENSITY;

    if (!background.R == 0)
    buffer = buffer | BACKGROUND_RED;

    if (!background.G == 0)
    buffer = buffer | BACKGROUND_GREEN;

    if (!background.B == 0)
    buffer = buffer | BACKGROUND_BLUE;

    if (!background.I == 0)
    buffer = buffer | BACKGROUND_INTENSITY;

    return buffer;
}

WORD set_colour_bitwise(short foreground , short  background)
{
    WORD buffer = foreground;

    switch (background)
    {
        case cRed :     buffer =     buffer | 0x40; break;
        case cBlue :    buffer =     buffer | 0x10; break;
        case cGreen :   buffer =     buffer | 0x20; break;
        case cGrey :    buffer =     buffer | 0x80; break;

        case clRed  :   buffer =     buffer | 0x40|0x80; break;
        case clBlue :   buffer =     buffer | 0x10|0x80; break;
        case clGreen :  buffer =     buffer | 0x20|0x80; break;
        case clGrey :   buffer =     buffer | 0x10|0x20|0x40; break;

        case cYellow :  buffer =     buffer | 0x20|0x40; break;
        case cCyan :    buffer =     buffer | 0x10|0x20; break;
        case cMagenta : buffer =     buffer | 0x40|0x10; break;

        case clYellow :  buffer =    buffer | 0x20|0x40|0x80; break;
        case clCyan :    buffer =    buffer | 0x10|0x20|0x80; break;
        case clMagenta : buffer =    buffer | 0x40|0x10|0x80; break;

        case cWhite :    buffer =    buffer |0x10|0x20|0x40|0x80; break;
        case cBlack :    buffer =    buffer |0; break;
    }


    return buffer;
}
