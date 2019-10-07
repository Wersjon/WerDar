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
    char symbol = '^';
    char clear = ' ';
    char missileSymbol;
    char missileDir; //0 - up; 1 - right; 2 - down; 3 - left;

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
    bool isMissile = false;
    bool spawned = false;
    short xM = 0;
    short yM = 0;
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
            else if(bombDir == 3 && /*X>1 && Y>1 &&*/ viewedMap[Y][X-1]==' ')
            {
                xB = X-1;
                yB = Y;
                tp(xB, yB); printf("%c", bombSymbol);
                isBomb = true;
            }
            else if(bombDir == 1 && /*Y>1 && X<79 && */viewedMap[Y+1][X]==' ')
            {
                xB = X;
                yB = Y+1;
                tp(xB, yB); printf("%c", bombSymbol);
                isBomb = true;
            }
            else if(bombDir == 2 && /*X>1 && Y>1 &&*/ viewedMap[Y][X+1]==' ')
            {
                xB = X+1;
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
            if(missileDir == 2 && viewedMap[Y][X+1]!='#' && X<80)
            {
                isMissile = true;
                missileSymbol = '-';
                xM = X+1;
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
        }
    }
    int isShot()
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
            else if(missileDir == 2 && X<80 && (xStartM-xM < 15))
            {
                if(viewedMap[yM][xM+1]==' ')
                {
                    tp(xM, yM); printf(" ");
                    xM++;
                    tp(xM, yM); printf("%c", missileSymbol);
                }
                else if(viewedMap[yM][xM+1]=='&')
                {
                    //If it touches wall, it kills it and itself.
                    tp(xM, yM); printf(" ");
                    isMissile = false;
                    viewedMap[yM][xM+1]=' ';
                    tp(xM+1, yM); printf(" ");
                }
                else if(viewedMap[yM][xM+1]=='#' || X<79)
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
        } else return 0;
        return 1;
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

            case 'k':
            case 'K':
            {
                switch(mode)
                {
                    case 0: //Build
                    {
                        if(viewedMap[Y][X+1] == ' ')
                        {
                            tp(X+1, Y);
                            setColor(3, 11);
                            printf("&");
                            setColor(0, 15);
                            viewedMap[Y][X+1] = '&';
                        }
                    }
                    break;
                    case 1: //shot
                    {
                        if(isMissile == false)missileDir = 2;
                        shot();
                    }
                    break;
                    case 2: //bomb
                    {
                        if(isBomb == false) bombDir = 2;
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

class computer //ai
{
private:
    bool isMissile = false;
    char clear = ' ';

    char missileSymbol = '-';
    short xStartM = 0;
    short yStartM = 0;
    void destroyMissile(short& xM, short& yM)
    {
        isMissile = false; //If missile is near console walls, it's disabled;
        tp(xM, yM); printf(" "); //Printf " " instead of missile char
    }
    short dir = 0; //temporary direction
public:
    char symbol = 'C';
    bool spawned = false;
    short xM = 0;
    short yM = 0;
    /*<bomb>*/
    short xB = 0;
    short yB = 0;
    char bombSymbol = 'X';
    bool isBomb = false;
    /*</bomb>*/

    bool isNewSecond = false;
    short color = 15;
    short X = 1, Y = 2;

    short cord = 77;

    /*<directions> //I've added 2 for buildings mechanics :p*/
    bool dirUp = false;
    bool dirDown = false;
	bool dirLeft = false;
    bool dirRight = true;
    /*<directions>*/
    
    string name;

    void spawn(short& X, short& Y); //spawn AI
    void hide(); // hide/kill AI;

    void go(short n); //move AI

    void shot();
    int isShot();

    void putBomb();
    void runBomb();

    int check(short pos, char ch);
    short rand();
};

//https://cdn.discordapp.com/attachments/619506379274715147/619506611383173130/Screen_Shot_09-06-19_at_02.17_PM.PNG
//:: https://www.p-programowanie.pl/cpp/klasy-c/

void computer :: spawn(short& X, short& Y)
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
void computer :: hide() // spawn/hide
{
    if(spawned) spawned = false;
    tp(X, Y); cout<<clear;
}

void computer :: go(short n) 
{
    setColor(0, color);
    if(spawned)
    {
        tp(X, Y); cout<<clear;

        switch (n)
        {
        case 72://up
        case 73:
        case 1:
            {
                if(Y > 2 && viewedMap[Y-1][X] != '#' && viewedMap[Y-1][X] != '&')
                    if(dirUp) Y--;
                dirUp = true;
                dirDown = false;
                dirLeft = false;
                dirRight = false;
            }
        break;
        case 80://down
        case 79:
        case 2:
            {
                if(Y < 23 && viewedMap[Y+1][X] != '#' && viewedMap[Y+1][X] != '&')
                    if(dirDown) Y++;
                dirUp = false;
                dirDown = true;
                dirLeft = false;
                dirRight = false;
            }
        break;
        case 75://left
        case 76:
        case 66:
        case 67:
        case 3:
            {
                if(X > 1 && viewedMap[Y][X-1] != '#' && viewedMap[Y][X-1] != '&')
                    if(dirLeft) X--;
                dirUp = false;
                dirDown = false;
                dirLeft = true;
                dirRight = false;
            }
        break;
        case 77://right
        case 78:
        case 68:
        case 69:
        case 4:
            {
                if(X < 78 && viewedMap[Y][X+1] != '#' && viewedMap[Y][X+1] != '&')
                    if(dirRight) X++;
                dirUp = false;
                dirDown = false;
                dirLeft = false;
                dirRight = true;
            }
        break;
        case 61: // 4/20 20% for shot
        case 62:
        case 63:
        case 64:
            shot();
            break;
        //case 70: bomb
        case 65: //0 off
            {
                if(dirUp && viewedMap[Y-1][X] == ' ') //Builds block for direction Up
                {
                    tp(X, Y-1);
                    setColor(3, 11);
                    printf("&");
                    viewedMap[Y-1][X] = '&';
                    setColor(0, 15);
                }else
                if(dirDown && viewedMap[Y+1][X] == ' ')
                {
                    tp(X, Y+1);
                    setColor(3, 11);
                    printf("&");
                    viewedMap[Y+1][X] = '&';
                    setColor(0, 15);
                }else
                if(dirLeft && viewedMap[Y][X-1] == ' ')
                {
                    tp(X-1, Y);
                    setColor(3, 11);
                    printf("&");
                    viewedMap[Y][X-1] = '&';
                    setColor(0, 15);
                }else
                if(dirRight && viewedMap[Y][X+1] == ' ')
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

void computer :: shot()
{
    setColor(0, color);//Sets color of missile.

    if(!isMissile && spawned)
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
            missileSymbol = '|';
            xM = X;
            yM = Y-1;
        }
        else if(dirDown)
        {
            dir = 2;
            missileSymbol = '|';
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

int computer :: isShot()
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
                if(xM - xStartM < 10) //Destroyes itself if it reaches 10 blocks
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
                if(xStartM - xM < 10)
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
                if(yStartM - yM < 10)
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
                if(yM - yStartM < 10)
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
    } else return 0;
    return 1;
}

void computer :: putBomb()
{
    if(!isBomb)
    {
        xB = X+1;
        yB = Y;
        tp(xB, yB); cout<<bombSymbol;
        isBomb = true;
    }
}
void computer :: runBomb()
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

int computer :: check(short pos, char ch)
{
    // 7 8 9
    // 4 5 6
    // 1 2 3
    switch (pos)
    {
    case 7: if(viewedMap[Y-1][X-1] == ch) return 1; break;
    case 8: if(viewedMap[Y-1][X] == ch) return 1; break;
    case 9: if(viewedMap[Y-1][X+1] == ch) return 1; break;
    case 4: if(viewedMap[Y][X-1] == ch) return 1; break;
    case 5: if(viewedMap[Y][X] == ch) return 1; break;
    case 6: if(viewedMap[Y][X+1] == ch) return 1; break;
    case 1: if(viewedMap[Y+1][X-1] == ch) return 1; break;
    case 2: if(viewedMap[Y+1][X] == ch) return 1; break;
    case 3: if(viewedMap[Y+1][X+1] == ch) return 1; break;
    
    default:
        break;
    }
    return 0;
}

short computer :: rand()
{
    if(cord != 2 && X <= cord)
    {
        if(check(6, '#') && check(8, '#'))
        {
            cord = 2;
            if(check(2, '#'))
                return 3;
            else
            {
                int temp[2] = {2, 3};
                return temp[random(0, 1)];
            }
        } 
        else if(check(6, '#') && check(2, '#'))
        {
            cord = 2;
            int temp[2] = {1, 3};
            return temp[random(0, 1)];
        }
        else if(check(8, '#') && check(2, '#'))
        {
            int temp[2] = {4, 64}; //right or shot
            return temp[random(0, 1)];
        }
        else
        {
            int temp[20] = {
                61, 62, 63, 64, 65, 68, 69, 70, //66,67
                71, 72, 73, 74, 77, 78, 79, 80 //75,76
            };
            return temp[random(0, 19)];
        }
    }
    else
    {
        cord = 2;
    }

    //left
    if(cord != 77 && X >= cord)
    {
        if(check(4, '#') && check(8, '#'))
        {
            cord = 77;
            if(check(2, '#'))
                return 4;
            else
            {
                int temp[2] = {2, 4};
                return temp[random(0, 1)];
            }
        } 
        else if(check(4, '#') && check(2, '#'))
        {
            cord = 77;
            int temp[2] = {1, 4};
            return temp[random(0, 1)];
        }
        else if(check(8, '#') && check(2, '#'))
        {
            int temp[2] = {3, 64}; //left or shot
            return temp[random(0, 1)];
        }
        else
        {
            int temp[20] = {
                61, 62, 63, 64, 65, 66, 67, 70, //68, 69
                71, 72, 73, 74, 75, 76, 79, 80 //77, 78
            };
            return temp[random(0, 19)];
        }
    }
    else
    {
        cord = 77;
    }

    return 0;
}

class menu
{
private:

public:
    string levelName = "EASY";
    short choose = 1;
	void show()
	{
		tp(0, 0);
		setColor(0, 7);
		cout<<"START GAME"<<endl;
		cout<<"SELECT LEVEL"<<endl;
		cout<<"QUIT"<<endl;
		cout<<"\nW, S and ENTER"<<endl;
		switch (choose)
		{
		case 1:
			tp(0, 0);
			setColor(0, 15);
			cout<<" START GAME"<<endl;
			break;
		case 2:
			tp(0, 1);
			setColor(0, 15);
			cout<<" SELECT LEVEL "; setColor(0, 7); cout<<levelName<<endl;
			break;
		case 3:
			tp(0, 2);
			setColor(0, 15);
			cout<<" QUIT"<<endl;
			break;
			
		default:
			break;
		}
	}
	void showLevels()
	{
        clear();
		tp(0, 0);
		setColor(0, 7);
		cout<<"EASY "<<endl;
		cout<<"MEDIUM "<<endl;
		cout<<"HARD "<<endl;
		cout<<"VERY HARD "<<endl;
		switch (choose)
		{
		case 1:
			tp(0, 0);
			setColor(0, 15);
			cout<<" EASY"<<endl;
			break;
		case 2:
			tp(0, 1);
			setColor(0, 15);
			cout<<" MEDIUM"<<endl;
			break;
		case 3:
			tp(0, 2);
			setColor(0, 15);
			cout<<" HARD"<<endl;
			break;
		case 4:
			tp(0, 3);
			setColor(0, 15);
			cout<<" VERY HARD"<<endl;
			break;
			
		default:
			break;
		}
	}
	void changeOption(char c, short n)
	{
		if(c == 'w')
		{
			if(choose == 1) choose = n;
			else choose--;
		}
		else if(c == 's')
		{
			if(choose == n) choose = 1;
			else choose++;
		}
	}
}menu;