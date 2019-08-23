#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>

using namespace std;

int mx, my; //Global variables for mouse X and mouse Y
HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

void tp(int x, int y);
class character
{
public:
    bool drawMode = 0;
    short X = 1, Y = 1;
    string name;
    char symbol;
    void showInPos(int x, int y)
    {
        tp(x, y);
        cout<<symbol;
    }
    void setPos(int X, int Y)
    {
        tp(X, Y); cout<<symbol;
    }
    void clearPos()
    {
        tp(X, Y); cout<<((drawMode)?symbol:' ');
    }
    void sayHello()
    {
        cout<<"Hi "<<name<<", symbol '"<<symbol<<"'"<<endl;
    }
}wersjon, darxe;

/*<mouse>  //*/
int mouse(void exist(), void click(), void doubleclick(),  void moving())
{
    INPUT_RECORD InRec; //Short of In Record, Describes an input event.
    DWORD EventCount; //Creates 32-bit unsigned integer.
    DWORD NumRead; //Creates 32-bit unsigned integer.

    bool doClick, doMove;

    while(true)
    {
        Sleep(10);
        exist();
        GetNumberOfConsoleInputEvents(hIn, &EventCount); //Sets EventCount
        while(EventCount > 0)
        {
            ReadConsoleInput(hIn, &InRec, 1, &NumRead); //Read Input, and:
            if(InRec.EventType == KEY_EVENT) //If input is pressed key:
            {
                switch (InRec.Event.KeyEvent.uChar.AsciiChar)
                {
                case 'c': //If it's 'c':
                    {
                        cout << "I'm test"; getch();
                    }
                    break;
                case 'x': //draw mode
                    {
                        wersjon.drawMode = (wersjon.drawMode)?0:1;
                    }
                    break;
                case 27: //exit
                    {
                        return 0;
                    }
                    break;
                case 'w': //up
                    {
                        wersjon.clearPos(); wersjon.setPos(wersjon.X, --wersjon.Y); getch();
                    }
                    break;
                case 's': //down
                    {
                        wersjon.clearPos(); wersjon.setPos(wersjon.X, ++wersjon.Y); getch();
                    }
                    break;
                case 'a': //left
                    {
                        wersjon.clearPos(); wersjon.setPos(--wersjon.X, wersjon.Y); getch();
                    }
                    break;
                case 'd': //right
                    {
                        wersjon.clearPos(); wersjon.setPos(++wersjon.X, wersjon.Y); getch();
                    }
                    break;
                case 'z': //test
                    {
                        system("cls");
                        cout<<"TEST";
                    }
                    break;
                
                default:
                    {
                        int temp(getch()); cout<<"Pressed key: "<<temp<<endl;
                    }
                    break;
                }
            }
            else if(InRec.EventType == MOUSE_EVENT) //If mouse caused an effect:
            {
                if(InRec.Event.MouseEvent.dwEventFlags == 0) //If user clicks:
                {
                    doClick = (doClick)?0:1;
                    my = InRec.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = InRec.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    if(doClick == true)click();
                }
                else if(InRec.Event.MouseEvent.dwEventFlags == 2) //if user DClicks:
                {
                    my = InRec.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = InRec.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    doubleclick();
                }
                else if(InRec.Event.MouseEvent.dwEventFlags == 1) //Gets where mouse is located, it needs to be in bottom.
                {
                    doMove = (doMove)?0:1;
                    my = InRec.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = InRec.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    if(doMove == true)moving();
                }
            GetNumberOfConsoleInputEvents(hIn, &EventCount); //Gets Number of Console Input Events.
            }
        }
    }
    return 0;
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
    printf("%2000n \n"); //Prints 2000 chars. :D
}