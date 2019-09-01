#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

using namespace std;

HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

char viewedMap[24][80]; //Map.

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

void mapReader()
{
    fstream map;
    string fstreamholder; //holds line for getline
    map.open("map.txt", ios::in); //Opens map.txt with input type.
    if(map.good() == false)
    {
        map.close();
        map.open("map.txt", ios::out); //changes input type to output, and draws how it looks.
        map << "################################################################################" << endl;
        int i = 2;
        while(i < 24)
        {
            map << "#                                                                              #" << endl;
            i++;
        }
        map << "################################################################################";
    }
    map.close();
    map.open("map.txt", ios::in);
    //Get's values from map.txt and saves it into viewedMap.
    int whatline = 0;
    int i;
    while(getline(map, fstreamholder))
    {
        i = 0;
        while(i<80)
        {
            viewedMap[whatline][i] = fstreamholder[i];
            i++;
        }
        whatline++;
    }
    int i1 = 0, i2 = 0;
    //draws map
    while(i1 < 24)
    {
        tp(0, i1+1);
        while(i2 < 80)
        {   
            if(viewedMap[i1][i2] == '#') setColor(1, 9);
            else setColor(0, 15);
            printf("%c", viewedMap[i1][i2]);
            i2++;
        }
        i2 = 0;
        i1++;
    }
}