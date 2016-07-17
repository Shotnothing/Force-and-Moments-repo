/*
********************************************************************************************
______                                        _  ___  ___                           _
|  ___|                                      | | |  \/  |                          | |
| |_ ___  _ __ ___ ___  ___    __ _ _ __   __| | | .  . | ___  _ __ ___   ___ _ __ | |_ ___
|  _/ _ \| '__/ __/ _ \/ __|  / _` | '_ \ / _` | | |\/| |/ _ \| '_ ` _ \ / _ \ '_ \| __/ __|
| || (_) | | | (_|  __/\__ \ | (_| | | | | (_| | | |  | | (_) | | | | | |  __/ | | | |_\__ \
\_| \___/|_|  \___\___||___/  \__,_|_| |_|\__,_| \_|  |_/\___/|_| |_| |_|\___|_| |_|\__|___/

                                                                                Version 0.8
********************************************************************************************
Author : JW s10172747k
            - UI, graphics, framework and resultant force calculation
	     NN s10173318e
            - Moments calculation and official write-up

Input parameters:  None


Returns:        0 : Success
                1 : Magnitude is negative (In function input_magnitude at line 87)  //To-do : Recursive function
                2 : Magnitude too big     (In function input_magnitude at line 87)  //To-do : Recursive function
                3 : Event handler breaks
*/

/// <Description>
/// This is part of a mini-project for 6compro
/// Name : s10172747k & s10173318e
/// Class: P1_D3
/// Title: Forces and Moments
///
///
/// <For my reference>
/// To-Do :  <Version 0.8>
///         - Cool Intro         [Done]
///         - Save/Load          [Done]
///         - Port to TCC        [Done]
///

//Initialisation [Directives]
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>

#include "forcesintro.c"

//Initialisation [Constants]
#define PI 3.14159265
#define false 0
#define true 1
#define VER_NO 0.8

//Initialisation [Prototypes]
void event_handler();
void draw_line(int length,int type);
void draw_splash();
void draw_menu(float ,float ,float ,float,float,int, int, int, int, int, int, int );
int digit_count(float);
float input_magnitude();
float input_angle();
float resolve_angle(int, float );
float input_x_pos();
float input_y_pos();
void console_plot(float, float, int, int);
void console_plot_moment(float, float);
void console_plot_force(float, float);
void toolbar(int);
void menu_options(float,float);
void colours_menu();
void text_colours_menu();
void background_colours_menu();
void help_menu();
void help_menu_ginfo();
void help_menu_ui();
void help_menu_calc();
void change_page(int);
int message_chain();
int precision_menu();
char* saveload_menu();
void save_for();
char* load_for();
char* receiveInput( char *s);
void confirm_exit();

//Initialisation [Global]
const char *p_SaveBuffer;

/*Function[force_main]
**************************
Description      : To be called by main function
Input Parameters : None
Output Returns   : 0 - Success
                   3 - Error (Reach end of main)
*/
int main()
{
    draw_splash();
    event_handler();

    return 3; //Error
}

