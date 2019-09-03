#include <iostream>
//#include <windows.h>
//#include <conio.h>
#include <cstdio>
#include <vector>

#include "mouser.hpp"

using namespace std;

//random int number <from,to>
int random(int from, int to)
{
	short size(to - from + 1);

	vector <short> _randoms(size + 10);
	for (size_t i = 0; i < size + 10; i++)
	{
		_randoms.at(i) = rand() % size + from;
	}

	return _randoms.at(rand() % size + 10);
}

class character
{
private:
    bool spawned = false;
    bool isMissile = false;
    
    char symbol = '^';
    char clear = ' ';
    char missileSymbol;
    char missileDir; //0 - up; 1 - right; 2 - down; 3 - left;

    short xM = 0;
    short yM = 0;
    short xStartM = 0;
    short yStartM = 0;

    /*<bomb>*/
    bool isBomb = false;
    char bombSymbol = 'X';
    short xB = 0;
    short yB = 0;
    short bombDir;
    short threesec = 0;
    /*</bomb>*/

public:

    short mode = 0;
    bool isNewSecond = false;
    short playercolor = 15;
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
            setColor(0, playercolor);
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
        tp(X, Y); cout<<clear;
    }
    void putBomb()
    {
        if(!isBomb)
        {
            if(Y>2 && X<79 && viewedMap[Y-1][X]==' ')
            {
                xB = X;
                yB = Y-1;
                tp(xB, yB); printf("%c", bombSymbol);
                isBomb = true;
            }
            /*xB = X+1;
            yB = Y;
            tp(xB, yB); cout<<bombSymbol;
            isBomb = true;*/
        }
    }
    void runBomb()
    {
        setColor(0, playercolor);
        if(isBomb)
        {
            if(isNewSecond)threesec++;
            if(threesec == 0)
            {
                tp(xB, yB); printf("3");
            }
            else if(threesec == 1) 
            {
                tp(xB, yB); printf("2");
            }
            else if(threesec == 2)
            { 
                tp(xB, yB); printf("1");
            }
            if(threesec == 3)
            {
                setColor(4, 12);
                viewedMap[yB][xB+1] = ' ';
                tp(xB+1, yB); printf("X");
                viewedMap[yB][xB-1] = ' ';
                tp(xB-1, yB); printf("X");
                viewedMap[yB-1][xB] = ' ';
                tp(xB, yB-1); printf("X");
                viewedMap[yB+1][xB] = ' ';
                tp(xB, yB+1); printf("X");
                viewedMap[yB][xB] = ' ';
                tp(xB, yB); printf("X");
                isBomb = false;
                Sleep(50);
                setColor(0, playercolor);
                tp(xB+1, yB); printf(" ");
                tp(xB-1, yB); printf(" ");
                tp(xB, yB-1); printf(" ");
                tp(xB, yB+1); printf(" ");
                tp(xB, yB); printf(" ");
                threesec = 0;
            }
        }
    }
    void shot()
    {
        setColor(0, playercolor);//Sets color of missile.
        if(!isMissile)
        {
            if(missileDir == 0 && viewedMap[Y-1][X]!='#' && Y>1)
            {
                isMissile = true;
                missileSymbol = '|';
                xM = X;
                yM = Y-1;
                xStartM = xM;
                yStartM = yM;
                tp(xStartM, yStartM); printf("%c", missileSymbol);
                if(viewedMap[yM][xM]=='&')
                {
                    isMissile = false; //Destroyes missile (in code)
                    viewedMap[yM][xM]=' '; //Destroyes Wall
                    tp(xStartM, yStartM); printf(" "); //Destroyes missile (on screen)
                }
            }
        }
        /*
        if(!isMissile && X<80 && viewedMap[Y][X+1]!='#')//Checks if player isn't next to barier or console walls
        {
            isMissile = true;
            xM = X+1;
            yM = Y;
            xStartM = xM;
            yStartM = yM;
            tp(xStartM, yStartM); cout<<missileSymbol;
            if(viewedMap[yM][xM]=='&') //Checks if block next to it is wall
            {
                isMissile = false; //Destroyes missile (in code)
                viewedMap[yM][xM]=' '; //Destroyes Wall
                tp(xStartM, yStartM); printf(" "); //Destroyes missile (on screen)
            }
        }*/
    }
    void isShot()
    {
        setColor(0, playercolor);
        if(isMissile)
        {
            if(missileDir == 0 && Y>1 && (yM-yStartM <= 20))
            {
                if(viewedMap[yM-1][xM]==' ')
                {
                    tp(xM, yM); printf(" ");
                    yM--;
                    tp(xM, yM); printf("%c", missileSymbol);
                }
                else if(viewedMap[yM-1][xM]=='&')
                {
                    //If it touches wall, it kills it and itself.
                    tp(xM, yM); printf(" ");
                    isMissile = false;
                    viewedMap[yM-1][xM]=' ';
                    tp(xM, yM-1); printf(" ");
                }
                else if(viewedMap[yM-1][xM]=='#' || Y>2)
                {
                    isMissile = false; //If missile is near console walls, it's disabled;
                    tp(xM, yM); printf(" "); //Printf " " instead of missile char
                }
                else
                {
                    isMissile = false; //If missile is near console walls, it's disabled;
                    tp(xM, yM); printf(" "); //Printf " " instead of missile char
                }
            }
            else
            {
                    isMissile = false; //If missile is near console walls, it's disabled;
                    tp(xM, yM); printf(" "); //Printf " " instead of missile char
            }
        }
        /*if(xM==79)
        {
            isMissile = false; //If missile is near console walls, it's disabled;
            tp(xM, yM); printf(" "); //Printf " " instead of missile char
        }
        if(isMissile) //&& isNewSecond)
        {
            if(xM - xStartM <= 20) //Destroyes itself if it reaches 20 blocks
            {
                if(viewedMap[yM][xM+1]!='&' && viewedMap[yM][xM+1]!='#') //Checks if next blocks aren't barriers or walls
                {
                    //Those lines moves missile
                    tp(xM, yM); cout<<clear;
                    xM++;
                    tp(xM, yM); cout<<missileSymbol;
                }
                else if(viewedMap[yM][xM+1]=='&')
                {
                    //If it touches wall, it kills it and itself.
                    tp(xM, yM); cout<<clear;
                    isMissile = false;
                    viewedMap[yM][xM+1]=' ';
                    tp(xM+1, yM);
                    printf(" ");
                }
                else if(viewedMap[yM][xM+1]=='#')
                {
                    //If it touches barrier it kills itself.
                    tp(xM, yM); cout<<clear;
                    isMissile = false;
                }
            }
            else
            {
                isMissile = false;
                tp(xM, yM); cout<<clear;
            }
        }*/
    }
    void go(char ch)
	{
        setColor(0, playercolor);
		if(spawned)
		{
			tp(X, Y); cout<<clear;

			switch (ch)
			{
			case 'W':
            case 'w':
				{
                    dirUp = true; 
                    dirDown = false; dirLeft = false; dirRight = false;
                    symbol = '^';
                    if(Y>1 && Y>1 && viewedMap[Y-1][X]==' ') Y--;
				}
			break;

			case 's':
            case 'S':
				{
                    dirDown = true; 
                    dirUp = false; dirLeft = false; dirRight = false;
                    symbol = 'v';
                    if(Y<24 && viewedMap[Y+1][X]==' ' ) Y++;
				}
			break;

			case 'a':
            case 'A':
                {
                    dirLeft = true;
                    dirUp = false; dirDown = false; dirRight = false;
                    symbol = '<';
                    if(X>0 && viewedMap[Y][X-1]==' ') X--;
				}
			break;

			case 'd':
            case 'D':
				{
                    dirRight = true;
                    dirUp = false; dirDown = false; dirLeft = false;
                    symbol = '>';
                    if(X<79 && viewedMap[Y][X+1]==' ') X++;
				}
			break;

            case 'e':
            case 'E':
            {
                if(mode < 2)
                {
                    mode++;
                }
                else mode = 0;
            }
            break;

            case 'u':
            case 'U':
            {
                switch(mode)
                {
                    case 0: //Build
                    {
                        if(viewedMap[Y-1][X] == ' ')
                        {
                            tp(X, Y-1);
                            setColor(3, 11);
                            printf("&");
                            setColor(0, 15);
                            viewedMap[Y-1][X] = '&';
                        }
                    }
                    break;
                    case 1: //shot
                    {
                        if(isMissile == false)missileDir = 0;
                        shot();
                    }
                    break;
                    case 2: //bomb
                    {
                        if(isBomb == false) bombDir = 0;
                        putBomb();
                    }
                    break;
                }
            }
            break;
            /*case 'b':
            case 'B':
            {
                if(dirUp == true && Y>1 && viewedMap[Y-1][X]!='#') //Builds block for direction Up
                {
                    tp(X, Y-1);
                    setColor(3, 11);
                    printf("&");
                    viewedMap[Y-1][X] = '&';
                    setColor(0, 15);
                }
                if(dirDown == true && Y<24 && viewedMap[Y+1][X]!='#')
                {
                    tp(X, Y+1);
                    setColor(3, 11);
                    printf("&");
                    viewedMap[Y+1][X] = '&';
                    setColor(0, 15);
                }
                if(dirLeft == true && X>0 && viewedMap[Y][X-1]!='#')
                {
                    tp(X-1, Y);
                    setColor(3, 11);
                    printf("&");
                    viewedMap[Y][X-1] = '&';
                    setColor(0, 15);
                }
                if(dirRight == true && X<79 && viewedMap[Y][X+1]!='#')
                {
                    tp(X+1, Y);
                    setColor(3, 11);
                    printf("&");
                    viewedMap[Y][X+1] = '&';
                    setColor(0, 15);
                }
            }
            break;*/
			default:
			break;
			}

			tp(X, Y); cout<<symbol;
		}
	}
};

