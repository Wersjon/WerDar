#include <windows.h>
#include <conio.h>
#include <ctime>
#include "classes.hpp"

/*<voids>*/
void menuBar(); //Displays menu
/*</voids>*/

int main()
{
    unsigned char ch;
    /*while(true)
    {
        int i = getch();
        cout<<i; //character id
    }*/
    float timePassed;
    int hours, minutes, seconds, holder;
    clock_t timePassing; //Double

    character wersjon;
    character darxe;

    wersjon.spawn(2, 2);
    wersjon.symbol = 'W';
    darxe.spawn(4, 4);
    darxe.symbol = 'D';

    system("mode con:cols=80 lines=25");
    hideCursor();
    
    menuBar();
    while(true)
    {
        timePassing = clock();
        timePassed = (double)timePassing/1000;
        holder = seconds;
        seconds = timePassed;
        if(holder != seconds)
        {
            wersjon.isNewSecond = true;
            darxe.isNewSecond = true;
        }
        minutes = seconds/60;
        hours = minutes/60;
        seconds %= 60;
        minutes %= 60;
        hours %= 24;
        Sleep(50);tp(12,0);setColor(11, 0);
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
        wersjon.isShot();
        darxe.isShot();
        if(kbhit())
        {
            ch = getch();

            switch (ch)
            {
            case 'p':
            case 'P':
                wersjon.shot();
                break;
            case 13:
                darxe.shot();
                break;
            case 224: //arrows
                ch = getch();
                darxe.go(ch);
                break;
            
            default:
                {   
                    wersjon.go(ch);
                }
                break;
            }
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