#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

using namespace std;

int mx, my; //Global variables for mouse X and mouse Y
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

void waiter(void whatido(), int howlong) //Sleeps howlong amount of time, and performs an action(function)
{
    Sleep(howlong);
    whatido();
}

void hideCursor() //Hides Cursor from user: (doesn't work if user resized window[?])
{
    CONSOLE_CURSOR_INFO CURSOR;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &CURSOR);
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
    printf("%2000i \n"); //Prints 2000 chars. :D
    tp(79, 22); printf(" ");
}