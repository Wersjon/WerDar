#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <string>

using namespace std;

int mx, my; //Global variables for mouse X and mouse Y
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

bool doClick; //If this value is true, it means user is holding mouse1/2

void mouse(void click(), void doubleclick(), void moving(), void keypress(char input))
{
    INPUT_RECORD Record; //Describes an input event.
    DWORD EventCount; //Creates 32-bit unsigned integer.
    DWORD NumRead; //Creates 32-bit unsigned integer.

    bool doChar; //Function is running when key is pressed and unpressed, so it's for removing 2 function runs

    while(true)
    {
        Sleep(10);
        GetNumberOfConsoleInputEvents(hIn, &EventCount); //Sets EventCount
        while(EventCount > 0)
        {
            ReadConsoleInput(hIn, &Record, 1, &NumRead); //Read Input
            if(Record.EventType == KEY_EVENT) //If input is pressed key:
            {
                doChar = (doChar)?0:1;
                if(doChar == true)keypress(Record.Event.KeyEvent.uChar.AsciiChar);
            }
            if(Record.EventType == MOUSE_EVENT) //If mouse caused an effect:
            {
                if(Record.Event.MouseEvent.dwEventFlags == 0) //If user clicks:
                {
                    doClick = (doClick)?0:1;
                    my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    if(doClick == true)click();
                }
                else if(Record.Event.MouseEvent.dwEventFlags == 2) //if user DClicks:
                {
                    my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    doubleclick();
                }
                else if(Record.Event.MouseEvent.dwEventFlags == 1) //Gets where mouse is located, it needs to be in bottom.
                {
                    my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    moving();
                }
            GetNumberOfConsoleInputEvents(hIn, &EventCount); //Gets Number of Console Input Events.
            }
        }
    }
}

void hidecursor() //Hides Cursor from user: (doesn't work if user resized window[?])
{
    CONSOLE_CURSOR_INFO CURSOR;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CURSOR);
}

void tp(int x, int y) //Teleports coordinates:
{
    COORD c; //Creates Coordinates variable named c.
    c.X = x; //Sets X coordinate.
    c.Y = y; //Sets Y coordinate.
    SetConsoleCursorPosition(hOut, c); //Sets Cursor Position to c.X, c.Y.
}

void setColor(int bg, int c) //sets Console colors:
{
    SetConsoleTextAttribute(hOut, bg*16 + c);
}

void clear() //Clears 80x25 Screen:
{
    tp(0, 0);
    printf("%2000d \n"); //Prints 2000 chars.
}

int whatColor(char x)
{
    //if(x == '0')return 0;
    if(x == '1')return 1;
    else if(x == '2')return 2;
    else if(x == '3')return 3;
    else if(x == '4')return 4;
    else if(x == '5')return 5;
    else if(x == '6')return 6;
    else if(x == '7')return 7;
    else if(x == '8')return 8;
    else if(x == '9')return 9;
    else if(x == 'A')return 10;
    else if(x == 'B')return 11;
    else if(x == 'C')return 12;
    else if(x == 'D')return 13;
    else if(x == 'E')return 14;
    else if(x == 'F')return 15;
    else return 0;
}

void load(string filename)
{
    /*Wer-Dar Paint v-1.1*/
    char area[80][25];

    fstream openfile;
    string holder;
    int i1=0, i2=0;

    openfile.open(filename + ".wdi", ios::in);
    if(openfile.good() == false)
    {
        cout << "error 404";
        openfile.close();
        return;
    }
    openfile.close();
    openfile.open(filename + ".wdi", ios::in);
    while(getline(openfile, holder))
    {
        if(i1>0)
        {
            while(i2<80)
            {
                area[i2][i1-1] = holder[i2];
                if(area[i2][i1-1] != '#')
                {
                    tp(i2, i1-1);
                    setColor(whatColor(area[i2][i1-1]), whatColor(area[i2][i1-1]));
                    printf("%c", area[i2][i1-1]);
                }
                i2++;
            }
        }
        i2=0;
        i1++;
    }
    tp(0, 0);
    openfile.close();
}