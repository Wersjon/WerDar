#include <windows.h>
#include <conio.h>
#include "mouser.hpp"

int main()
{
    CONSOLE_CURSOR_INFO CURSOR;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &CURSOR);
    mouse();
    getch();
    return 0;
}