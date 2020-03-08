#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>

#include "classes.hpp" //including file classes.hpp that includes mouser.hpp

/*<voids>*/
void start();
void load();
void logoBar();
/*</voids>*/

int main()
{
    srand(time(NULL));
    SetConsoleTitleA("Wer-Dar");
    system("mode con:cols=80 lines=25"); //Sets console mode to 80x25
    hideCursor(); //Hides cursor from player view.
    short compSize = 4;

    unsigned char ch;

    float timePassed; //Time that have passed.
    int hours, minutes, seconds, holder;
    clock_t timePassing; //timePassing is double Value.
    clock_t time;
    short seconds3 = 0, cFPS = 0;
    character player;
    computer AI;
    computer comp[compSize];
    short killCounter = 0;
    short FPS = 60; short _FPS = 1000/FPS;
    bool info = false;
    short xStart = 1, xEnd = 78, yStart = 2, yEnd = 23;
    
    load("logo");
    menu.wait(5); //waiting for 5 seconds (with 500ms break)
    load("menu");

    start();

    player.playercolor = 14;
    mapReader(); //Reads Map from file

    player.spawn(48, 15);
    logoBar();

    //AI - random positions
    {
        short x,y;
        while(true)
        {
            x = random(1,78);
            y = random(2,23);
            if(viewedMap[y][x] == ' ')
                if(x < 37 || x > 58 || y < 15 || y > 18) break;
        }
        AI.spawn(x, y);
        for (size_t i = 0; i < compSize; i++)
        {
            while(true)
            {
                x = random(1,78);
                y = random(2,23);
                if(viewedMap[y][x] == ' ')
                    if(x < 37 || x > 58 || y < 15 || y > 18) break;
            }
            comp[i].spawn(x, y);
            if(i>1) Sleep(100);
        }
    }
    
    time = clock();
    while(true)
    {
        timePassing = clock() - time; //Starts counting time.
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
            setColor(11, 0);
            tp(71, 0);
            printf("FPS: ");  printf("%i ", cFPS);
            cFPS=0;
        }
        else
        {
            player.isNewSecond = false;
            AI.isNewSecond = false;
            cFPS++;
        }

        Sleep(_FPS); setColor(11, 0); //!important Sleep OZNACZA JAK SZYBKO DZIEJE SIĘ AKCJA

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
                killCounter++;
                setColor(0, 15); tp(23, 1);
                printf("You won! AI has been defeated. Return [ESC]");
                while(getch() != 27);
            }
        }
            
        player.runBomb();

        if(AI.isShot())
        if(player.spawned && AI.xM == player.X && AI.yM == player.Y)
        {
            player.hide(); //kill
            setColor(0, 15); tp(26, 1);
            printf("GAME OVER! Return [ESC]");
            while(getch() != 27);
        }
        for (size_t i = 0; i < compSize; i++)
        {
            if(comp[i].isShot())
            {
                if(player.spawned && comp[i].xM == player.X && comp[i].yM == player.Y)
                {
                    player.hide(); //kill
                    setColor(0, 15); tp(26, 1);
                    printf("GAME OVER! Return [ESC]");
                    while(getch() != 27);
                }
            }
        }
        
        
        AI.go(AI.rand()); //(4*2)+(2*2)/20 = 60% chance for move up/left/down/right % 10/20/10/20

        for (size_t i = 0; i < compSize; i++)
        {
            comp[i].go(comp[i].rand());
        }
        
        //*/
        
        if(kbhit())
        {
            ch = getch();
            if (ch == 27) break;
            switch (ch)
            {
                case 'y':
                case 'Y':
                {
                    //Nothing important
                    load("logo");
                    logoBar();
                }
                break;
                case 13: AI.shot(); break;
                //Change FPS + and -
                case 43: if(FPS>=890) FPS = 60; else if(FPS<60) _FPS = 1000/(FPS++); else _FPS = 1000/(FPS+=10); break;
                case 45: if(FPS>=70) _FPS = 1000/(FPS-=10); else if(FPS>1) _FPS = 1000/(FPS--); break;
                case 224: //tests AI
                {
                    int n = getch();
                    AI.go(n);
                    if(n == 82) //Insert - show/hide info
                    {
                        info = info ? 0 : 1;
                        tp(16, 22); cout<<"        ";
                        tp(16, 23); cout<<"        ";
                        break;
                    }
                    break;
                }
                default:  
                {
                    player.go(ch);
                    break;
                }
            }
        }
        if(info) //if 'info' is true then show informations
        {
            tp(16, 21); cout<<"P: "<<player.X<<","<<player.Y<<" ";
            tp(16, 22); cout<<"C: "<<AI.X<<","<<AI.Y<<" ";
            tp(16, 23); cout<<"D: ";
            if(AI.dirUp)    cout<<"Up   ";
            if(AI.dirDown)  cout<<"Down ";
            if(AI.dirLeft)  cout<<"Left ";
            if(AI.dirRight) cout<<"Right";
        }
    }//while
    return 0;
}

void logoBar()
{
    setColor(3, 0);
    tp(0, 0);
    printf("TimePassed:HH:MM:SS M:&                                                         ");
    tp(0, 1);
    setColor(0, 15);
}

void start()
{
    string options[4] = {"Start", "Options", "Test", "Quit"};
    unsigned char currentOption = 0; //0: start; etc.
    unsigned char everyfive = 5;
    bool animdone = false;
    char znak;

    tp(36, 11);setColor(11,0);
    cout << options[0];
    tp(36, 12);setColor(3,0);
    cout << options[1];
    tp(36, 13);setColor(11,0);
    cout << options[2];
    tp(36, 14);setColor(3,0);
    cout << options[3];

    while(true)
    {
        if(animdone && everyfive == 5)
        {
            if(currentOption%2 == 0)setColor(11, 4);
            if(currentOption%2 == 1)setColor(3, 4);
            tp(36, 11+currentOption);
            cout << "            ";
            tp(36, 11+currentOption);
            cout << "->" << options[currentOption];
            animdone = false;
            everyfive = 0;
        }
        else if(!animdone && everyfive == 5)
        {
            if(currentOption%2 == 0)setColor(11, 1);
            if(currentOption%2 == 1)setColor(3, 1);
            tp(36, 11+currentOption);
            cout << "            ";
            tp(36, 11+currentOption);
            cout << "> " << options[currentOption];
            animdone = true;
            everyfive = 0;
        }
        Sleep(50);
        everyfive++;
        if(kbhit())
        {
            znak = getch();
            switch(znak)
            {
                case 'W':
                case 'w':
                    if(currentOption>0)
                    {
                        if(currentOption%2 == 0)setColor(11,0);
                        if(currentOption%2 == 1)setColor(3,0);
                        tp(36, 11+currentOption);
                        cout << "            ";
                        tp(36, 11+currentOption);
                        cout << options[currentOption];
                        currentOption--;
                        everyfive = 5;
                    }
                break;

                case 'S':
                case 's':
                    if(currentOption<3)
                    {
                        if(currentOption%2 == 0)setColor(11,0);
                        if(currentOption%2 == 1)setColor(3,0);
                        tp(36, 11+currentOption);
                        cout << "            ";
                        tp(36, 11+currentOption);
                        cout << options[currentOption];
                        currentOption++;
                        everyfive = 5;
                    }
                break;
                case 13:
                    switch(currentOption)
                    {
                        case 0:
                            return;
                        break;
                        case 1: //seperate
                        case 2:
                            //    
                        break;
                        case 3:
                            exit(0);
                        break;
                    }
                break;
                default:
                break;
            }
        }
    }
}