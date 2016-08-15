#include <stdio.h>
#include <math.h>
#include "hgfx.h"

void forcesintro();
void RenderScreen();
void InitialiseScreenBuffer();
void DrawTextForces(short);
void DrawCrayBear(short);

char g_IntroAnimation_OutputBuffer[27][81];

extern void forcesintro()
{
    FillScreen(clGrey,cBlack,0,0,' ');
    InitialiseScreenBuffer();
    RenderScreen();

    int i = 0,j;
    short forecolour = clGrey;

    for(j=0;j<=70;j++)//two lines horizontal
    {
         PointCursor(j  ,3);
         g_IntroAnimation_OutputBuffer[4][j] = 205;
         printf("%c",g_IntroAnimation_OutputBuffer[4][j]);


         PointCursor(79-j,22);
         g_IntroAnimation_OutputBuffer[20][79-j] = 205;
         printf("%c",g_IntroAnimation_OutputBuffer[20][79-j]);

         if (j>60)
         {
                PointCursor(i  ,3);
                g_IntroAnimation_OutputBuffer[4][i] = ' ';
                printf("%c",g_IntroAnimation_OutputBuffer[4][i]);

                PointCursor(79-i,22);
                g_IntroAnimation_OutputBuffer[20][79-i] = ' ';
                printf("%c",g_IntroAnimation_OutputBuffer[20][79-i]);

                i = i + 1;
         }

        if(kbhit())
        {
            break;
        }

         Sleep(10);
    }

    PointCursor(79-j,22);
    g_IntroAnimation_OutputBuffer[4][j] = 200;
    printf("%c",g_IntroAnimation_OutputBuffer[4][j]);

    PointCursor(j  ,3);
    g_IntroAnimation_OutputBuffer[20][79-j] = 187;
    printf("%c",g_IntroAnimation_OutputBuffer[20][79-j]);

    for(j=1;j<=18;j++) //two lines vertical
    {
         PointCursor(71,j+3);
         g_IntroAnimation_OutputBuffer[j+6][60] = 186;
         printf("%c",g_IntroAnimation_OutputBuffer[j+6][60]);

         PointCursor(8,22-j);
         g_IntroAnimation_OutputBuffer[19-j][19] = 186;
         printf("%c",g_IntroAnimation_OutputBuffer[19-j][19]);

        if(kbhit())
        {
            break;
        }

         Sleep(20);
    }
        j = 0;
        forecolour  = cGrey;
        while(j<3)
        {
            DrawTextForces(forecolour);

            switch (j%2){
            case 0: forecolour  = clGrey;break;
            case 1: forecolour  = cWhite;break;
            }
            j = j+1;

            if(kbhit())
            {
                break;
            }

            Sleep(300);
        }

        PointCursor(45,23);
        printf("Press any key to continue");

    j = 0;
    forecolour  = clYellow;

    while(1==1)
    {
        DrawCrayBear(forecolour);

        switch (j%4){
        case 0: forecolour  = clRed;break;
        case 1: forecolour  = clBlue;break;
        case 2: forecolour  = clGreen;break;
        case 3: forecolour  = clYellow;break;
        }
        j = j+1;

        if(kbhit())
        {
            break;
        }

        Sleep(300);
    }
    FillScreen(fdefault,bdefault,0,0,' ');
}

void RenderScreen()
{
    int i,j;
    for(i=0;i<=24;i++){
        for(j=0;j<=79;j++){
             printf("%c",g_IntroAnimation_OutputBuffer[i][j]);
        }
    }
}

void InitialiseScreenBuffer()
{
    int i,j;
    for(i=0;i<=24;i++){
        for(j=0;j<=79;j++){
             g_IntroAnimation_OutputBuffer[i][j]=' ';
        }
    }
}

void DrawTextForces(short forecolour)
{
        int j;

        j = 5;
        PointCursor(31,j);
        cprint(forecolour,cBlack," _______");
        PointCursor(31,j+1);
        cprint(forecolour,cBlack,"(_______)");
        PointCursor(31,j+2);
        cprint(forecolour,cBlack, "_____ ___   ____ ____ ____  ___ ");
        PointCursor(31,j+3);
        cprint(forecolour,cBlack, "|  ___) _ \\ / ___) ___) _  )/___) ");
        PointCursor(31,j+4);
        cprint(forecolour,cBlack, "| |  | |_| | |  ( (__( (/ /|___ |  ");
        PointCursor(31,j+5);
        cprint(forecolour,cBlack, "|_|   \\___/|_|   \\____)____|___/  ");

        j = 14;
        PointCursor(26,j);
        cprint(forecolour,cBlack," __  __                            _       ");
        PointCursor(26,j+1);
        cprint(forecolour,cBlack,"|  \\/  |                          | |      ");
        PointCursor(26,j+2);
        cprint(forecolour,cBlack,"| \\  / | ___  _ __ ___   ___ _ __ | |_ ___ ");
        PointCursor(26,j+3);
        cprint(forecolour,cBlack,"| |\\/| |/ _ \\| '_ ` _ \\ / _ \\ '_ \\| __/ __|");
        PointCursor(26,j+4);
        cprint(forecolour,cBlack,"| |  | | (_) | | | | | |  __/ | | | |_\\__ \\");
        PointCursor(26,j+5);
        cprint(forecolour,cBlack,"|_|  |_|\\___/|_| |_| |_|\\___|_| |_|\\__|___/");

        j = 11;
        PointCursor(41,j);
        cprint(forecolour,cBlack,"   ___   ");
        PointCursor(41,j+1);
        cprint(forecolour,cBlack,"  ( _ )  ");
        PointCursor(41,j+2);
        cprint(forecolour,cBlack,"  / _ \\/\\");
        PointCursor(41,j+3);
        cprint(forecolour,cBlack," | (_>  <");
        PointCursor(41,j+4);
        cprint(forecolour,cBlack,"  \\___/\\/");
}

void DrawCrayBear(short forecolour)
{
        PointCursor(13,4);
        cprint(forecolour,cBlack,"   _     _   ");
        PointCursor(13,5);
        cprint(forecolour,cBlack,"  (c).-.(c)  ");
        PointCursor(13,6);
        cprint(forecolour,cBlack,"   / ._. \\   ");
        PointCursor(13,7);
        cprint(forecolour,cBlack," __\\( Y )/__ ");
        PointCursor(13,8);
        cprint(forecolour,cBlack,"(_.-/'-'\\-._)");
        PointCursor(13,9);
        cprint(forecolour,cBlack,"   ||   ||   ");
        PointCursor(13,10);
        cprint(forecolour,cBlack," _.' `-' '._ ");
        PointCursor(13,11);
        cprint(forecolour,cBlack,"(.-./`-'\\.-.)");
        PointCursor(13,12);
        cprint(forecolour,cBlack," `-'     `-'");
}
