#include <windows.h>
#include <conio.h>
#include "mouser.hpp"

/*<voids>*/
void isRunning(); //Says App what to do if user is running this application.
void isClicked(); //Says App what to do if user Clicks
void isDoubleClicked(); //Says App what to do if user DClicks
void isMoving(); //Says App What to do if mouse moves
void menuBar(); //Displays menu
/*</voids>*/

int main()
{
    hideCursor(); //Hides cursor from user vision (doesn't work if user resizes console);
    clear();
    mouse(isRunning, isClicked, isDoubleClicked, isMoving); //Mouse function, with 4 subfunctions
    return 0; //it "quits app", however it doesn't :shrug:
}

void isRunning()
{
    menuBar();
}

void isClicked()
{
    cout<<"ic;";
}

void isDoubleClicked()
{
    cout<<"idc;";
}

void isMoving()
{
    cout<<"im;";
}

void menuBar()
{
    tp(0, 0);

}