/*Function[event_handler]
**************************
Description      : Spine of the program
Input Parameters : None
Output Returns   : None (Void)
*/
void event_handler()
{
    float magnitude, angle, x_resultant = 0 , y_resultant = 0 , magnitude_resultant=0, angle_resultant=0, moment_resultant=0, x_pos = 0, y_pos = 0;
    float buffer_x_resultant , buffer_y_resultant , buffer_magnitude_resultant, buffer_angle_resultant;
    int message, degree_bool=1, message_stream, magnitude_precision = 6, angle_precision = 6, x_resultant_precision = 6, y_resultant_precision = 6,index_precision, moment_flag = 0, moment_precision = 6;
    char save_string_buffer[512], out_string[512], buffer[512];
    char *pch, *pchend, *temp;
    int loop_count = 0;


    do
    {
        system("CLS");


        draw_menu(
                      magnitude_resultant,
                      angle_resultant,
                      x_resultant,
                      y_resultant,
                      moment_resultant,

                      magnitude_precision,
                      angle_precision,
                      x_resultant_precision,
                      y_resultant_precision,
                      moment_precision,

                      degree_bool,
                      moment_flag
                 );

        sprintf(save_string_buffer, "#%d#%f#%f#%f#%f#%f#%d#%d#%d#%d#%d#",

                      degree_bool,

                      magnitude_resultant,
                      angle_resultant,
                      x_resultant,
                      y_resultant,
                      moment_resultant,

                      magnitude_precision,
                      angle_precision,
                      x_resultant_precision,
                      y_resultant_precision,
                      moment_precision
                 );


        p_SaveBuffer = save_string_buffer;

        message = tolower(  message_chain()  );

        switch (message)
        {

            case 27 :      //esc
            {
                 confirm_exit();
                 break;
            }
            case 97:        //a
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //Get handle to console output
                CONSOLE_SCREEN_BUFFER_INFO consoleInfo;             //Declare console info
                GetConsoleScreenBufferInfo(hConsole, &consoleInfo); //Retrieve console info
                WORD menu_saved_attributes;                         //Declare WORD
                menu_saved_attributes = consoleInfo.wAttributes;    //Save wAttributes of console

                printf("\n\n[");

                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                printf("CLEAR");
                SetConsoleTextAttribute(hConsole, menu_saved_attributes);

                printf("] Sure? [y/n]");
                sure_label://Apologies for goto
                switch ( tolower( getch() ) )
                {
                    case 'y': x_resultant = 0 , y_resultant = 0 , magnitude_resultant=0, angle_resultant=0; break;
                    case 'n': break;
                    default: goto sure_label;
                }
                break;
            }

            case 115 :      //s
            {
                 settings_label://Apologies for goto
                 system("CLS");
                 printf("=======    Settings    =======\n\n");
                 printf("[1]  Colours\n");
                 printf("[2]  Help\n");
                 printf("[3]  Precision\n");
                 printf("[4]  Save/Load\n");
                 printf("\n[Esc]  Exit\n\n\n");
                 message_stream=getch();

                 switch(message_stream)
                 {
                    case 27 :               //esc
                    {
                        break;
                    }
                    case 49 :               //1
                    {
                        colours_menu();
                        break;
                    }
                    case 50:                //2
                    {
                        help_menu();
                        break;
                    }
                    case 51:                //3
                    {
                        index_precision = precision_menu(
                                                                 magnitude_precision,
                                                                 angle_precision,
                                                                 x_resultant_precision,
                                                                 y_resultant_precision
                                                        );
                        switch(index_precision%5)
                        {
                            case 1: magnitude_precision   = index_precision/10; break;

                            case 2: angle_precision       = index_precision/10; break;

                            case 3: x_resultant_precision = index_precision/10; break;

                            case 4: y_resultant_precision = index_precision/10; break;

                            case 0:
                            {
                            magnitude_precision   = index_precision/10;
                            angle_precision       = magnitude_precision;
                            x_resultant_precision = angle_precision;
                            y_resultant_precision = x_resultant_precision;
                            moment_precision      = y_resultant_precision;
                            break;
                            }

                            default : printf("ERROR: Line 185");getch();break;
                        }
                        break;
                    }
                    case 52:
                    {
                          temp = saveload_menu();

                          if(temp!=0)
                          {
                              strcpy( buffer, temp );
                              pchend = buffer;

                              cprint(cGreen,bdefault,"[Good]");
                              cprint(fdefault,bdefault,"  ");
                              printf("Parsing file\n");

                              pchend = strchr(buffer,'#');
                              pch = strchr(buffer,'#');
                              loop_count = 0;
                              while (pch!=NULL && loop_count<=10)
                              {
                                memset(out_string, 0, 512);
                                pch=strchr(pch+1,'#');
                                //printf("%d\n",pch-buffer);
                                strncpy ( out_string, buffer + (int)(pchend-buffer+1), (int)(pch-pchend-1));

                                cprint(cGreen,bdefault,"[Good]");
                                cprint(fdefault,bdefault,"  ");
                                printf("Recieved %s to %d\n",out_string,loop_count);

                                pchend=pch;

                                switch(loop_count)
                                {
                                    case 0: degree_bool = atoi(out_string);                   break;


                                    case 1 : magnitude_resultant = (float)strtod(out_string,NULL);    break;
                                    case 2 : angle_resultant = (float)strtod(out_string,NULL);        break;
                                    case 3 : x_resultant = (float)strtod(out_string,NULL);            break;
                                    case 4 : y_resultant = (float)strtod(out_string,NULL);            break;
                                    case 5 : moment_resultant = (float)strtod(out_string,NULL);       break;

                                    case 6: magnitude_precision = atoi(out_string);            break;
                                    case 7: angle_precision = atoi(out_string);                break;
                                    case 8: x_resultant_precision = atoi(out_string);          break;
                                    case 9: y_resultant_precision = atoi(out_string);          break;
                                    case 10: moment_precision = atoi(out_string);              break;
                                }
                                loop_count = loop_count + 1;

                              }

                              cprint(cGreen,bdefault,"[Good]");
                              cprint(fdefault,bdefault,"  Load complete\n");
                              cprint(fdefault,bdefault,"  \nPress any key to continue");
                              getch();
                          }
                    }
                    default:
                    {
                         goto  settings_label;
                    }
                    break;
                 }
                break;
            }

            case 100 :      //d
            {
                if (degree_bool==0)
                {
                    degree_bool = 1;
                }
                 else
                {
                    degree_bool = 0;
                }
                break;
            }

            case '\r':      //Enter
            {
                    printf("[Enter] Enter Force\n");
                    draw_line(79,205);
                    magnitude = input_magnitude();
                    if (magnitude!=0)
                    {
                        printf("\n");

                        angle = input_angle(degree_bool);

                        //Temporary buffer of data for possible undo
                        buffer_x_resultant = x_resultant;
                        buffer_y_resultant = y_resultant;
                        buffer_magnitude_resultant =magnitude_resultant;
                        buffer_angle_resultant = angle_resultant;

                        if (degree_bool == 0)
                        {
                                x_resultant = x_resultant + magnitude * cos(angle);
                                y_resultant = y_resultant + magnitude * sin(angle);
                                angle_resultant = atan(y_resultant/x_resultant);
                        }
                        else if (degree_bool == 1)
                        {
                                x_resultant = x_resultant + magnitude * cos(angle*PI/180);    //*10000 for high accuracy

                                y_resultant = y_resultant + magnitude * sin(angle*PI/180);

                                angle_resultant = atan(y_resultant/x_resultant);

                                if (y_resultant < pow(0.1,digit_count(magnitude))&& y_resultant > -pow(0.1,digit_count(magnitude)))              //Rounding off float y_resultant
                                    y_resultant = 0;
                                if (x_resultant < pow(0.1,digit_count(magnitude))&& x_resultant > -pow(0.1,digit_count(magnitude)))              //Rounding off float s_resultant
                                    x_resultant = 0;
                                //if (angle_resultant < pow(0.1,digit_count(magnitude))&& angle_resultant > -pow(0.1,digit_count(magnitude)))      //Rounding off float angle_resultant
                                //    angle_resultant = 0;
                        }
                        magnitude_resultant = sqrt(pow(x_resultant,2)+pow(y_resultant,2));

                        printf("\n\n\nPress any key to continue, or [z] to undo\n") ;
                        if(getch()==122)
                        {
                            x_resultant = buffer_x_resultant;
                            y_resultant = buffer_y_resultant;
                            magnitude_resultant = buffer_magnitude_resultant;
                            angle_resultant = buffer_angle_resultant;
                        }
                        break;

                 }
                 break;
            }
            case 10:  //ctrl enter
            {
                    float x_pos = 3,  y__pos = 3;

                    printf("[Enter] Enter Moment\n");
                    draw_line(79,205);

                    moment_flag = 1;
                    x_pos=input_x_pos();
                    y_pos=input_y_pos();
                    magnitude = input_magnitude();
                    if (magnitude==0)  break;

                    angle = input_angle();

                    if (degree_bool == 0)
                    {
                            x_resultant = x_resultant + magnitude * cos(angle);
                            y_resultant = y_resultant + magnitude * sin(angle);
                            angle_resultant = atan(y_resultant/x_resultant);
                    }
                    else if (degree_bool == 1)
                    {
                            x_resultant = x_resultant + magnitude * cos(angle*PI/180)*10000;    //*10000 for high accuracy

                            y_resultant = y_resultant + magnitude * sin(angle*PI/180)*10000;

                            angle_resultant = atan(y_resultant/x_resultant);

                            x_resultant = x_resultant / 10000;
                            y_resultant = y_resultant / 10000;

                            if (y_resultant < pow(0.1,digit_count(magnitude))&& y_resultant > -pow(0.1,digit_count(magnitude)))              //Rounding off float y_resultant
                                y_resultant = 0;
                            if (x_resultant < pow(0.1,digit_count(magnitude))&& x_resultant > -pow(0.1,digit_count(magnitude)))              //Rounding off float s_resultant
                                x_resultant = 0;
                    }
                    magnitude_resultant = sqrt(pow(x_resultant,2)+pow(y_resultant,2));
                    moment_resultant = -1*(x_pos * x_resultant + y_pos * y_resultant);

                    printf("\n\nPress any key to continue, or [z] to undo\n") ;
                    if(getch()==122)
                    {
                        x_resultant = buffer_x_resultant;
                        y_resultant = buffer_y_resultant;
                        magnitude_resultant = buffer_magnitude_resultant;
                        angle_resultant = buffer_angle_resultant;
                    }
                    break;
            }
            default: break;
        }
    }
    while (true);

}

