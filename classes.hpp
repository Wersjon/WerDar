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
    bool isMissile = false;
    
    char symbol = '$';
    char clear = ' ';
    char missileSymbol = '-';

    short xM = 0;
    short yM = 0;
    short xStartM = 0;
    short yStartM = 0;

public:
    //bool isNewSecond = false;
    short X = 5, Y = 5;

    /*<directions> //I've added 2 for buildings mechanics :p*/
    bool dirUp = true;
    bool dirDown = false;
	bool dirLeft = false;
    bool dirRight = false;
    /*<directions>*/
    
    string name;

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
			tp(X, Y); cout<<clear;

			switch (ch)
			{
			break;
			case 'w':
			case 72:
				{
                    if(dirUp == true && Y>1)Y--;
                    else if(dirDown == true && Y<24)Y++;
                    else if(dirLeft == true && X>0)X--;
                    else if(dirRight == true && X<79)X++;
                    /*if(Y>1)
                    {
                        dirUp = true;
                        dirDown = false; dirLeft = false; dirRight = false;
					    Y--;
                    }
                    symbol = '^';*/
				}
			break;
			case 's':
            case 80:
				{
                    if(dirDown == true && Y>1)Y--;
                    else if(dirUp == true && Y<24)Y++;
                    else if(dirRight == true && X>0)X--;
                    else if(dirLeft == true && X<79)X++;
                    /*if(Y<24)
                    {
                        dirDown = true;
                        dirUp = false; dirLeft = false; dirRight = false;
                        Y++;
                    }
                    symbol = 'v';*/
				}
			break;
			case 'a':
            case 75:
                {
                    if(dirLeft == true)
                    {
                        dirDown = true;
                        dirLeft = false;
                        symbol = 'v';
                    }
                    else if(dirDown == true)
                    {
                        dirRight = true;
                        dirDown = false;
                        symbol = '>';
                    }
                    else if(dirRight == true)
                    {
                        dirUp = true;
                        dirRight = false;
                        symbol = '^';
                    }
                    else if(dirUp == true)
                    {
                        dirLeft = true;
                        dirUp = false;
                        symbol = '<';
                    }
                    /*if(X>0)
                    {
                        dirLeft = true;
                        dirUp = false; dirDown = false; dirRight = false;
                        X--;
                    }
                    symbol = '<';*/
				}
			break;
			case 'd':
            case 77:
				{
                    if(dirLeft == true)
                    {
                        dirUp = true;
                        dirLeft = false;
                        symbol = '^';
                    }
                    else if(dirUp == true)
                    {
                        dirRight = true;
                        dirUp = false;
                        symbol = '>';
                    }
                    else if(dirRight == true)
                    {
                        dirDown = true;
                        dirRight = false;
                        symbol = 'v';
                    }
                    else if(dirDown == true)
                    {
                        dirLeft = true;
                        dirDown = false;
                        symbol = '<';
                    }
                    /*if(X<79)
                    {
                        dirRight = true;
                        dirUp = false; dirDown = false; dirLeft = false;
                        X++;
                    }
                    symbol = '>';*/
				}
			break;
			/*case 'e':
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
			break;*/
            case 'b':
            case 'B':
            {
                if(dirUp == true && Y>1)
                {
                    tp(X, Y-1);
                    setColor(1, 1);
                    printf("#");
                    setColor(0, 15);
                }
                if(dirDown == true && Y<24)
                {
                    tp(X, Y+1);
                    setColor(1, 1);
                    printf("#");
                    setColor(0, 15);
                }
                if(dirLeft == true && X>0)
                {
                    tp(X-1, Y);
                    setColor(1, 1);
                    printf("#");
                    setColor(0, 15);
                }
                if(dirRight == true && X<79)
                {
                    tp(X+1, Y);
                    setColor(1, 1);
                    printf("#");
                    setColor(0, 15);
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