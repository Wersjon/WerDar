#include <windows.h>
#include <conio.h>
#include "mouser.hpp"

/*<voids>*/
void isRunning(); //Says App what to do if user is running this application.
void isClicked(); //Says App what to do if user Clicks
void isDoubleClicked(); //Says App what to do if user DClicks
void isMoving(); //Says App What to do if mouse moves
/*</voids>*/

int main()
{
    hideCursor(); //Hides cursor from user vision (doesn't work if user resizes console);
    mouse(isRunning, isClicked, isDoubleClicked, isMoving); //Mouse function, with 4 subfunctions
    return 0; //it "quits app", however it doesn't :shrug:
}

void isRunning()
{

}

void isClicked()
{

}

void isDoubleClicked()
{

}

void isMoving()
{

}