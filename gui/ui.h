#ifndef _ui_h_
#define _ui_h_

#define XRES 1570
#define YRES 835

#define ID_FILE_NEW 1001
#define ID_FILE_OPEN 1002
#define ID_FILE_SAVE 1003
#define ID_FILE_SAVEAS 1004
#define ID_FILE_EXIT 1005

#define ID_EDIT_RESET 2001
#define ID_EDIT_CUT 2002
#define ID_EDIT_COPY 2003
#define ID_EDIT_PASTE 2004
#define ID_EDIT_DELETE 2005

#define ID_HELP_ABOUT 3001

#define ID_MAGNITUDE 0101
#define ID_ANGLE 0102
#define ID_XPOS 0103
#define ID_YPOS 0104

#define ID_TOOLBAR 0001
#define ID_CREATEFORCE 0002
#define ID_LAYER 0003
#define ID_DELETEFORCE 0004
#define ID_EDITFORCE 0005

void InitMenu(HMENU hMenu, HMENU hSubMenu, HWND hwnd);
HWND InitStatus(HWND hwnd);
HWND InitCreateForce(HWND hwnd, int xpos, int ypos);
HWND InitToolbar(HWND hwnd);
HWND InitEntryField(HWND hwnd, HMENU id, int xpos, int ypos);
HWND InitText(HWND hwnd, int xpos, int ypos, int length, const char* text);
HWND InitLayer(HWND hwnd);
HWND InitDeleteForce(HWND hwnd, int xpos, int ypos);
HWND InitEditForce(HWND hwnd, int xpos, int ypos);
HWND InitOutput(HWND hwnd, int xpos, int ypos, const char* content);
void InitUIGraphic(HDC hdc);
void DrawGrid(HWND hwnd, HDC hdc);

typedef struct
{
    double magnitude;
    float angle;
    float xpos;
    float ypos;
    double xres;
    double yres;
    double moment;
    COLORREF colour;
    int freeflag;
} force;

#endif // _ui_h_
