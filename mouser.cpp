#include <iostream>
#include <conio.h>
#include "mouser.hpp"

using namespace std;
//myszeczka :EE
void mouse()
{
    int my, mx; //mouse position;
    INPUT_RECORD InRec; //Short of In Record, Describes an input event.
    DWORD EventCount; //Creates 32-bit unsigned integer.
    DWORD NumRead; //Creates 32-bit unsigned integer.
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE); //I don't want write that monstrocity.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); //I don't want write that monstrocity.

    while(true)
    {
        Sleep(100);
        GetNumberOfConsoleInputEvents(hIn, &EventCount); //Sets EventCount
        while(EventCount > 0)
        {
            ReadConsoleInput(hIn, &InRec, 1, &NumRead); //Read Input, and:
            if(InRec.EventType == KEY_EVENT) //If input is pressed key:
            {
                if(InRec.Event.KeyEvent.uChar.AsciiChar == 'c') //If it's 'c':
                {
                    //SuperSecretMenu. :D
                    cout << "I'm test";
                    getch();
                }
            }
            else if(InRec.EventType == MOUSE_EVENT) //If mouse caused an effect:
            {
                if(InRec.Event.MouseEvent.dwEventFlags == 1 ) //if user DClicks:
                {
                    my = InRec.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = InRec.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    COORD c;
                    c.X = 0; //Sets X coordinate.
                    c.Y = 0; //Sets Y coordinate.
                    SetConsoleCursorPosition(hOut, c); //Sets Cursor Position to c.X, c.Y.
                    cout << "X:" << mx << "; Y:" << my << "; ";
                }
                else if (InRec.Event.MouseEvent.dwEventFlags == 0) //Gets where mouse is located:
                {
                    my = InRec.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = InRec.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)                    }
                }
            GetNumberOfConsoleInputEvents(hIn, &EventCount); //Gets Number of Console Input Events.
            }
        }
    }
}