class computer
{
private:
    bool spawned = false;
    bool isMissile = false;
    
    char symbol = 'C';
    char clear = ' ';
    char missileSymbol = '-';

    short xM = 0;
    short yM = 0;
    short xStartM = 0;
    short yStartM = 0;
public:
    /*<bomb>*/
    short xB = 0;
    short yB = 0;
    char bombSymbol = 'X';
    bool isBomb = false;
    /*</bomb>*/

    bool isNewSecond = false;
    short color = 15;
    short X = 5, Y = 5;

    /*<directions> //I've added 2 for buildings mechanics :p*/
    bool dirUp = false;
    bool dirDown = false;
	bool dirLeft = false;
    bool dirRight = true;
    /*<directions>*/
    
    string name;

    void spawn(short x, short y)
	{
		if(!spawned)
		{
            setColor(0, color);
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
        tp(X, Y); cout<<clear;
    }
    void putBomb()
    {
        if(!isBomb)
        {
            xB = X+1;
            yB = Y;
            tp(xB, yB); cout<<bombSymbol;
            isBomb = true;
        }
    }
    void runBomb()
    {
        if(isBomb)
        {
            setColor(4, 12);
            viewedMap[yB][xB+1] = ' ';
            tp(xB+1, yB); printf("X");
            viewedMap[yB][xB-1] = ' ';
            tp(xB-1, yB); printf("X");
            viewedMap[yB-1][xB] = ' ';
            tp(xB, yB-1); printf("X");
            viewedMap[yB+1][xB] = ' ';
            tp(xB, yB+1); printf("X");
            viewedMap[yB][xB] = ' ';
            tp(xB, yB); printf("X");
            isBomb = false;
            Sleep(50);
            setColor(0, 15);
            tp(xB+1, yB); printf(" ");
            tp(xB-1, yB); printf(" ");
            tp(xB, yB-1); printf(" ");
            tp(xB, yB+1); printf(" ");
            tp(xB, yB); printf(" ");
        }
    }
    void shot()
    {
        setColor(0, color);//Sets color of missile.
        if(!isMissile && X<80 && viewedMap[Y][X+1]!='#')//Checks if player isn't next to barier or console walls
        {
            isMissile = true;
            xM = X+1;
            yM = Y;
            xStartM = xM;
            yStartM = yM;
            tp(xStartM, yStartM); cout<<missileSymbol;
            if(viewedMap[yM][xM]=='&') //Checks if block next to it is wall
            {
                isMissile = false; //Destroyes missile (in code)
                viewedMap[yM][xM]=' '; //Destroyes Wall
                tp(xStartM, yStartM); printf(" "); //Destroyes missile (on screen)
            }
        }
    }
    void isShot()
    {
        setColor(0, color);
        if(xM==79)
        {
            isMissile = false; //If missile is near console walls, it's disabled;
            tp(xM, yM); printf(" "); //Printf " " instead of missile char
        }
        if(isMissile/* && isNewSecond*/)
        {
            if(xM - xStartM <= 20) //Destroyes itself if it reaches 20 blocks
            {
                if(viewedMap[yM][xM+1]!='&' && viewedMap[yM][xM+1]!='#') //Checks if next blocks aren't barriers or walls
                {
                    //Those lines moves missile
                    tp(xM, yM); cout<<clear;
                    xM++;
                    tp(xM, yM); cout<<missileSymbol;
                }
                else if(viewedMap[yM][xM+1]=='&')
                {
                    //If it touches wall, it kills it and itself.
                    tp(xM, yM); cout<<clear;
                    isMissile = false;
                    viewedMap[yM][xM+1]=' ';
                    tp(xM+1, yM);
                    printf(" ");
                }
                else if(viewedMap[yM][xM+1]=='#')
                {
                    //If it touches barrier it kills itself.
                    tp(xM, yM); cout<<clear;
                    isMissile = false;
                }
            }
            else
            {
                isMissile = false;
                tp(xM, yM); cout<<clear;
            }
        }
    }
    void go(short n = 0)
	{
        setColor(0, color);
		if(spawned)
		{
			tp(X, Y); cout<<clear;

			switch (n)
			{
			case 0:
				{
                    //Depending on direction, it moves Left,Right,Top,Bottom.
                    //If Direction is Up & Player isn't near console walls & player isn't near barrier block and neither wall, it can move.
                    if(dirUp == true && Y>1 && viewedMap[Y-1][X]!='#' && viewedMap[Y-1][X]!='&')Y--;
                    else if(dirDown == true && Y<24 && viewedMap[Y+1][X]!='#' && viewedMap[Y+1][X]!='&')Y++;
                    else if(dirLeft == true && X>0 && viewedMap[Y][X-1]!='#' && viewedMap[Y][X-1]!='&')X--;
                    else if(dirRight == true && X<79 && viewedMap[Y][X+1]!='#' && viewedMap[Y][X+1]!='&')X++;
                    /*if(Y>1)
                    {
                        dirUp = true;
                        dirDown = false; dirLeft = false; dirRight = false;
					    Y--;
                    }
                    symbol = '^';*/
				}
			break;
			case 1:
				{
                    //Depending on direction, it moves Left,Right,Top,Bottom.
                    //If Direction is Up & Player isn't near console walls & player isn't near barrier block and neither wall, it can move.
                    if(dirDown == true && Y>1 && viewedMap[Y-1][X]!='#' && viewedMap[Y-1][X]!='&')Y--;
                    else if(dirUp == true && Y<24 && viewedMap[Y+1][X]!='#' && viewedMap[Y+1][X]!='&')Y++;
                    else if(dirRight == true && X>0 && viewedMap[Y][X-1]!='#' && viewedMap[Y][X-1]!='&')X--;
                    else if(dirLeft == true && X<79 && viewedMap[Y][X+1]!='#' && viewedMap[Y][X+1]!='&')X++;
                    /*if(Y<24)
                    {
                        dirDown = true;
                        dirUp = false; dirLeft = false; dirRight = false;
                        Y++;
                    }
                    symbol = 'v';*/
				}
			break;
			case 2:
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
			case 3:
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
            case 4: //0 off
                {
                    if(dirUp == true && Y>1 && viewedMap[Y-1][X]!='#') //Builds block for direction Up
                    {
                        tp(X, Y-1);
                        setColor(3, 11);
                        printf("&");
                        viewedMap[Y-1][X] = '&';
                        setColor(0, 15);
                    }
                    if(dirDown == true && Y<24 && viewedMap[Y+1][X]!='#')
                    {
                        tp(X, Y+1);
                        setColor(3, 11);
                        printf("&");
                        viewedMap[Y+1][X] = '&';
                        setColor(0, 15);
                    }
                    if(dirLeft == true && X>0 && viewedMap[Y][X-1]!='#')
                    {
                        tp(X-1, Y);
                        setColor(3, 11);
                        printf("&");
                        viewedMap[Y][X-1] = '&';
                        setColor(0, 15);
                    }
                    if(dirRight == true && X<79 && viewedMap[Y][X+1]!='#')
                    {
                        tp(X+1, Y);
                        setColor(3, 11);
                        printf("&");
                        viewedMap[Y][X+1] = '&';
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