/*Function[draw_line]
**************************
Description      : Draws a line
Input Parameters : length (Int)
                   type   (Int)
Output Returns   : None
*/
void draw_line(int length,int type)
{
    int i;
    for (i=0;i<=length;i++)
        printf("%c",type);
}

/*Function[draw_splash]
**************************
Description      : Initializes console, then prints splash screen at program launch
Input Parameters : None
Output Returns   : None (Void)
*/
void draw_splash()
{

    SetConsoleTitle("Forces and Moments");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//  < Reduce Buffer Size >
    COORD NewScreenBufferSize;
    NewScreenBufferSize.X = 80;
    NewScreenBufferSize.Y = 26;
    if(!SetConsoleScreenBufferSize(hConsole, NewScreenBufferSize))
    printf("RUNTIME ERROR: SetConsoleScreenBufferSize RETURNS %d\n",GetLastError());

    SMALL_RECT DisplayArea = {0, 0, NewScreenBufferSize.X, NewScreenBufferSize.Y};
    SetConsoleWindowInfo(hConsole, TRUE, &DisplayArea);
//

    forcesintro();
    system("cls");
    getch();

    printf(" _______                            \n\
(_______)                           \n\
 _____ ___   ____ ____ ____  ___    \n\
|  ___) _ \\ / ___) ___) _  )/___)   \n\
| |  | |_| | |  ( (__( (/ /|___ |   \n\
|_|   \\___/|_|   \\____)____|___/    \n\n\
");
    printf("==================================\n") ;
    printf("Name:           Forces and Moments\n") ;
    printf("Version:        %.1f\n",VER_NO) ;
    printf("Description:    This is a program that calculates a resultant force\n                from multiple compound forces.\n") ;
    printf("Authors:        s10172747\n") ;
    printf("                s10173318\n\n");
    printf("Press any key to continue\n") ;
    getch();
}

