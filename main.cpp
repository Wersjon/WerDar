#include <windows.h>
#include <conio.h>
#include <ctime>
#include "classes.hpp"

/*<voids>*/
void menuBar(); //Displays menu
void mapReader(); //Reads Map
/*</voids>*/
char viewedMap[80][24];

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

    character player;
    character darxe;

    player.spawn(2, 2);
    darxe.spawn(4, 4);

    system("mode con:cols=80 lines=25");
    hideCursor();
    
    menuBar();
    while(true)
    {
        timePassing = clock();
        timePassed = (double)timePassing/1000;
        holder = seconds;
        seconds = timePassed;
        /*if(holder != seconds)
        {
            player.isNewSecond = true;
            darxe.isNewSecond = true;
        }*/
        minutes = seconds/60; //Sets how many minutes are you playing, without modulo 60
        hours = minutes/60; 
        seconds %= 60; //Sets how many seconds are you playing
        minutes %= 60;
        hours %= 24;

        Sleep(25);tp(12,0);setColor(11, 0); //!important Sleep OZNACZA JAK SZYBKO DZIEJE SIĘ AKCJA

        //displays how many hours you are playing with or without 0 before.
        if(hours<10)printf("0%i", hours);
        else printf("%i", hours);
        tp(15,0);

        if(minutes<10)printf("0%i", minutes);
        else printf("%i", minutes);
        tp(18,0);

        if(seconds<10)printf("0%i", seconds);
        else printf("%i", seconds);
        setColor(0, 15);

        player.isShot();
        darxe.isShot();
        if(kbhit())
        {
            ch = getch();

            switch (ch)
            {
            case 'p':
            case 'P':
                player.shot();
            break;
            case 13:
                darxe.shot();
            break;
            case 224: //arrows
                ch = getch();
                darxe.go(ch);
            break;
        
            default:  
                player.go(ch);
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