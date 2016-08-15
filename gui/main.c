#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <assert.h>

#define WINVER 0x0501
#include <windows.h>
#include <commctrl.h>

#include "ui.h"

#define XRES 1560
#define YRES 842
#define MAXNOFORCE 32

void UpdateOutput(HWND hwnd);
BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam); //not implemented now, used for edit force

const char g_ClassName[] = "staticscalcClass";

force layer[MAXNOFORCE];
HWND hEdit, hStatus, hCreateForce, hToolbar, hMagnitudeInput, hAngleInput, hXInput, hYInput, hLayer, hDeleteForce, hEditForce;
HWND hResultantForce, hResultantAngle, hResultantX, hResultantY, hResultantMoment;
HWND hBuffer, hErrorMsg;
time_t rawtime;
struct tm * timeinfo;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    int i=0;
    char buffer[32], buffer2[32], buffer3[48], buffer4[32], buffer5[32];

    switch(msg)
    {
        case WM_CREATE:
        {
            HMENU hMenu, hSubMenu;
            HFONT hfCurrent;
            HDC hwnd_dc = GetDC(hwnd);

            debugmsg("GOOD","WM_CREATE received");

            InitCommonControls();

            InitMenu(hMenu, hSubMenu, hwnd);

            hToolbar = InitToolbar(hwnd);
            hStatus = InitStatus(hwnd);

            hMagnitudeInput = InitEntryField(hwnd, ID_MAGNITUDE, 100, 100);
            SendMessage(hMagnitudeInput, EM_SETLIMITTEXT , 16, 0);
            hAngleInput = InitEntryField(hwnd, ID_ANGLE,100, 135);
            SendMessage(hAngleInput, EM_SETLIMITTEXT , 8, 0);
            hXInput = InitEntryField(hwnd, ID_XPOS,100, 170);
            SendMessage(hXInput, EM_SETLIMITTEXT , 8, 0);
            hYInput = InitEntryField(hwnd, ID_YPOS,100, 205);
            SendMessage(hYInput, EM_SETLIMITTEXT , 8, 0);

            hResultantForce = InitOutput(hwnd, 100, 470, "0 N");
            hResultantAngle = InitOutput(hwnd, 100, 495, "0 °");
            hResultantX = InitOutput(hwnd, 100, 520, "0 N");
            hResultantY = InitOutput(hwnd, 100, 545, "0 N");
            hResultantMoment = InitOutput(hwnd, 100, 570, "0 Nm");

            hErrorMsg = CreateWindowEx(
                                    NULL,
                                    "STATIC",
                                    "*Values after invalid character will be omitted.",
                                    WS_VISIBLE | WS_CHILD ,
                                    10,
                                    330,
                                    300,
                                    15,
                                    hwnd,
                                    (HMENU)ID_EDITFORCE,
                                    GetModuleHandle(NULL),
                                    NULL
                                );

            UpdateOutput(hwnd);

            hCreateForce = InitCreateForce(hwnd, 40, 265);
            hDeleteForce = InitDeleteForce(hwnd,1300,680);
            hEditForce = InitEditForce(hwnd,1300,610);

            hLayer = InitLayer(hwnd);

            break;
        }

        case WM_CTLCOLORSTATIC:
        {
            HDC hdcStatic = (HDC) wParam;
            SetTextColor(hdcStatic, RGB(0,0,0));
            SetBkColor(hdcStatic, RGB(255,255,255));
            return (INT_PTR)CreateSolidBrush(RGB(255,255,255));
        }

        case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case ID_FILE_EXIT:
					PostMessage(hwnd, WM_CLOSE, 0, 0);
                    debugmsg("GOOD","Program aborted");
                    break;

                case ID_CREATEFORCE:
                    {
                        debugmsg("GOOD","Creating force");
                        if(SendDlgItemMessage(hwnd, ID_LAYER, LB_GETCOUNT, 0, 0) < MAXNOFORCE - 1 )
                        {
                            SendDlgItemMessage(hwnd, ID_MAGNITUDE, WM_GETTEXT, 16, buffer );
                            SendDlgItemMessage(hwnd, ID_ANGLE, WM_GETTEXT, 15, buffer2 );
                            SendDlgItemMessage(hwnd, ID_XPOS, WM_GETTEXT, 15, buffer4 );
                            SendDlgItemMessage(hwnd, ID_YPOS, WM_GETTEXT, 15, buffer5 );
                            strcpy(buffer3,buffer);
                            strcat (buffer3," N, ");
                            strcat (buffer3,buffer2);
                            strcat (buffer3,"° at ( ");
                            strcat (buffer3,buffer4);
                            strcat (buffer3," , ");
                            strcat (buffer3,buffer5);
                            strcat (buffer3," )");

                            SendDlgItemMessage(hwnd, ID_LAYER, LB_ADDSTRING, 0, buffer3 );

                            for(i=0;i<MAXNOFORCE;i++)
                            {
                                if(layer[i].freeflag == 0)
                                {
                                    layer[i].magnitude = strtod(buffer, NULL);
                                    layer[i].angle = strtof(buffer2,NULL);
                                    layer[i].xpos = strtof(buffer4,NULL);
                                    layer[i].ypos = strtof(buffer5,NULL);

                                    layer[i].xres = layer[i].magnitude * cos(layer[i].angle * 3.1415926535 /180);
                                    layer[i].yres = layer[i].magnitude * sin(layer[i].angle * 3.1415926535 /180);

                                    layer[i].freeflag = 1;
                                    UpdateOutput(hwnd);
                                    break;
                                }
                            }

                        }
                        break;
                    }


                case ID_DELETEFORCE:
                    {
                        debugmsg("GOOD","Deleting force");
                        int DelIndex = SendDlgItemMessage(hwnd, ID_LAYER, LB_GETCURSEL, 0 , 0);
                        int index = SendDlgItemMessage(hwnd, ID_LAYER, LB_DELETESTRING,
                                                       DelIndex,
                                                       0);
                        layer[DelIndex].magnitude = 0;
                        layer[DelIndex].angle = 0;
                        layer[DelIndex].xpos = 0;
                        layer[DelIndex].ypos = 0;
                        layer[DelIndex].xres = 0;
                        layer[DelIndex].yres = 0;
                        layer[DelIndex].moment = 0;
                        layer[DelIndex].freeflag = 0;
                        UpdateOutput(hwnd);

                        free(&DelIndex);
                        free(&index);

                        break;
                    }

                case ID_EDITFORCE:
                {
                    MessageBox(hwnd,"Work In Progress","Oops",MB_OK);
                    debugmsg("ERROR","WIP : Edit Force");
                    break;
                }

                case ID_FILE_NEW:
                {
                    MessageBox(hwnd,"Work In Progress","Oops",MB_OK);
                    debugmsg("ERROR","WIP : File New");
                    break;
                }

                case ID_FILE_OPEN:
                {
                    MessageBox(hwnd,"Work In Progress","Oops",MB_OK);
                    debugmsg("ERROR","WIP : File Open");
                    break;
                }

                case ID_LAYER:
                    switch(HIWORD(wParam))
                    {
                        case LBN_SELCHANGE:
                        break;
                    }
                    break;
        }

        break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint (hwnd, &ps);
            InitUIGraphic(hdc);
            DrawGrid(hwnd, hdc);

            EndPaint (hwnd, &ps);
            break;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX stcalc;
    HWND hwnd;
    MSG Msg;
    HANDLE Icon32;

    stcalc.cbSize        = sizeof(WNDCLASSEX);
    stcalc.style         = 0;
    stcalc.lpfnWndProc   = WndProc;
    stcalc.cbClsExtra    = 0;
    stcalc.cbWndExtra    = 0;
    stcalc.hInstance     = hInstance;
    stcalc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    stcalc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    stcalc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    stcalc.lpszMenuName  = NULL;
    stcalc.lpszClassName = g_ClassName;
    stcalc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClassEx(&stcalc);

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_ClassName,
        "Statics Calc",
        WS_OVERLAPPEDWINDOW,
        0, 0, XRES, YRES,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    SendMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
    UpdateWindow(hwnd);

    HANDLE hIcon = LoadImage(0, ("icon.ico"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    if (hIcon)
    {
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, hIcon);

        SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_SMALL, hIcon);
        SendMessage(GetWindow(hwnd, GW_OWNER), WM_SETICON, ICON_BIG, hIcon);
    }

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