/*Function[draw_menu]
**************************
Description      : Controls the main menu. Not only a draw function, draw is a misnomer but I can't be asked to change.
Input Parameters : None
Output Returns   : None (Void)
*/
void draw_menu(float magnitude_resultant,
               float angle_resultant,
               float x_resultant,
               float y_resultant,
               float moment_resultant,
               int magnitude_precision,
               int angle_precision,
               int x_resultant_precision,
               int y_resultant_precision,
               int moment_precision,
               int degree_bool,
               int moment_flag)
{
    float d_angle_resultant;

    if (degree_bool==1)
    {
        d_angle_resultant = angle_resultant * 180 / PI;
    }


        printf("      <<Forces>>     \n");
        printf("=====================");                                                            console_plot(x_resultant,y_resultant,0,0);
        printf("Magnitude :     %.*f   ", magnitude_precision , magnitude_resultant);               console_plot(x_resultant,y_resultant,1,magnitude_precision + digit_count(magnitude_resultant));

        if (degree_bool==1)
        {
                printf("Angle :         %.*f%c   ", angle_precision , d_angle_resultant, 248);      console_plot(x_resultant,y_resultant,2,angle_precision + 1 + digit_count(d_angle_resultant));
        }
        else if (degree_bool==0)
        {
                printf("Angle :         %.*f rad",angle_precision , angle_resultant);               console_plot(x_resultant,y_resultant,2,angle_precision + 1 + digit_count(angle_resultant));
        }
        printf("X - Resultant : %.*f   ", x_resultant_precision , x_resultant);                     console_plot(x_resultant,y_resultant,3,x_resultant_precision + digit_count(x_resultant));
        printf("Y - Resultant : %.*f   ", y_resultant_precision , y_resultant);                     console_plot(x_resultant,y_resultant,4,y_resultant_precision + digit_count(y_resultant));

        printf("Moment :        %.*f   ", moment_precision ,moment_resultant);                      console_plot(x_resultant,y_resultant,5,moment_precision + digit_count(moment_resultant));
        printf("=====================");                                                            console_plot(x_resultant,y_resultant,6,0);
        toolbar(degree_bool);                                                                       console_plot(x_resultant,y_resultant,7,-8);

        menu_options(x_resultant,y_resultant);
}

/*Function[Digit Count]
**************************
Description      : Counts the number of digits in a float and returns as an integer
Input Parameters : subject(Float)
Output Returns   : log10(subject) or 0 (Int)
*/
int digit_count(float subject)
{
    if (subject>0)
        return log10(subject);
    else if (subject<0)
        return log10(-subject)+1;
    else
        return 0;
}

/*Function[input_magnitude]
**************************
Description      : Prompts magnitude, checks for validity
Input Parameters : None
Output Returns   : magnitude (Float) - Used by event_handler
*/
float input_magnitude()
{
        float magnitude = 0;
        printf("Enter magnitude : ");
        scanf("%f",&magnitude);
        if (magnitude < 0)
        {
            system("CLS");
            printf("Value of magnitude cannot be negative.\n\n");
            printf("Press any key to continue\n") ;
            getch();
            return input_magnitude();                                                               //Calls to re-enter values
        }
        else if (magnitude >= 3.4E+38)
        {
            system("CLS");
            printf("Value of magnitude cannot be bigger than 3.4E+38.\n\n");
            printf("Press any key to continue\n") ;
            getch();
            return input_magnitude();                                                               //Calls to re-enter values
        }
        else if (magnitude < 3.4E+38 && 0 < magnitude)
        {
            return magnitude;
        }
        else
        {
            system("CLS");
            printf("Invalid Input\n\n");
            printf("Press any key to continue\n") ;
            getch();
            return 0;                                                               //Calls to re-enter values
        }
}

/*Function[input_angle]
**************************
Description      : Prompts angle, adjusts to equivalent angle
Input Parameters : degree_bool (Int) - Used to handle angle unit, from event_handler
Output Returns   : angle (Float) - Used by event_handler
*/
float input_angle(int degree_bool)
{
        float angle = 0;
        printf("Enter angle : ");
        scanf("%f",&angle);
        resolve_angle(degree_bool, angle);
        return angle;
}

/*Function[resolve_angle]
**************************
Description      : Not implemented
Input Parameters : degree_bool (Int)
                   angle       (Float)
Output Returns   : angle       (Float)
*/
float resolve_angle(int degree_bool, float angle)
{
        int flag = 1;

        if (degree_bool == 0)
        {
                while(flag==1)
                {
                    if (0 <= angle && angle <= (2*PI))
                    {
                        flag=0;
                        break;
                    }
                    else if (0 > angle)
                    {
                        angle = angle + (2*PI);
                        flag=1;
                    }
                    else if (angle > (2*PI))
                    {
                        angle = angle - (2*PI);
                        flag=1;
                    }

                }
        }
        else if (degree_bool == 1)
        {
                while(flag==1)
                {
                    if (0 <= angle && angle <= 360)
                    {
                        flag=0;
                        break;
                    }
                    else if (angle < 0)
                    {
                        angle = angle + (360);
                        flag=1;

                    }
                    else if (angle > (360))
                    {
                        angle = angle - (360);
                        flag=1;

                    }

                }
        }
        return angle;
}

