#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <string>

using namespace std;

short mx, my; //Global variables for mouse X and mouse Y
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

bool doClick; //If this value is true, it means user is holding mouse1/2

void mouse(void click(), void doubleclick(), void moving(), void keypress(char input))
{
    INPUT_RECORD Record; //Describes an input event.
    DWORD NumRead; //Creates 32-bit unsigned integer.
    bool doChar; //Function is running when key is pressed and unpressed, so it's for removing 2 function runs

    while(true)
    {
        Sleep(10);
        ReadConsoleInput(hIn, &Record, 1, &NumRead); //Read Input
        if(Record.EventType == KEY_EVENT) //If input is pressed key:
        { 
            doChar = (doChar) ?0 :1; //Records reads press & unpress, so it's nessesary to have this and if below:
            if(doChar == true) keypress(Record.Event.KeyEvent.uChar.AsciiChar); //runs function that contains char
        }
        if(Record.EventType == MOUSE_EVENT) //If mouse caused an effect:
        {
            if(Record.Event.MouseEvent.dwEventFlags == 0) //If user clicks:
            {
                doClick = (doClick) ?0 :1; //Records reads press & unpress, so it's nessesary to have this and if below 
                my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                if(doClick == true) click(); //runs click
            }
            else if(Record.Event.MouseEvent.dwEventFlags == 2) //if user DClicks:
            {
                my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                doubleclick(); //runs doubleclick
            }
            else if(Record.Event.MouseEvent.dwEventFlags == 1) //Gets where mouse is located, it needs to be in bottom.
            {
                my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                moving(); //runs moving
            }
        }
    }
}

void hideCursor() //Hides Cursor from user: (doesn't work if user resized window[?])
{
    CONSOLE_CURSOR_INFO cursorInfo; //Sets variable called cursorInfo that contaisn cursors info
    cursorInfo.dwSize = 1; //Sets it's size to 1
    cursorInfo.bVisible = FALSE; //Makes it invisible
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //Sets value into cmd
}

void tp(int x, int y) //Teleports coordinates:
{
    COORD coords; //Creates Coordinates variable named c.
    coords.X = x; //Sets X coordinate.
    coords.Y = y; //Sets Y coordinate.
    SetConsoleCursorPosition(hOut, coords); //Sets Cursor Position to c.X, c.Y.
}

void setColor(int bg, int c) //sets Console colors:
{
    /*
        // Colors are implemented in numbers
        // After every 16*x there is new background, so it's: 0 - black; 16 - Blue; 32 - Green;
        // There is new color for char every 1, and it resets after hitting 16, so it's:  0 - black; 1 - Blue; 2 - Green;
    */
    SetConsoleTextAttribute(hOut, bg * 16 + c); //Sets color
}

void clear() //Clears 80x25 Screen:
{
    tp(0, 0); //teleports to 0, 0
    printf("%2000d \n"); //Prints 2000 chars
}

int whatColor(char x) //Says about color of "char x". Colors are stored in HEX value in .wdi files:
{
    if(x == '1') return 1;
    else if(x == '2') return 2;
    else if(x == '3') return 3;
    else if(x == '4') return 4;
    else if(x == '5') return 5;
    else if(x == '6') return 6;
    else if(x == '7') return 7;
    else if(x == '8') return 8;
    else if(x == '9') return 9;
    else if(x == 'A') return 10;
    else if(x == 'B') return 11;
    else if(x == 'C') return 12;
    else if(x == 'D') return 13;
    else if(x == 'E') return 14;
    else if(x == 'F') return 15;
    else return 0;
}

void loadfile(string filename)
{
    /*Wer-Dar Paint v-1.4*/
    char area[80][25], area2[80][25], chars[80][25]; //sets variable for 3 painting layers
    fstream openfile;
    string holder;
    int i1 = 0, i2 = 0;

    openfile.open(filename + ".wdi", ios::in); //opens .wdi file
    if(openfile.good() == false) //if it doesn't exist, it displays "error 404"(file not found).
    {
        tp(0, 0); setColor(0, 15);
        cout << "error 404";
        openfile.close();
        return;
    }
    openfile.close();
    openfile.open(filename + ".wdi", ios::in);
    while(getline(openfile, holder)) //Opens file, and gets to every line value to holder
    {
        if(i1 < 26 && i1 > 0)
        {
            while(i2 < 80)
            {
                area[i2][i1 - 1] = holder[i2]; //Loads to area[x][y] holder[x] value, every iteration, there is new y in holder.
                i2++; //x is 1 higher
            }
        }
        if(i1 > 27 && i1 < 53)
        {
            while(i2 < 80)
            {
                area2[i2][i1 - 28] = holder[i2]; //Loads chars to area2, similiar to area, this one reads lower part of .wdi file
                i2++;
            }
        }
        if(i1 > 54 && i1 < 80)
        {
            while(i2 < 80)
            {
                chars[i2][i1 - 55] = holder[i2]; //Loads chars to chars[x][y]
                i2++;
            }
        }
        i2=0;
        i1++;
    }
    i1=0; i2=0;
    while(i1 < 25) //Displays paiting on canvas
    {
        while(i2 < 80)
        {
            tp(i2, i1);
            setColor(whatColor(area[i2][i1]), whatColor(area2[i2][i1])); //Sets color of area and area2 by whatColor
            if(area[i2][i1]!='#') printf("%c", chars[i2][i1]); //If char isn't "invisible", it doesn't print it.
            i2++;
        }
        i1++; i2 = 0;
    }
    openfile.close();
}

/*void loadfile(string filename)
{
    // Wer-Dar Paint v-1.3
    char area[80][25], area2[80][25], invisible = 177;
    fstream openfile;
    string holder;
    int i1=0, i2=0;

    openfile.open(filename+".wdi", ios::in);
    if(openfile.good() == false)
    {
        cout << "error 404";
        openfile.close();
        return;
    }
    openfile.close();
    openfile.open(filename+".wdi", ios::in);
    while(getline(openfile, holder))
    {
        if(i1 < 26 && i1>0)
        {
            while(i2<80)
            {
                area[i2][i1-1] = holder[i2];
                i2++;
            }
        }
        if(i1 > 27)
        {
            while(i2<80)
            {
                area2[i2][i1-28] = holder[i2];
                i2++;
            }
        }
    i2=0;
    i1++;
    }
    i1=0; i2=0;
    while(i1 < 25)
    {
        while(i2 < 80)
        {
            tp(i2, i1);
            setColor(whatColor(area[i2][i1]), whatColor(area2[i2][i1]));
            if(area[i2][i1]!='#') printf("%c", invisible);
            i2++;
        }
        i1++; i2 = 0;
    }
    openfile.close();
}*/