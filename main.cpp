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
    computer AI;
    
    player.playercolor = 14;
    
    system("mode con:cols=80 lines=25"); //Sets console mode to 80x25
    hideCursor(); //Hides cursor from player view.
    
    mapReader(); //Reads Map from file
    menuBar(); //Displays MenuBar

    player.spawn(3, 3);
    AI.spawn(1, 2);
    
    while(true)
    {
        timePassing = clock(); //Starts counting time.
        timePassed = (double)timePassing/1000; //Gets what time is it.

        holder = seconds%60;
        seconds = timePassed; //how many seconds have been passed since program started

        /*if(seconds3 == 0 && AI.isBomb == true)
        {
            tp(AI.xB, AI.yB); 
            printf("3");
        }
        else if(seconds3 == 1 && (AI.isBomb == true))
        {
            tp(AI.xB, AI.yB); printf("2");
        }
        else if(seconds3 == 2 && (AI.isBomb == true))
        {
            tp(AI.xB, AI.yB); printf("1");
        }
        if(AI.isBomb == true && AI.isNewSecond == true)seconds3++;
        if(seconds3 == 3)
        {
            seconds3 = 0;
            AI.runBomb();
        }*/
        
        //please rewrite bomb system for AI

        minutes = seconds/60; //Sets how many minutes are you playing, without modulo 60
        hours = minutes/60; 
        seconds %= 60; //Sets how many seconds are you playing
        minutes %= 60;
        hours %= 24;

        if(holder != seconds)
        {
            player.isNewSecond = true;
            AI.isNewSecond = true;
        }
        else
        {
            player.isNewSecond = false;
            AI.isNewSecond = false;
        }

        Sleep(33); setColor(11, 0); //!important Sleep OZNACZA JAK SZYBKO DZIEJE SIĘ AKCJA

        tp(11, 0);
        if(hours<10) printf("0%i", hours); //displays how many hours you are playing with or without 0 before.
        else printf("%i", hours); 
        
        tp(14, 0);
        if(minutes<10) printf("0%i", minutes);
        else printf("%i", minutes);
        
        tp(17,0);
        if(seconds<10)printf("0%i", seconds);
        else printf("%i", seconds);

        tp(22, 0);
        if(player.mode == 0)printf("&");
        if(player.mode == 1)printf("-");
        if(player.mode == 2)printf("X");

        setColor(0, 15);

        player.isShot(); //If player shot, missle is launched.
        player.runBomb();
        AI.isShot();
        
        int n = random(61, 80); //20 random numbers
        switch (n)
        {
        case 61: // 2/20 10% for shot
        case 62:
            AI.shot();
            break;
        case 63: // 1/20 5% for bomb
            AI.putBomb();
            break;
        default:
            AI.go(n); //(4*2)/20 = 40% chance for move
            break;
        }
        
        
        if(kbhit())
        {
            ch = getch();

            switch (ch)
            {
                case 'y':
                case 'Y':
                {
                    //Nothing important
                    setColor(4, 15);
                    clear();
                    menuBar();
                }
                break;
                case 224: //tests AI
                {
                    ch = getch();
                    AI.go(ch);
                }
                break;

                default:  
                {
                    player.go(ch);
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
    printf("TimePassed:HH:MM:SS M:&                                                         ");
    tp(0, 1);
    setColor(0, 15);
}