/*Function[input_x_pos]
**************************
Description      :
Input Parameters : none
Output Returns   : angle       (Float)
*/
float input_x_pos()
{
        float x_pos;
        int i;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //Get handle to console output
        COORD cursor_coords;

        printf("Enter %cx : ",127);
        scanf("%f",&x_pos);
        if (x_pos <= 2147483646 && x_pos >= -2147483647)
        {
            return x_pos;
        }
        else
        {
            if (x_pos > 2147483646)
            printf("\nToo big, must be under 2147483647 for accurate computation.\nPress any key to continue.");

            else if (x_pos < -2147483647)
            printf("\nToo small, must be above -2147483648 for accurate computation.\nPress any key to continue.");

            else
            {
                printf("Error : input_x_pos()");
                exit(-1);
            }

            cursor_coords.X = 0;
            cursor_coords.Y = 18;
            getch();
            SetConsoleCursorPosition(hConsole,cursor_coords);
            for (i=18;i<=24;i++)
            {
                cursor_coords.Y = i;
                SetConsoleCursorPosition(hConsole,cursor_coords);
                printf("                                                                                ");
            }
            cursor_coords.Y = 18;
            SetConsoleCursorPosition(hConsole,cursor_coords);
            return input_x_pos();

        }

}

/*Function[input_x_pos]
**************************
Description      :
Input Parameters : none
Output Returns   : angle       (Float)
*/
float input_y_pos()
{
        float y_pos;
        int i;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //Get handle to console output
        COORD cursor_coords;

        printf("Enter %cy : ",127);
        scanf("%f",&y_pos);

        if (y_pos < 2147483646 && y_pos > -2147483647)
        {
            return y_pos;
        }
        else
        {
            if (y_pos > 2147483646)
            printf("\nToo big, must be under 2147483647 for accurate computation.\nPress any key to continue.");

            else if (y_pos < -2147483647)
            printf("\nToo small, must be above -2147483648 for accurate computation.\nPress any key to continue.");

            else
            {
                printf("Error : input_y_pos()");
                exit(-1);
            }

            cursor_coords.X = 0;
            cursor_coords.Y = 18;
            getch();
            SetConsoleCursorPosition(hConsole,cursor_coords);
            for (i=18;i<=24;i++)
            {
                cursor_coords.Y = i;
                SetConsoleCursorPosition(hConsole,cursor_coords);
                printf("                                                                                ");
            }
            cursor_coords.Y = 18;
            SetConsoleCursorPosition(hConsole,cursor_coords);
            return input_x_pos();

        }
}

/*Function[console_plot]
**************************
Description      :
Input Parameters : x_resultant (Float)
                   y_resultant (Float)
Output Returns   : none (Void)
*/
void console_plot(float x_resultant, float y_resultant, int rowno, int indent)
{
    int x,y,i;

    int element[12][28]  =              //Apologies
    {
    {32,32,32,32,32,32,32,32,32,32,32,32,32,'Y',32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,205,205,205,205,205,205,205,205,205,205,205,205,206,205,205,205,205,205,205,205,205,205,205,205,205,32,'X'},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
    {32,32,32,32,32,32,32,32,32,32,32,32,32,186,32,32,32,32,32,32,32,32,32,32,32,32,32,32}
    };


    if ( x_resultant == 0 && y_resultant == 0)                //Centre
        {}
    else if ( x_resultant > 0 && y_resultant > 0)           //NE
        {
            y = 6;
            for (x=14;x<=26;x++)
            {
                    y=y-1;
                    element[y][x] = '/';

            }
            element[5][15] = ')';
        }
    else if ( x_resultant < 0 && y_resultant > 0)           //NW
        {
            y = 6;
            for (x=12;x>=8;x--)
            {
                    y=y-1;
                    element[y][x] = '\\';

            }
            element[5][11] = '(';
        }
    else if ( x_resultant < 0 && y_resultant < 0)           //SW
        {
            y = 6;
            for (x=12;x>=8;x--)
            {
                    y=y+1;
                    element[y][x] = '/';

            }
            element[7][11] = '(';
        }
    else if ( x_resultant > 0 && y_resultant < 0)           //SE
        {
            y = 6;
            for (x=14;x<=26;x++)
            {
                if (y<=10)
                {
                    y=y+1;
                    element[y][x] = '\\';
                }
            }
            element[7][15] = ')';
        }
    else if ( x_resultant > 0 && y_resultant == 0)           //E
        {
            for (x=15;x<=24;x++)
            {
                element[6][x] = 219;
            }
        }
    else if ( x_resultant == 0 && y_resultant > 0)           //N
        {
            for (y=5;y>=2;y--)
            {
                element[y][13] = 219;
            }

        }
    else if ( x_resultant < 0 && y_resultant == 0)           //W
        {
            for (x=11;x>=2;x--)
            {
                element[6][x] = 219;
            }
        }
    else if ( x_resultant == 0 && y_resultant < 0)           //S
        {
            for (y=7;y<=10;y++)
            {
                element[y][13] = 219;
            }
        }

    //for(x=0;x<=11;x++)
    //{
            for (i=0;i<=(27-indent);i++)
                printf(" ");

            for(y=0;y<=27;y++)
            {
                printf("%c",element[rowno][y]);
            }
            printf("\n");
    //}
}

