#include <windows.h>
#include <conio.h>
#include <ctime>
#include "classes.hpp"

/*<voids>*/
void isRunning(); //Says App what to do if user is running this application.
void isClicked(); //Says App what to do if user Clicks
void isDoubleClicked(); //Says App what to do if user DClicks
void isMoving(); //Says App What to do if mouse moves
void menuBar(); //Displays menu
int consoleMode();
/*</voids>*/

int main()
{
    char ch;
    float timePassed;
    int hours, minutes, seconds;
    clock_t timePassing; //Double

    character wersjon;

    wersjon.spawn(2, 2);
    wersjon.symbol = 'W';

    system("mode con:cols=80 lines=25");
    hideCursor();
    
    menuBar();
    while(true)
    {
        timePassing = clock();
        timePassed = (double)timePassing/1000;
        seconds = timePassed;
        minutes = seconds/60;
        hours = minutes/60;
        seconds %= 60;
        minutes %= 60;
        hours %= 24;
        Sleep(100);tp(12,0);setColor(11, 0);
        if(hours<10)printf("0%i", hours);
        else printf("%i", hours);
        tp(15,0);
        if(minutes<10)printf("0%i", minutes);
        else printf("%i", minutes);
        tp(18,0);
        if(seconds<10)printf("0%i", seconds);
        else printf("%i", seconds);
        setColor(0, 15);
        //printf("%f seconds passed\n", timePassed);
        if(kbhit())
        {
            ch = getch();
            wersjon.go(ch);
        }
    }
}

void menuBar()
{
    setColor(3, 0);
    tp(0, 0);
    printf("TimePassed: HH:MM:SS                                                            ");
    setColor(0, 15);
}