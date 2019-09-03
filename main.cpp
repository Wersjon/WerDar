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
    srand(time(NULL));
    unsigned char ch;
    /*int i;
    while(i = getch())
    {
        cout<<i<<endl;
    }*/
    float timePassed; //Time that have passed.
    int hours, minutes, seconds, holder;
    clock_t timePassing; //timePassing is double Value.
    short seconds3 = 0;
    character player;
    character comp;
    computer AI;
    
    player.playercolor = 14;
    comp.playercolor = 11;
    
    system("mode con:cols=80 lines=25"); //Sets console mode to 80x25
    hideCursor(); //Hides cursor from player view.
    
    mapReader(); //Reads Map from file
    menuBar(); //Displays MenuBar

    player.spawn(3, 3);
    comp.spawn(4, 4);
    AI.spawn(1, 2);
    
    while(true)
    {
        timePassing = clock(); //Starts counting time.
        timePassed = (double)timePassing/1000; //Gets what time is it.
        
        holder = seconds%60;
        seconds = timePassed; //how many seconds have been passed since program started
        
        if(seconds3 == 0 && comp.isBomb == true)
        {
            tp(comp.xB, comp.yB); printf("3");
        }
        else if(seconds3 == 1 && comp.isBomb == true)
        {
            tp(comp.xB, comp.yB); printf("2");
        }
        else if(seconds3 == 2 && comp.isBomb == true)
        {
            tp(comp.xB, comp.yB); printf("1");
        }
        if(comp.isBomb == true && comp.isNewSecond == true)seconds3++;
        if(seconds3 == 3)
        {
            seconds3 = 0;
            comp.runBomb();
        }

        minutes = seconds/60; //Sets how many minutes are you playing, without modulo 60
        hours = minutes/60; 
        seconds %= 60; //Sets how many seconds are you playing
        minutes %= 60;
        hours %= 24;

        if(holder != seconds)
        {
            player.isNewSecond = true;
            comp.isNewSecond = true;
        }
        else
        {
            player.isNewSecond = false;
            comp.isNewSecond = false;
        }

        Sleep(25); tp(11, 0); setColor(11, 0); //!important Sleep OZNACZA JAK SZYBKO DZIEJE SIĘ AKCJA

        if(hours<10) printf("0%i", hours); //displays how many hours you are playing with or without 0 before.
        else printf("%i", hours); 
        tp(14, 0);

        if(minutes<10) printf("0%i", minutes);
        else printf("%i", minutes);
        tp(17,0);

        if(seconds<10)printf("0%i", seconds);
        else printf("%i", seconds);
        setColor(0, 15);

        player.isShot(); //If player shot, missle is launched.
        comp.isShot();
        AI.isShot();

        int n = random(0,5);
        switch (n)
        {
        case 4:
            AI.shot();
            break;
        case 5:
            AI.putBomb();
            AI.runBomb();
            break;
        
        default:
            AI.go(n);
            break;
        }
        
        
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
                {
                    //Nothing important
                    setColor(4, 15);
                    clear();
                    menuBar();
                }
                break;
            case 13: //Entere
                comp.shot();
                break;
            case 'V':
            case 'v':
                comp.putBomb();
            break;
            case 224: //arrows
                {
                    ch = getch();
                    switch (ch)
                    {
                    //case 82: //Insert button
                    /*case 71: //Home button
                        comp.runBomb();
                        break;
                    */
                    default:
                        comp.go(ch);
                        break;
                    }
                }
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
    printf("TimePassed:HH:MM:SS                                                             ");
    setColor(0, 15);
}