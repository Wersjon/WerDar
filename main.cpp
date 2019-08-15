#include <windows.h>
#include <conio.h>
#include "mouser.hpp"

void isRunning();
void isClicked();
void isDoubleClicked();
void isMoving();

int main()
{
    hideCursor();
    mouse(isRunning, isClicked, isDoubleClicked, isMoving);
    getch();
    return 0;
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