#define WINVER 0x0501
#include <windows.h>
#include <commctrl.h>

#define MAXNOFORCE 32

#include "ui.h"

void InitMenu(HMENU hMenu, HMENU hSubMenu, HWND hwnd)
{
            hMenu = CreateMenu();

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_NEW, "&New");
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_OPEN, "&Open");
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_SAVE, "&Save");
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_SAVEAS, "Save &As");
            AppendMenu(hSubMenu, MF_SEPARATOR, NULL,"");
            AppendMenu(hSubMenu, MF_STRING, ID_FILE_EXIT, "E&xit");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_EDIT_RESET, "&Reset");
            AppendMenu(hSubMenu, MF_SEPARATOR, ID_FILE_EXIT,"");
            AppendMenu(hSubMenu, MF_STRING, ID_EDIT_CUT, "Cut");
            AppendMenu(hSubMenu, MF_STRING, ID_EDIT_COPY, "Copy");
            AppendMenu(hSubMenu, MF_STRING, ID_EDIT_PASTE, "Paste");
            AppendMenu(hSubMenu, MF_STRING, ID_EDIT_DELETE, "Delete");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Edit");

            hSubMenu = CreatePopupMenu();
            AppendMenu(hSubMenu, MF_STRING, ID_HELP_ABOUT, "&About");
            AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&Help");

            SetMenu(hwnd, hMenu);
}

HWND InitStatus(HWND hwnd)
{
        HWND hStatus;
        hStatus = CreateStatusWindow(
                                        WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP,
                                        "hello",
                                        hwnd,
                                        NULL
                                    );
        return hStatus;
}

HWND InitConsole(HWND hwnd)
{
    HWND hEdit;
    hEdit = CreateWindowEx(
                                WS_EX_CLIENTEDGE,
                                "EDIT",
                                "Enter stuff here ",
                                WS_CHILD | WS_VISIBLE | WS_VSCROLL | /*WS_HSCROLL |*/ ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                                XRES-1250,
                                YRES-235,
                                1210,
                                150,
                                hwnd,
                                NULL,
                                GetModuleHandle(NULL),
                                NULL
                            );
    return hEdit;
}

HWND InitCreateForce(HWND hwnd, int xpos, int ypos)
{
    HWND hCreateForce;

    hCreateForce = CreateWindowEx(
                                    WS_EX_CLIENTEDGE,
                                    "BUTTON",
                                    "Create Force",
                                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    xpos,
                                    ypos,
                                    150,
                                    50,
                                    hwnd,
                                    (HMENU)ID_CREATEFORCE,
                                    GetModuleHandle(NULL),
                                    NULL
                                );

    return hCreateForce;
}

