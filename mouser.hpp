//#include <iostream>
//#include <windows.h>
//#include <conio.h>
//#include <cstdio>

using namespace std;

HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

char viewedMap[25][80]; //Map.

void hideCursor() //Hides Cursor from user: (doesn't work if user resized window[?])
{
    CONSOLE_CURSOR_INFO CURSOR;
    CURSOR.dwSize = 1;
    CURSOR.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &CURSOR);
}

void tp(int x, int y) //Teleports coordinates:
{
    COORD c; //Creates Coordinates variable named c.
    c.X = x; //Sets X coordinate.
    c.Y = y; //Sets Y coordinate.
    SetConsoleCursorPosition(hOut, c); //Sets Cursor Position to c.X, c.Y.
}

void setColor(int bg, int c) //sets Console colors:
{
    SetConsoleTextAttribute(hOut, bg*16 + c);
}

void clear() //Clears 80x25 Screen:
{
    tp(0, 0);
    printf("%2000i \n"); //Prints 2000 chars. :D
    tp(79, 22); printf(" ");
}

void mapReader()
{
    fstream map;
    string fstreamholder; //holds line for getline
    map.open("map.txt", ios::in); //Opens map.txt with input type.
    if(map.good() == false)
    {
        map.close();
        map.open("map.txt", ios::out); //changes input type to output, and draws how it looks.
        map << "                                                                                " << endl;
        map << "################################################################################" << endl;
        int i = 2;
        while(i < 24)
        {
            map << "#                                                                              #" << endl;
            i++;
        }
        map << "################################################################################";
    }
    map.close();
    map.open("map.txt", ios::in);
    //Get's values from map.txt and saves it into viewedMap.
    int whatline = 1;
    int i;
    while(getline(map, fstreamholder))
    {
        i = 0;
        while(i<80)
        {
            viewedMap[whatline][i] = fstreamholder[i];
            i++;
        }
        whatline++;
    }
    int i1 = 1, i2 = 0;
    //draws map
    while(i1 < 25)
    {
        tp(0, i1+1);
        while(i2 < 80)
        {   
            if(viewedMap[i1][i2] == '#') setColor(1, 9);
            else if(viewedMap[i1][i2] == '&') setColor(3, 11);
            else setColor(0, 15);
            printf("%c", viewedMap[i1][i2]);
            i2++;
        }
        i2 = 0;
        i1++;
    }
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

void displayMenu()
{
    setColor(8, 0);
    tp(30, 9);
    printf("                      ");
    tp(30, 11);
    printf("  ");
    tp(50, 11);
    printf("  ");
    tp(18, 13);
    printf("              ");
    tp(50, 13);
    printf("                ");
    tp(30, 15);
    printf("  ");
    tp(50, 15);
    printf("  ");

    setColor(7, 0);
    tp(30, 10);
    printf("  ");
    tp(50, 10);
    printf("  ");
    tp(16, 12);
    printf("                ");
    tp(50, 12);
    printf("              ");
    tp(30, 14);
    printf("  ");
    tp(50, 14);
    printf("  ");
    tp(30, 16);
    printf("                      ");

    setColor(0, 0);
    tp(32, 10);
    printf("                  ");
    tp(32, 11);
    printf("  ");
    tp(48, 11);
    printf("  ");
    tp(32, 12);
    printf("  ");
    tp(48, 12);
    printf("  ");
    tp(32, 13);
    printf("  ");
    tp(48, 13);
    printf("  ");
    tp(32, 14);
    printf("  ");
    tp(48, 14);
    printf("  ");
    tp(32, 15);
    printf("                  ");

    setColor(7, 0);
    tp(34, 13);
    printf("Test          ");

    setColor(8, 0);
    tp(34, 12);
    printf("Options       ");
    tp(34, 14);
    printf("Quit/Exit     ");
}