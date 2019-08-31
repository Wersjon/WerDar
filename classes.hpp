#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdio>
#include "mouser.hpp"

using namespace std;

class character
{
private:
    bool spawned = false;
    char clear = ' ';
    bool isMissile = false;
    char missileSymbol = '-';
    short xM = 0;
    short yM = 0;
    short xStartM = 0;
    short yStartM = 0;
public:
    //bool isNewSecond = false;
    bool drawMode = 0;
    short X = 5, Y = 5;
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
    void hide() // spawn/hide
	{
		if(spawned) spawned = false;
        else
        {
            spawn(X, Y);
        }
		tp(X, Y); cout<<clear;
	}
    void shot()
    {
        if(!isMissile)
        {
            isMissile = true;
            xM = X+1;
            yM = Y;
            xStartM = xM;
            yStartM = yM;
            tp(xStartM, yStartM); cout<<missileSymbol;
        }
    }
    void isShot()
    {
        if(isMissile/* && isNewSecond*/)
        {
            if(xM - xStartM <= 20)
            {
                tp(xM, yM); cout<<clear;
                xM++;
                tp(xM, yM); cout<<missileSymbol;
            }
            else
            {
                isMissile = false;
                tp(xM, yM); cout<<clear;
            }
        }
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
			case 72:
				{
                    if(Y>1)
                    {
                        dirUp = true;
					    Y--;
                    }
				}
			break;
			case 's':
            case 80:
				{
                    if(Y<24)
                    {
                        dirUp = false;
                        Y++;
                    }
				}
				break;
			case 'a':
            case 75:
                {
                    if(X>0)
                    {
                        dirLeft = true;
                        X--;
                    }
				}
				break;
			case 'd':
            case 77:
				{
                    if(X<79)
                    {
                        dirLeft = false;
                        X++;
                    }
				}
				break;
			case 'e':
				{
                    if(Y>1 && X<79)
                    {
                        dirUp = true; Y--;
                        dirLeft = false; X++;
                    }
				}
				break;
			case 'q':
				{
                    if(Y>1 && X>0)
                    {
                        dirUp = true; Y--;
                        dirLeft = true; X--;
                    }
				}
				break;
			case 'z':
				{
                    if(Y<24 && X>0)
                    {
                        dirUp = false; Y++;
                        dirLeft = true; X--;
                    }
				}
				break;
			case 'c':
				{
                    if(Y<24 && X<79)
                    {
                        dirUp = false; Y++;
                        dirLeft = false; X++;
                    }
				}
				break;

			default:
			break;
			}

			tp(X, Y); cout<<symbol;
		}
	}
};