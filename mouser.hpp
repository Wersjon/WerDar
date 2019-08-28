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
private:
    bool spawned = false;
    char clear = ' ';
public:
    bool drawMode = 0;
    short X = 1, Y = 1;
    bool dirUp = false; //direction Up, Down
	bool dirLeft = false; //direction Left, Right
    string name;
    char symbol;

    void spawn(short x, short y)
	{
		if(!spawned)
		{
			spawned = true;
			X = x;
			Y = y;
			tp(x, y);
			cout<<symbol;
		}
	}
    void sayHello()
    {
        cout<<"Hi "<<name<<", symbol '"<<symbol<<"'"<<endl;
    }
    void hide()
	{
		if(spawned) spawned = false;
		tp(X, Y); cout<<clear;
	}
    void go(char ch)
	{
		if(spawned)
		{
			tp(X, Y); if(!drawMode) cout<<clear;

			switch (ch)
			{
			case 'x': //draw mode
				{
                    drawMode = drawMode ? 0 : 1;
				}
				break;
			case 'w':
				{
					dirUp = true;
					Y--;
				}
				break;
			case 's':
				{
					dirUp = false;
					Y++;
				}
				break;
			case 'a':
				{
					dirLeft = true;
					X--;
				}
				break;
			case 'd':
				{
					dirLeft = false;
					X++;
				}
				break;
			case 'e':
				{
					dirUp = true; Y--;
					dirLeft = false; X++;
				}
				break;
			case 'q':
				{
					dirUp = true; Y--;
					dirLeft = true; X--;
				}
				break;
			case 'z':
				{
					dirUp = false; Y++;
					dirLeft = true; X--;
				}
				break;
			case 'c':
				{
					dirUp = false; Y++;
					dirLeft = false; X++;
				}
				break;

			default:
				break;
			}

			tp(X, Y); cout<<symbol;
		}
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
                if(InRec.Event.KeyEvent.uChar.AsciiChar)
                {
                    char ch = getch();
                    switch (ch)
                    {
                    case 27: return 0;
                    case '0': //test, terminate mouser :D
                        {
                            system("cls");
                            cout<<"TEST";
                        }
                        break;
                    case '1': //spawn object
                        {
                            wersjon.spawn(wersjon.X, wersjon.Y);
                        }
                        break;
                    case '2': //hide object
                        {
                            wersjon.hide();
                        }
                        break;
                    case '3': //spawn object
                        {
                            darxe.spawn(darxe.X, darxe.Y);
                        }
                        break;
                    case '4': //hide object
                        {
                            darxe.hide();
                        }
                        break;
                    
                    default: //move objects
                        {
                            wersjon.go(ch);
                            darxe.go(ch);
                        }
                        break;
                    }
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