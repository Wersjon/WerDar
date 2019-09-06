#include <iostream>
//#include <windows.h>
//#include <conio.h>
#include <cstdio>
#include <vector>
#define q(var) cout<<#var<<"="<<var //tests

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

    /*<directions> //I've added 2 for buildings mechanics :p*/
    bool dirUp = true;
    bool dirDown = false;
	bool dirLeft = false;
    bool dirRight = false;
    /*<directions>*/
    
public:

    short mode = 0;
    bool isNewSecond = false;
    short playercolor = 15;
    short X = 5, Y = 5;
    
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

    void hide() // spawn/hide
    {
        if(spawned) spawned = false;
        tp(X, Y); cout<<clear;
    }
    
    void putBomb()
    {
        if(!isBomb)
        {
            if(bombDir == 0 && /*Y>1 && X<79 && */viewedMap[Y-1][X]==' ')
            {
                xB = X;
                yB = Y-1;
                tp(xB, yB); printf("%c", bombSymbol);
                isBomb = true;
            }
            if(bombDir == 3 && /*X>1 && Y>1 &&*/ viewedMap[Y][X-1]==' ')
            {
                xB = X-1;
                yB = Y;
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
                if(xB<79)
                {
                    viewedMap[yB][xB+1] = ' ';
                    tp(xB+1, yB); printf("X");
                }
                if(xB>0)
                {
                    viewedMap[yB][xB-1] = ' ';
                    tp(xB-1, yB); printf("X");
                }
                if(yB>1)
                {
                    viewedMap[yB-1][xB] = ' ';
                    tp(xB, yB-1); printf("X");
                }
                if(yB<24)
                {
                    viewedMap[yB+1][xB] = ' ';
                    tp(xB, yB+1); printf("X");
                }
                viewedMap[yB][xB] = ' ';
                tp(xB, yB); printf("X");
                isBomb = false;
                Sleep(50);
                setColor(0, playercolor);

                if(xB<79)tp(xB+1, yB); 
                if(xB<79)printf(" ");

                if(xB>0)tp(xB-1, yB); 
                if(xB>0)printf(" ");
                
                if(yB>1)tp(xB, yB-1); 
                if(yB>1)printf(" ");
                
                if(yB<24)tp(xB, yB+1); 
                if(yB<24)printf(" ");

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
            if(missileDir == 3 && viewedMap[Y][X-1]!='#' && X>1)
            {
                isMissile = true;
                missileSymbol = '-';
                xM = X-1;
                yM = Y;
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
            if(missileDir == 1 && viewedMap[Y+1][X]!='#' && Y>1)
            {
                isMissile = true;
                missileSymbol = '|';
                xM = X;
                yM = Y+1;
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
    }
    void isShot()
    {
        setColor(0, playercolor);
        if(isMissile)
        {
            if(missileDir == 0 && Y>1 && (yStartM-yM < 12))
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
            else if(missileDir == 3 && X>1 && (xStartM-xM < 15))
            {
                if(viewedMap[yM][xM-1]==' ')
                {
                    tp(xM, yM); printf(" ");
                    xM--;
                    tp(xM, yM); printf("%c", missileSymbol);
                }
                else if(viewedMap[yM][xM-1]=='&')
                {
                    //If it touches wall, it kills it and itself.
                    tp(xM, yM); printf(" ");
                    isMissile = false;
                    viewedMap[yM][xM-1]=' ';
                    tp(xM-1, yM); printf(" ");
                }
                else if(viewedMap[yM][xM-1]=='#' || X>2)
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
            else if(missileDir == 1 && Y<25 && (yM-yStartM < 12))
            {
                if(viewedMap[yM+1][xM]==' ')
                {
                    tp(xM, yM); printf(" ");
                    yM++;
                    tp(xM, yM); printf("%c", missileSymbol);
                }
                else if(viewedMap[yM+1][xM]=='&')
                {
                    //If it touches wall, it kills it and itself.
                    tp(xM, yM); printf(" ");
                    isMissile = false;
                    viewedMap[yM+1][xM]=' ';
                    tp(xM, yM+1); printf(" ");
                }
                else if(viewedMap[yM+1][xM]=='#' || Y>2)
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

            case 'h':
            case 'H':
            {
                switch(mode)
                {
                    case 0: //Build
                    {
                        if(viewedMap[Y][X-1] == ' ')
                        {
                            tp(X-1, Y);
                            setColor(3, 11);
                            printf("&");
                            setColor(0, 15);
                            viewedMap[Y][X-1] = '&';
                        }
                    }
                    break;
                    case 1: //shot
                    {
                        if(isMissile == false)missileDir = 3;
                        shot();
                    }
                    break;
                    case 2: //bomb
                    {
                        if(isBomb == false) bombDir = 3;
                        putBomb();
                    }
                    break;
                }
            }
            break;

            case 'j':
            case 'J':
            {
                switch(mode)
                {
                    case 0: //Build
                    {
                        if(viewedMap[Y+1][X] == ' ')
                        {
                            tp(X, Y+1);
                            setColor(3, 11);
                            printf("&");
                            setColor(0, 15);
                            viewedMap[Y+1][X] = '&';
                        }
                    }
                    break;
                    case 1: //shot
                    {
                        if(isMissile == false)missileDir = 1;
                        shot();
                    }
                    break;
                    case 2: //bomb
                    {
                        if(isBomb == false) bombDir = 1;
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
    void destroyMissile(short& xM, short& yM)
    {
        isMissile = false; //If missile is near console walls, it's disabled;
        tp(xM, yM); printf(" "); //Printf " " instead of missile char
    }
    short dir = 0; //temporary direction

    bool info = false;
public:
    /*<bomb>*/
    short xB = 0;
    short yB = 0;
    char bombSymbol = 'X';
    bool isBomb = false;
    /*</bomb>*/

    bool isNewSecond = false;
    short color = 15;
    short X = 1, Y = 2;

    /*<directions> //I've added 2 for buildings mechanics :p*/
    bool dirUp = false;
    bool dirDown = false;
	bool dirLeft = false;
    bool dirRight = true;
    /*<directions>*/
    
    string name;

    void spawn(short& X, short& Y)
	{
		if(!spawned)
		{
            setColor(0, color);
			spawned = true;
            this->X = X;
            this->Y = Y;
			tp(X, Y);
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

        if(!isMissile)
        {
            isMissile = true;
            xStartM = X;
            yStartM = Y;
            if(dirRight)
            {
                dir = 4;
                missileSymbol = '-';
                xM = X+1;
                yM = Y;
            }
            else if(dirLeft)
            {
                dir = 3;
                missileSymbol = '-';
                xM = X-1;
                yM = Y;
            }
            else if(dirUp)
            {
                dir = 1;
                missileSymbol = ':';
                xM = X;
                yM = Y-1;
            }
            else if(dirDown)
            {
                dir = 2;
                missileSymbol = ':';
                xM = X;
                yM = Y+1;
            }

            if(viewedMap[yM][xM] == '&')
            {
                destroyMissile(xM, yM);
                viewedMap[yM][xM] = ' ';
            }
            else if(viewedMap[yM][xM] == '#') isMissile = false;
            else 
            {
                tp(xM, yM);
                cout<<missileSymbol;
            }
        }
    }
    void isShot()
    {
        setColor(0, color);
        
        if(isMissile/* && isNewSecond*/)
        {
            /*if(yM <= 2 || yM >= 23 || xM >= 78 || xM <= 1)
            {
                destroyMissile(xM, yM);
            }*/
            switch (dir)
            {
            case 4: //right
                {
                    if(xM - xStartM <= 10) //Destroyes itself if it reaches 10 blocks
                    {
                        if(viewedMap[yM][xM+1] == '&')
                        {
                            destroyMissile(xM, yM);
                            viewedMap[yM][xM+1] = ' ';
                            tp(xM+1, yM); printf(" ");
                        }
                        else if(viewedMap[yM][xM+1] == '#')
                            destroyMissile(xM, yM);
                        else
                        {
                            tp(xM, yM); printf(" ");
                            tp(++xM, yM); cout<<missileSymbol;
                        }
                    }
                    else destroyMissile(xM, yM);
                }
                break;
            case 3: //left
                {
                    if(xStartM - xM <= 10)
                    {
                        if(viewedMap[yM][xM-1] == '&')
                        {
                            destroyMissile(xM, yM);
                            viewedMap[yM][xM-1] = ' ';
                            tp(xM-1, yM); printf(" ");
                        }
                        else if(viewedMap[yM][xM-1] == '#')
                            destroyMissile(xM, yM);
                        else
                        {
                            tp(xM, yM); printf(" ");
                            tp(--xM, yM); cout<<missileSymbol;
                        }
                    }
                    else destroyMissile(xM, yM);
                }
                break;
            case 1: //up
                {
                    if(yStartM - yM <= 10)
                    {
                        if(viewedMap[yM-1][xM] == '&')
                        {
                            destroyMissile(xM, yM);
                            viewedMap[yM-1][xM] = ' ';
                            tp(xM, yM-1); printf(" ");
                        }
                        else if(viewedMap[yM-1][xM] == '#')
                            destroyMissile(xM, yM);
                        else
                        {
                            tp(xM, yM); printf(" ");
                            tp(xM, --yM); cout<<missileSymbol;
                        }
                    }
                    else destroyMissile(xM, yM);
                }
                break;
            case 2: //down
                {
                    if(yM - yStartM <= 10)
                    {
                        if(viewedMap[yM+1][xM] == '&')
                        {
                            destroyMissile(xM, yM);
                            viewedMap[yM+1][xM] = ' ';
                            tp(xM, yM+1); printf(" ");
                        }
                        else if(viewedMap[yM+1][xM] == '#')
                            destroyMissile(xM, yM);
                        else
                        {
                            tp(xM, yM); printf(" ");
                            tp(xM, ++yM); cout<<missileSymbol;
                        }
                    }
                    else destroyMissile(xM, yM);
                }
                break;
            
            default:
                break;
            }
        }
    }
    void go(short& n)
	{
        setColor(0, color);
		if(spawned)
		{
			tp(X, Y); cout<<clear;

			switch (n)
			{
			case 72://up
			case 73:
				{
                    if(Y > 2 && viewedMap[Y-1][X] != '#' && viewedMap[Y-1][X] != '&')
                    {
                        Y--;
                        dirUp = true;
                        dirDown = false;
                        dirLeft = false;
                        dirRight = false;
                    }
				}
			break;
			case 80://down
            case 79:
				{
                    if(Y < 23 && viewedMap[Y+1][X] != '#' && viewedMap[Y+1][X] != '&')
                    {
                        Y++;
                        dirUp = false;
                        dirDown = true;
                        dirLeft = false;
                        dirRight = false;
                    }
				}
			break;
			case 75://left
            case 76:
                {
                    if(X > 1 && viewedMap[Y][X-1] != '#' && viewedMap[Y][X-1] != '&')
                    {
                        X--;
                        dirUp = false;
                        dirDown = false;
                        dirLeft = true;
                        dirRight = false;
                    }
				}
			break;
			case 77://right
            case 78:
                {
                    if(X < 78 && viewedMap[Y][X+1] != '#' && viewedMap[Y][X+1] != '&')
                    {
                        X++;
                        dirUp = false;
                        dirDown = false;
                        dirLeft = false;
                        dirRight = true;
                    }
				}
			break;
            case 82: //Insert - show/hide info
                {
                    info = info ? 0 : 1;
                    tp(16, 22); cout<<"        ";
                    tp(16, 23); cout<<"        ";
                    break;
                }
            case 0: //0 off 
                {
                    //old system
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
                    //new system? not yet xd :E
                }
                break;
			default:
			    break;
			}

			tp(X, Y); cout<<symbol;
            if(info) //if 'info' is true then show informations
            {
                tp(16, 22); cout<<"C: "<<X<<","<<Y<<" ";
                tp(16, 23); cout<<n<<" ";
                if(dirUp)    cout<<"Up   ";
                if(dirDown)  cout<<"Down ";
                if(dirLeft)  cout<<"Left ";
                if(dirRight) cout<<"Right";
            }
		}
	}
};