HWND InitToolbar(HWND hwnd)
{
    HWND hToolbar;

    TBBUTTON tbb[6];
    TBADDBITMAP tbab;

    hToolbar = CreateWindowEx(
                                0,
                                TOOLBARCLASSNAME,
                                NULL, WS_CHILD | WS_VISIBLE,
                                0,
                                0,
                                0,
                                0,
                                hwnd,
                                (HMENU)ID_TOOLBAR,
                                GetModuleHandle(NULL),
                                NULL
                            );

    SendMessage(hToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

    tbab.hInst = HINST_COMMCTRL;
    tbab.nID = IDB_STD_SMALL_COLOR;
    SendMessage(hToolbar, TB_ADDBITMAP, 0, (LPARAM)&tbab);

    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = STD_FILENEW;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_FILE_NEW;

    tbb[1].iBitmap = STD_FILEOPEN;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_FILE_OPEN;

    tbb[2].iBitmap = STD_FILESAVE;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_FILE_SAVEAS;

    tbb[3].iBitmap = STD_UNDO;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_FILE_SAVEAS;

    tbb[4].iBitmap = STD_REDOW;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_BUTTON;
    tbb[4].idCommand = ID_FILE_SAVEAS;

    tbb[5].iBitmap = STD_HELP;
    tbb[5].fsState = TBSTATE_ENABLED;
    tbb[5].fsStyle = TBSTYLE_BUTTON;
    tbb[5].idCommand = ID_FILE_SAVEAS;

    SendMessage(hToolbar, TB_ADDBUTTONS, 6 /*NO OF BUTTONS DONT FORGET ME*/ , (LPARAM)&tbb);
    return hToolbar;
}

HWND InitEntryField(HWND hwnd, HMENU id, int xpos, int ypos)
{
    HWND hEdit;
    hEdit = CreateWindowEx(
                                WS_EX_CLIENTEDGE,
                                "EDIT",
                                "0",
                                WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                                xpos,
                                ypos,
                                120,
                                25,
                                hwnd,
                                (HMENU)id,
                                GetModuleHandle(NULL),
                                NULL
                            );
    return hEdit;
}

HWND InitText(HWND hwnd, int xpos, int ypos, int length, const char* text)
{
    HWND hText;
    hText = CreateWindowEx(
                                0,
                                "STATIC",
                                text,
                                WS_CHILD | WS_VISIBLE | SS_RIGHT ,
                                xpos,
                                ypos,
                                length,
                                16,
                                hwnd,
                                NULL,
                                GetModuleHandle(NULL),
                                NULL
                            );
    return hText;
}


HWND InitLayer(HWND hwnd)
{
    HWND hLayer;

    hLayer = CreateWindowEx(
                                    WS_EX_CLIENTEDGE,
                                    "LISTBOX",
                                    "Layer",
                                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_DISABLENOSCROLL | LBS_NOSEL,
                                    1250,
                                    100,
                                    250,
                                    500,
                                    hwnd,
                                    (HMENU)ID_LAYER,
                                    GetModuleHandle(NULL),
                                    NULL
                                );

    return hLayer;
}

HWND InitDeleteForce(HWND hwnd, int xpos, int ypos)
{
    HWND hDeleteForce;

    hDeleteForce = CreateWindowEx(
                                    WS_EX_CLIENTEDGE,
                                    "BUTTON",
                                    "Delete Force",
                                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    xpos,
                                    ypos,
                                    150,
                                    50,
                                    hwnd,
                                    (HMENU)ID_DELETEFORCE,
                                    GetModuleHandle(NULL),
                                    NULL
                                );

    return hDeleteForce;
}

HWND InitEditForce(HWND hwnd, int xpos, int ypos)
{
    HWND hEditForce;

    hEditForce = CreateWindowEx(
                                    WS_EX_CLIENTEDGE,
                                    "BUTTON",
                                    "Edit Force",
                                    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                                    xpos,
                                    ypos,
                                    150,
                                    50,
                                    hwnd,
                                    (HMENU)ID_EDITFORCE,
                                    GetModuleHandle(NULL),
                                    NULL
                                );

    return hEditForce;
}

HWND InitOutput(HWND hwnd, int xpos, int ypos, const char* content)
{
    HWND hOutput;

    hOutput = CreateWindowEx(
                                    NULL,
                                    "STATIC",
                                    content,
                                    WS_VISIBLE | WS_CHILD ,
                                    xpos,
                                    ypos,
                                    140,
                                    15,
                                    hwnd,
                                    (HMENU)ID_EDITFORCE,
                                    GetModuleHandle(NULL),
                                    NULL
                                );

    return hOutput;
}

void InitUIGraphic(HDC hdc)
{
    HFONT hf_Title = CreateFont(26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Copperplate Gothic Bold");
    HFONT hf_Subscript = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "Consolas");

    TextOut (hdc,12,103,"Magnitude :",11);
    TextOut (hdc,43,138,"Angle :",7);
    TextOut (hdc,43,172,"X-Pos :",7);
    TextOut (hdc,43,207,"Y-Pos :",7);

    HFONT hfOld = SelectObject(hdc, hf_Title);
    TextOut (hdc,82,50,"Input",5);
    TextOut (hdc,1330,50,"Layer",5);
    SelectObject(hdc, hfOld);

    Rectangle(hdc,15, 400, 250, 730);
    Rectangle(hdc,18, 403, 247, 727);

    SelectObject(hdc, hf_Title);
    TextOut (hdc,82,420,"Output",6);

    SelectObject(hdc, hfOld);
    TextOut (hdc,48,470,"F        :",11);
    TextOut (hdc,48,495,"Angle :",7);
    TextOut (hdc,45,520,"X-Res :",7);
    TextOut (hdc,45,545,"Y-Res :",7);
    TextOut (hdc,32,570,"Moment :",8);

    SelectObject(hdc, hf_Subscript);
    TextOut (hdc,56,478,"net",3);

    SelectObject(hdc, hfOld);
}

void DrawGrid(HWND hwnd, HDC hdc)
{
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB(150,150,150));

    MoveToEx(hdc, 350, 400, NULL);
    LineTo(hdc, 1200, 400);

    MoveToEx(hdc, 750, 80, NULL);
    LineTo(hdc, 750, 720);
}
