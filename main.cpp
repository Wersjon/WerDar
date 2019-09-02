#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>

#include "classes.hpp" //including file classes.hpp that includes mouser.hpp

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
    float timePassed; //Time that have passed.
    int hours, minutes, seconds, holder;
    clock_t timePassing; //timePassing is double Value.

    character player;
    character comp;
    
    player.playercolor = 14;
    comp.playercolor = 11;
    
    player.spawn(3, 3);
    comp.spawn(4, 4);

    system("mode con:cols=80 lines=25"); //Sets console mode to 80x25
    hideCursor(); //Hides cursor from player view.
    
    mapReader(); //Reads Map from file
    menuBar(); //Displays MenuBar
    
    while(true)
    {
        timePassing = clock(); //Starts counting time.
        timePassed = (double)timePassing/1000; //Gets what time is it.
        holder = seconds; //not used for now
        seconds = timePassed; //how many seconds have been passed since program started
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

        Sleep(25); tp(12, 0); setColor(11, 0); //!important Sleep OZNACZA JAK SZYBKO DZIEJE SIĘ AKCJA

        if(hours<10) printf("0%i", hours); //displays how many hours you are playing with or without 0 before.
        else printf("%i", hours); 
        tp(15, 0);

        if(minutes<10) printf("0%i", minutes);
        else printf("%i", minutes);
        tp(18,0);

        if(seconds<10)printf("0%i", seconds);
        else printf("%i", seconds);
        setColor(0, 15);

        player.isShot(); //If player shot, missle is launched.
        comp.isShot();
        if(kbhit())
        {
            ch = getch();

            switch (ch)
            {
            case 'p':
            case 'P':
                player.shot();
            break;
            case 'y':
            case 'Y':
                setColor(4, 15);
                clear();
                menuBar();
            break;
            case 13: //Entere
                comp.shot();
            break;
            case 224: //arrows
                ch = getch();
                comp.go(ch);
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