void UpdateOutput(HWND hwnd)
{
    double xbuf = 0, ybuf = 0, mbuf = 0;
    char buf[32];
    int i;
    for(i=0;i<MAXNOFORCE;i++)
    {
        xbuf = xbuf + layer[i].xres;
        ybuf = ybuf + layer[i].yres;
        mbuf = mbuf - layer[i].xres * layer[i].ypos + layer[i].yres * layer[i].xpos;
    }

    snprintf(buf,32,"%f N",sqrt(xbuf*xbuf + ybuf*ybuf));
    SendMessage(hResultantForce, WM_SETTEXT , 0, buf);

    snprintf(buf,32,"%f °",atan(ybuf/xbuf)*180/3.1415926535);
    SendMessage(hResultantAngle, WM_SETTEXT , 0, buf);

    snprintf(buf,32,"%f N",xbuf);
    SendMessage(hResultantX, WM_SETTEXT , 0, buf);

    snprintf(buf,32,"%f N",ybuf);
    SendMessage(hResultantY, WM_SETTEXT , 0, buf);

    snprintf(buf,32,"%f Nm",mbuf);
    SendMessage(hResultantMoment, WM_SETTEXT , 0, buf);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
        case WM_INITDIALOG:
        return TRUE;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
        break;

        default:
            return FALSE;
    }
    return TRUE;
}

void debugmsg(const char* flag, const char* msg)
{
    time(&rawtime);
    timeinfo = localtime ( &rawtime );
    printf("[%d:%d:%d] (%s) %s\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,flag,msg);
}






