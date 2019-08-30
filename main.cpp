#include <windows.h>
#include <conio.h>
#include <ctime>
#include "mouser.hpp"

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
    wersjon.name = "Wersjon";
    wersjon.symbol = 'W';
    darxe.name = "DarXe";
    darxe.symbol = 'D';
    hideCursor(); //Hides cursor from user vision (doesn't work if user resizes console);
    //clear();
    while(true)
    {
        if(mouse(isRunning, isClicked, isDoubleClicked, isMoving)) //Mouse function, with 4 subfunctions
        {
            consoleMode();
        }
        else break;
    }

    return 0; //it should "quit" app, however it doesn't.
}

void isRunning()
{
    menuBar();
}

void isClicked()
{
    //cout<<"ic;";
}

void isDoubleClicked()
{
    //cout<<"idc;";
}

void isMoving()
{
    cout<<"moving";
}

void menuBar()
{
    clock_t timer = clock();
    setColor(3, 0);
    tp(0, 0);
    cout<<"                              MENU_BAR by Wersjon                               "<<endl;
    cout<<"                              consoleMODE - 5                                   "<<endl;
    //timer
    tp(35,2);
    if(timer/60000<10) cout<<"0"; cout<<timer/60000<<":";
    if(timer/1000%60<10) cout<<"0"; cout<<timer/1000%60<<":";
    cout<<timer%1000<<endl;

    setColor(0, 15);
    wersjon.sayHello();
    darxe.sayHello();
    tp(0, 2);
}

int consoleMode()
{
    clear(); //WERSJONEK
    while(true)
    {
        if(kbhit())
        {
            char ch = getch();
            switch (ch)
            {
            case 27:
                return 0;
                break;
            
            default:
                break;
            }
        }
        tp(0,0);
        cout<<"1TEST\n";
        cout<<"2TEST\n";
        cout<<"3TEST\n";
        cout<<"ESC EXIT\n";
        Sleep(10);
    }
    return 0;
}