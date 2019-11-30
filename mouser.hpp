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

int whatColor(char x)
{
    if(x == '1')return 1;
    else if(x == '2')return 2;
    else if(x == '3')return 3;
    else if(x == '4')return 4;
    else if(x == '5')return 5;
    else if(x == '6')return 6;
    else if(x == '7')return 7;
    else if(x == '8')return 8;
    else if(x == '9')return 9;
    else if(x == 'A')return 10;
    else if(x == 'B')return 11;
    else if(x == 'C')return 12;
    else if(x == 'D')return 13;
    else if(x == 'E')return 14;
    else if(x == 'F')return 15;
    else return 0;
}

void load(string filename)
{
    /*Wer-Dar Paint v-1.4*/
    char area[80][25], area2[80][25], chars[80][25];
    fstream openfile;
    string holder;
    int i1=0, i2=0;

    openfile.open("images/" + filename + ".wdi", ios::in);
    if(openfile.good() == false)
    {
        cout << "error 404";
        openfile.close();
        return;
    }
    openfile.close();
    openfile.open("images/" + filename + ".wdi", ios::in);
    while(getline(openfile, holder))
    {
        if(i1 < 26 && i1>0)
        {
            while(i2<80)
            {
                area[i2][i1-1] = holder[i2];
                i2++;
            }
        }
        if(i1 > 27 && i1 < 53)
        {
            while(i2<80)
            {
                area2[i2][i1-28] = holder[i2];
                i2++;
            }
        }
        if(i1 > 54 && i1 < 80)
        {
            while(i2<80)
            {
                chars[i2][i1-55] = holder[i2];
                i2++;
            }
        }
    i2=0;
    i1++;
    }
    i1=0; i2=0;
    while(i1 < 25)
    {
        tp(0, i1);
        while(i2 < 80)
        {
            tp(i2, i1);
            setColor(whatColor(area[i2][i1]), whatColor(area2[i2][i1]));
            if(area[i2][i1]!='#') printf("%c", chars[i2][i1]);
            i2++;
        }
        i1++; i2 = 0;
    }
    openfile.close();
}

/*void load(string filename)
{
    //Wer-Dar Paint v-1.2

    char area[80][25];

    fstream openfile;
    string holder;
    int i1=0, i2=0;

    openfile.open("images/" + filename + ".wdi", ios::in);
    if(openfile.good() == false)
    {
        cout << "error 404";
        openfile.close();
        return;
    }
    openfile.close();
    openfile.open("images/" + filename + ".wdi", ios::in);
    while(getline(openfile, holder))
    {
        if(i1>0)
        {
            while(i2<80)
            {
                area[i2][i1-1] = holder[i2];
                if(area[i2][i1-1] != 177 && area[i2][i1-1] != '#')
                {
                    tp(i2, i1-1);
                    setColor(whatColor(area[i2][i1-1]), whatColor(area[i2][i1-1]));
                    printf("%c", area[i2][i1-1]);
                }
                i2++;
            }
        }
        i2=0;
        i1++;
    }
    tp(0, 0);
    openfile.close();
}*/