/*Function[console_plot_moment]
**************************
Description      : Not implemented
Input Parameters : x_pos (Float)
                   y_pos (Float)
Output Returns   : none (Void)
*/
void console_plot_moment(float x_pos, float y_pos)
{
        int i;

        x_pos = -1;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  //Get handle to console output
        COORD cursor_coords;
        COORD original_cursor_coords;
        CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
        GetConsoleScreenBufferInfo(hConsole,&screen_buffer_info);
        original_cursor_coords.X = screen_buffer_info.dwCursorPosition.X;
        original_cursor_coords.Y = screen_buffer_info.dwCursorPosition.Y;

        cursor_coords.X = 60;
        cursor_coords.Y = 21;
        SetConsoleCursorPosition(hConsole,cursor_coords);
        printf("%c",127);

        if (x_pos > 0)
        {
            cursor_coords.Y = 20;
            SetConsoleCursorPosition(hConsole,cursor_coords);
            printf("%c",201);
            for ( i=cursor_coords.X+1 ; i<70 ; i++ )
            {
                    cursor_coords.X = i;
                    SetConsoleCursorPosition(hConsole,cursor_coords);
                    printf("%c",205);
            }

        }
        else if (x_pos < 0)
        {
            cursor_coords.Y = 20;
            SetConsoleCursorPosition(hConsole,cursor_coords);
            printf("%c",187);
            for ( i=cursor_coords.X-1 ; i>50 ; i-- )
            {
                    cursor_coords.X = i;
                    SetConsoleCursorPosition(hConsole,cursor_coords);
                    printf("%c",205);
            }
        }
        else
        {

        }

        if (y_pos > 0)
        {

        }
        else if (y_pos < 0)
        {

        }
        else
        {

        }

        SetConsoleCursorPosition(hConsole,original_cursor_coords);
}

/*Function[toolbar]
**************************
Description      : Adds degrees/radians display under forces table
Input Parameters : degree_bool - Used to handle angle unit
Output Returns   : none (Void)
*/
void toolbar(int degree_bool)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    printf("Mode: ");

    switch (degree_bool)
    {
        case 0:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("Radians");
            break;
        }
        case 1:
        {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            printf("Degrees");
            break;
        }

    }
    SetConsoleTextAttribute(hConsole, saved_attributes);

}

/*Function[message_chain]
**************************
Description      : Returns retrieved keypress ID. Tbh I don't know why this is here.
Input Parameters : none (Void)
Output Returns   : x (Int)
*/
int message_chain()
{
    int x;
    x = getch();
    fflush(stdin);
    return x;
}

/*Function[menu_options]
**************************
Description      : Main Menu print and selection of options
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void menu_options(float x_resultant, float y_resultant)
{
    printf("Options:        [Enter]      Enter Force");                           console_plot(x_resultant,y_resultant,8,19);
    printf("                [Ctrl+Enter] Enter Moment");                          console_plot(x_resultant,y_resultant,9,20);
                                                                                  console_plot(x_resultant,y_resultant,10,-21);
    printf("                [a]          Clear");                                 console_plot(x_resultant,y_resultant,11,13);
    printf("                [s]          Settings");
    printf("\n                [d]          Toggle Angle Unit");
    printf("\n\n");

    printf("Input Option:   ");
}

/*Function[colours_menu]
**************************
Description      : Colours Menu under settings menu
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void colours_menu()
{
    int message_stream;

    while (true)
    {
        system("CLS");
        printf("======   Colour Menu    ======\n\n");
        printf("[1]  Text\n");
        printf("[2]  Background (Black Text)\n\n");
        printf("[Esc]  Exit");
        message_stream = getch();
        switch (message_stream)
        {
            case 27 :
            {
               break;
            }
            case 49:
            {
                fflush(stdin);
                text_colours_menu();
                break;
            }
            case 50:
            {
                fflush(stdin);
                background_colours_menu();
                break;
            }
            default:
                colours_menu();
        }
        break;
    }
}

/*Function[list_colours_menu]
**************************
Description      : Lists colours in text_colours_menu && background_colours_menu
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void list_colours_menu()
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            WORD saved_attributes;
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            saved_attributes = consoleInfo.wAttributes;

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            printf("[1]  White\n");


            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
            printf("[2]  Grey\n");

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_INTENSITY);
            printf("[3]  Red\n");


            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
            printf("[4]  Green\n");

            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_INTENSITY);
            printf("[5]  Blue\n");

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_GREEN);
            printf("[6]  Yellow\n");

            SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_BLUE);
            printf("[7]  Magenta\n");

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE);
            printf("[8]  Cyan\n");

            SetConsoleTextAttribute(hConsole, saved_attributes);
            printf("[0]  Default\n\n\n");
}

/*Function[text_colours_menu]
**************************
Description      : Coloured Text
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void text_colours_menu()
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            //WORD saved_attributes;
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            //saved_attributes = consoleInfo.wAttributes;

            int message_stream;

            system("CLS");
            printf("======   Text Menu    ======\n\n");
            list_colours_menu();
            printf("[Esc]  Exit");
            message_stream=getch();
            switch(message_stream)
            {
                case 49: SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY); break;//white
                case 50: SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY); break;//black
                case 51: SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_INTENSITY); break;//red
                case 52: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_INTENSITY); break;//green
                case 53: SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_INTENSITY); break;//blue
                case 54: SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_GREEN); break;//yellow
                case 55: SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_BLUE); break;//magenta
                case 56: SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE); break;//cyan
                case 48: SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN); break;//default
                case 27: break;
            }
}

/*Function[background_colours_menu]
**************************
Description      : Coloured Background
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void background_colours_menu()
{
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            //WORD saved_attributes;
            GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
            //saved_attributes = consoleInfo.wAttributes;

            int message_stream;

            system("CLS");
            printf("======   Background Menu    ======\n\n");
            list_colours_menu();
            printf("[Esc]  Exit");
            message_stream=getch();
            switch(message_stream)
            {
                case 49: SetConsoleTextAttribute(hConsole, BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY); break;//white
                case 50: SetConsoleTextAttribute(hConsole, BACKGROUND_INTENSITY); break;//black
                case 51: SetConsoleTextAttribute(hConsole, BACKGROUND_RED|BACKGROUND_INTENSITY); break;//red
                case 52: SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN|BACKGROUND_INTENSITY); break;//green
                case 53: SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE|BACKGROUND_INTENSITY); break;//blue
                case 54: SetConsoleTextAttribute(hConsole, BACKGROUND_RED|BACKGROUND_GREEN); break;//yellow
                case 55: SetConsoleTextAttribute(hConsole, BACKGROUND_RED|BACKGROUND_BLUE); break;//magenta
                case 56: SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN|BACKGROUND_BLUE); break;//cyan
                case 48: SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|0); break;//default
                case 27: break;
                default :{}
            }
}

/*Function[help_menu]
**************************
Description      : Help Menu
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void help_menu()
{
    int message_stream;
    while (true)
    {
        system("CLS");
         printf("=======    Help/Info     =======\n\n");
         printf("Welcome to the help menu.\n");
         printf("Please choose a category.\n\n");
         printf("[1]        General Information\n");
         printf("[2]        User Interface\n");
         printf("[3]        Calculations\n\n");
         printf("[Esc]      Exit\n");
         message_stream = getch();
         printf("%d",message_stream);//db

         switch (message_stream)
         {
            case 27 :
            {
                break;
            }
            case 49 :
            {
                help_menu_ginfo();
                break;
            }
            case 50 :
            {
                help_menu_ui();
                break;
            }
            case 51 :
            {
                help_menu_calc();
                break;
            }
            default :
            {
                help_menu();
            }
        }
        break;
    }
}

/*Function[change_page]
**************************
Description      : Adds degrees/radians display under forces table
Input Parameters : page (Int) - Current page of help_menu
Output Returns   : none (Void)
*/
void change_page(int page)
{
        int message_stream;
        printf("Use arrow keys to navigate.\n");
        printf("<<                                  >>");
        message_stream = getch();
        switch(message_stream)
        {
            case 27  :
            {
                break;
            }
            case 224  :
            {
                message_stream = getch();
                switch(message_stream)
                {
                    case 27 :
                    {
                        break;
                    }
                    case 75 :
                    {
                        page = page - 1;
                        break;
                    }
                    case 77 :
                    {
                        page = page + 1;
                        break;
                    }
                    default :;
                }
                if (message_stream == 27)
                break;
            }
        }
    if (message_stream != 27)
    {
        switch (page%3)
        {
            case 0: help_menu_ginfo();
            case 1: help_menu_ui();
            case 2: help_menu_calc();
        }
    }

}

