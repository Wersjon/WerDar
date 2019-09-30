#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>

#include "classes.hpp" //including file classes.hpp that includes mouser.hpp

/*<voids>*/
void menuBar(); //Displays menu
void displayLogo();
/*</voids>*/

int main()
{
    SetConsoleTitleA("Wer-Dar");
    system("mode con:cols=80 lines=25"); //Sets console mode to 80x25
    hideCursor(); //Hides cursor from player view.
    displayLogo();
    for (size_t i = 0; i < 10; i++)
    {
        Sleep(500);
        if(kbhit()) { getch(); break; }
    }
    
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
    const short compSize = 15;
    computer AI; short n = 0, nComp[compSize];
    computer comp[compSize];
    short killCounter = 0;
    short _FPS = 30;
    const short FPS = 1000/_FPS;
    
    player.playercolor = 14;
    mapReader(); //Reads Map from file

    player.spawn(48, 15);

    AI.spawn(AI.X, AI.Y); AI.symbol = 'A';
    for (size_t i = 0; i < compSize; i++)
    {
        comp[i].spawn(comp[i].X, comp[i].Y);
    }

    menuBar(); //Displays MenuBar
    
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

        Sleep(FPS); setColor(11, 0); //!important Sleep OZNACZA JAK SZYBKO DZIEJE SIĘ AKCJA

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
        switch (player.mode)
        {
            case 0: printf("&"); break;
            case 1: printf("-"); break;
            case 2: printf("X"); break;
        }
        setColor(11, 0);
        tp(60, 0);
        printf("Kills: ");printf("%i",killCounter);

        setColor(0, 15);

        if(player.isShot()) //If player shot, missle is launched.
        {
            for (size_t i = 0; i < compSize; i++)
            {
                if(comp[i].spawned && player.xM == comp[i].X && player.yM == comp[i].Y)
                {
                    comp[i].hide();
                    killCounter++;
                    player.isMissile = false;
                }
            }
            
            if(player.xM == AI.X && player.yM == AI.Y && AI.spawned) //if missile is launched - check
            {
                AI.hide(); //kill
                tp(25, 0); printf("AI [*]");
                tp(32, 0);
                if(hours<10) printf("0%i", hours);
                else printf("%i", hours); 
                tp(35, 0);
                if(minutes<10) printf("0%i", minutes);
                else printf("%i", minutes);
                tp(38, 0);
                if(seconds<10)printf("0%i", seconds);
                else printf("%i", seconds);
            }
        }
            
        player.runBomb();

        if(AI.isShot())
        if(player.spawned && AI.xM == player.X && AI.yM == player.Y)
        {
            player.hide(); //kill
            tp(35, 0); printf("Player [*]");
            tp(46, 0);
            if(hours<10) printf("0%i", hours);
            else printf("%i", hours); 
            tp(49, 0);
            if(minutes<10) printf("0%i", minutes);
            else printf("%i", minutes);
            tp(52, 0);
            if(seconds<10)printf("0%i", seconds);
            else printf("%i", seconds);
        }
        for (size_t i = 0; i < compSize; i++)
        {
            if(comp[i].isShot())
            {
                if(player.spawned && comp[i].xM == player.X && comp[i].yM == player.Y)
                {
                    player.hide(); //kill
                    tp(35, 0); printf("Player [*]");
                    tp(46, 0);
                    if(hours<10) printf("0%i", hours);
                    else printf("%i", hours); 
                    tp(49, 0);
                    if(minutes<10) printf("0%i", minutes);
                    else printf("%i", minutes);
                    tp(52, 0);
                    if(seconds<10)printf("0%i", seconds);
                    else printf("%i", seconds);
                }
            }
        }
        
        
        AI.go(AI.rand()); //(4*2)+(2*2)/20 = 60% chance for move up/left/down/right % 10/20/10/20

        for (size_t i = 0; i < compSize; i++)
        {
            nComp[i] = random(61,80);
            switch (nComp[i])
            {
            case 61:
            case 62:
            case 63:
            case 64:
                comp[i].shot();
                break;
            default:
                comp[i].go(nComp[i]);
                break;
            }
        }
        
        //*/
        
        if(kbhit())
        {
            ch = getch();

            switch (ch)
            {
                case 'y':
                case 'Y':
                {
                    //Nothing important
                    displayLogo();
                    menuBar();
                }
                break;
                case 13: AI.shot(); break;
                case 224: //tests AI
                {
                    n = getch();
                    AI.go(n);
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

void displayLogo()
{   
    tp(0, 0); setColor(0, 0); clear();
    tp(16, 2);
    setColor(9, 9); printf("    ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("          ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("          ");
    setColor(0, 0); printf("                                    ");
    
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("        "); 
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("    ");
    setColor(9, 9); printf("    "); 

    tp(16, 4);
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(0, 0); printf("      ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  ");

    tp(18, 5);
    setColor(9, 9); printf("    "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("    ");
    setColor(9, 9); printf("          "); 
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    "); 
    setColor(1, 1); printf("  ");

    tp(18, 6);
    setColor(9, 9); printf("                ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("        ");
    setColor(9, 9); printf("          ");
    setColor(1, 1); printf("    ");

    tp(18, 7);
    setColor(9, 9); printf("      ");
    setColor(1, 1); printf("    ");
    setColor(9, 9); printf("      ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("      ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");

    tp(20, 8); 
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("      ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");

    tp(20, 9);
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("          ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");

    tp(22, 10);
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("    ");
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("      ");
    setColor(1, 1); printf("          ");
    setColor(0, 0); printf("  ");
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("      ");
    setColor(1, 1); printf("    ");

    tp(16, 12);
    setColor(9, 9); printf("                                                ");

    tp(18, 13);
    setColor(1, 1); printf("                                                ");

    tp(16, 15);
    setColor(9, 9); printf("          ");
    setColor(0, 0); printf("          ");
    setColor(9, 9); printf("      ");
    setColor(0, 0); printf("      ");
    setColor(9, 9); printf("          ");

    tp(16, 16);
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(0, 0); printf("        ");
    setColor(9, 9); printf("      ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("    ");
    setColor(9, 9); printf("    ");

    tp(16, 17);
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");

    tp(16, 18);
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");

    tp(16, 19);
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("          ");
    setColor(1, 1); printf("    ");

    tp(16, 20);
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("              ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    
    tp(16, 21);
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("      ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");

    tp(16, 22);
    setColor(9, 9); printf("          ");
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(9, 9); printf("    ");
    setColor(1, 1); printf("  ");
    setColor(0, 0); printf("    ");
    setColor(9, 9); printf("    ");

    tp(18, 23);
    setColor(1, 1); printf("          ");
    setColor(0, 0); printf("      ");
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("      ");
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("  ");
    setColor(1, 1); printf("    ");
    setColor(0, 0); printf("      ");
    setColor(1, 1); printf("    ");
}