/*Function[help_menu_ginfo]
**************************
Description      : General Information under help menu
Input Parameters : none (Void)
Output Returns   : none (Void)
*/

void help_menu_ginfo()
{
    while (true)
    {
        time_t t = time(NULL);
        struct tm stime = *localtime(&t);
        system("CLS");
        printf("    << General Information >>\n");
        printf("==================================\n\n");
        printf("Author: s10172747 \n");
        printf("Time  :  %d:%d:%d\n",stime.tm_hour, stime.tm_min, stime.tm_sec);
        printf("Date  :  %d/%d/%d\n\n", stime.tm_mday, stime.tm_mon + 1, stime.tm_year + 1900);
        printf("This is a project for 6compro.\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        change_page(9);
        break;
    }
}

/*Function[help_menu_ui]
**************************
Description      : User Interface under help menu
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void help_menu_ui()
{
    while (true)
    {
        system("CLS");
        printf("      << User Interface >>\n");
        printf("==================================\n\n");
        printf("Work In Progress, there is no need for one yet.\n");
        printf("\n");
        printf("\n\n");
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        change_page(10);
        break;
    }
}

/*Function[help_menu_calc]
**************************
Description      : Calculation under help menu
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void help_menu_calc()
{
    while (true)
    {
        system("CLS");
        printf("        << Calculation >>\n");
        printf("==================================\n\n");
        printf(" n rad = n%c * %c\n",248,227);
        printf("        --------\n");
        printf("          180\n");
        printf("\n");
        printf(" %cX = magnitude * cos ( %c )\n",127,233);
        printf("\n");
        printf(" %cY = magnitude * sin ( %c )\n",127,233);
        printf("\n");
        printf(" magnitude = %c( %cX%c + %cY%c )\n",251,127,253,127,253);
        printf("\n");
        printf(" %c = atan ( %cY %c %cX )\n",233,127,246,127);
        printf("\n");
        printf(" moment = %c f * d\n",228);
        printf("\n");
        printf("\n\n\n\n\n\n");
        change_page(11);
        break;
    }
}

/*Function[help_menu_calc]
**************************
Description      : Prompts user to change precision of output, not implemented
Input Parameters : none (Void)
Output Returns   : Precision (Int)
*/
int precision_menu(int c_magnitude_precision,int c_angle_precision,int c_x_precision,int c_y_precision)
{
    int precision , message_stream, parameter_option;
    while (true)
    {
        system("CLS");
        printf("======   Precision    ======\n\n");
        printf
        (
"What do you want to edit?:\n\n\
[1]   Magnitude     (Current : %d)                          \n\
[2]   Angle         (Current : %d)                          \n\
[3]   X-Resultant   (Current : %d)                          \n\
[4]   Y-Resultant   (Current : %d)                          \n\
[0]   All                                                   \n\n\
[Esc] Exit\n\n\
Input:", c_magnitude_precision, c_angle_precision, c_x_precision, c_y_precision
        );
        parameter_option = getch();
        switch (parameter_option)
        {
            case 27 :
            {
                break;
            }
            default :
            {
                if (message_stream == 49 || 50 || 51 || 52 || 48)
                {
                        precision_label:
                        system("CLS");
                        printf("======   Precision    ======\n\n");
                        printf("Enter the required precision (in decimal places):\n[0-6] or [Esc]\n\nInput:");
                        message_stream = getch();

                            if (message_stream >= 49 && message_stream <= 55)
                            {
                                precision = (parameter_option - 48) + 10 * (message_stream - 48);
                                return precision;
                                break;
                            }
                            else if (message_stream == 27)
                            {
                                precision_menu(c_magnitude_precision, c_angle_precision, c_x_precision, c_y_precision);
                            }
                            else
                            {
                                goto precision_label;
                            }
                }
                else
                {
                    precision_menu(c_magnitude_precision, c_angle_precision, c_x_precision, c_y_precision );
                }
            }
        }
    break;
    }
    return 0;
}

char *saveload_menu()
{
    int message_stream;
    system("CLS");
    printf("======   Save/Load    ======\n\n");
    printf("[1]   Save\n");
    printf("[2]   Load\n\n");

    printf("[Esc] Exit\n");
    message_stream = getch();

    switch (message_stream)
    {
        case 49: save_for(); return 0;
        case 50: return load_for();
        case 27: return 0;
        default: saveload_menu();
    }

}

void save_for()
{
    /*
    int i;
    char filename[128];

    system("cls");
    printf("<<   Browse Files    >>\n\n");

      DIR *dp;
      struct dirent *ep;
      dp = opendir ("./sav");
      if (dp != NULL)
      {
        i=1;
        while (ep = readdir (dp))
        {

            printf("%d  :   ",i);

            puts (ep->d_name);
            i = i+1;
        }
        (void) closedir (dp);
      }
      else
        printf("ERROR: /sav directory cannot be opened.");

    printf("\n\nSave As  : ");
    receiveInput( filename );
    printf("\n");
    cprint(cGreen,bdefault,"[Low] ");
    cprint(fdefault,bdefault,"Attempting to save as %s\n", filename);

      if (dp != NULL)
      {
        i=1;
        while (ep = readdir (dp))
        {

            printf("%d  :   ",i);

            puts (ep->d_name);
            i = i+1;
        }
        (void) closedir (dp);
      }
        */

        system("cls");
        cprint(fdefault,bdefault,"Overwrite Save?  [y/n]");
        switch( tolower( getch() ) )
        {
            case 'y' :
                system("cls");
                cprint(cGreen,bdefault,"[Good]");
                cprint(fdefault,bdefault,"  Attempting to save\n");

                FILE *save = fopen("sav.frc", "w+");
                if (save == NULL)
                {
                    cprint(clYellow,bdefault,"[Warn] ");
                    cprint(fdefault,bdefault," Unable to open sav.frc\n");

                }

                if(!fprintf(save, "%s", p_SaveBuffer))
                {
                    cprint(cRed,bdefault,"[Bad] ");
                    cprint(fdefault,bdefault,"  Unable to write to sav.frc\n");
                }
                else
                {
                    cprint(cGreen,bdefault,"[Good]");
                    cprint(fdefault,bdefault,"  Save complete\n");
                    cprint(fdefault,bdefault,"  \nPress any key to continue");
                }
                fclose(save);

                getch();
            case 'n' : break;
            default :save_for(); break;
        }
        return 0;

}

char *load_for()
{

        static char buffer[512];

        system("cls");
        cprint(fdefault,bdefault,"Load Save?  [y/n]");
        switch( tolower( getch() ) )
        {
            case 'y' :
                system("cls");
                cprint(cGreen,bdefault,"[Good]");
                cprint(fdefault,bdefault,"  Attempting to load\n");

                FILE *save = fopen("sav.frc", "r");
                if (save == NULL)
                {
                    cprint(cRed,bdefault,"[Bad] ");
                    cprint(fdefault,bdefault,"  Unable to open sav.frc\n");

                }
                else
                {
                    fscanf(save, "%s", buffer);
                    fclose(save);
                }
                return buffer;

            case 'n' : break;
            default :load_for(); break;
        }
}

char* receiveInput( char *s ){
    scanf("%[^\n]127s",s);
    return s;
}



/*Function[confirm_exit]
**************************
Description      : Confirms and terminates program
Input Parameters : none (Void)
Output Returns   : none (Void)
*/
void confirm_exit()
{
    char message;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD menu_saved_attributes;
    menu_saved_attributes = consoleInfo.wAttributes;
    printf("\n\n[");

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("Exit");

    SetConsoleTextAttribute(hConsole, menu_saved_attributes);
    printf("] Are you sure? [y/n]");

    message = tolower( getch() );

    if (message == 'y')
    {
        exit(0);
    }
}
