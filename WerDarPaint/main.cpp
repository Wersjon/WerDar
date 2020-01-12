#include "mouser.hpp"

using namespace std;

/*

// Wer-Dar Paint v-1.5 by Jakub Sobacki
// Few things before you get started
// This app requires special treatment for cmd, it's written when app is opened (main function)

*/

/* Layers for painting */
char area[80][25], area2[80][25], chars[80][25];
short currentId;

/* Declaration for functions */
void keypressed(char input);
void clicked();
void doubleClicked();
void moved();
void menu();

int whatColor(char x);
char whatChar(short x);
void saveDisk();
void loadDisk();
void displayChar();
void draw();

/* 5 Declaration of 5 other global values */
short currentColor = 15, secondaryColor = 15, px, py; //Stores color of cursor
char currentChar = 177; //Holds current char

int main()
{
    /* Declaration of variables */
    int i = 0;
    char toolbar[34] =
    {
        '0', '0', '1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8', '9', '9', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', '#', '#'
    };
    char tools[4] = {(char)176, (char)177, (char)178, (char)220};

    SetConsoleOutputCP(852); //Setting CodePage to 852, to have all characters
    SetConsoleTitleA("Wer-Dar Paint"); //Setting title
    hideCursor(); //Hiding cursor

    loadfile("wdplogo"); //Loading wdplogo.wdi (read)
    while(i < 40) //If KeyBoardHIT, end while and start program (for 4 seconds).
    {
        if(kbhit()) 
        {
            getch();
            break;
        }
        Sleep(100);
        i++;
    }

    clear(); //Clears screen / system("cls") is broken, and slower.
    loadfile("load");

    /*informational text for user */
    tp(1, 1); setColor(0, 15); printf("Edit modes: Turn off Quick edit mode;"); //teleports cursor to 1, 1;  Sets color for text; and printfs the text
    setColor(12, 15); printf(" T");
    setColor(0, 15); printf("urn off insert mode; Turn rest on;");
    tp(1, 2); printf("Selecting Text: Everything off;");
    tp(1, 3); printf("Layout{");
    tp(1, 4); printf("- For buffer: Width: 80+; Height: 50+");setColor(12, 15); printf(";"); setColor(0, 15);
    tp(1, 5); printf("- For window: Width: 80+; Height: 26+");setColor(12, 15); printf(";"); setColor(0, 15);
    tp(1, 6); printf("- Turn off wrapping text on resize}");
    tp(1, 7); printf("Terminal(Windows 10 - experimental): ");
    setColor(12, 15); printf("Tu");
    setColor(0, 15); printf("rn off: Disable Scroll Forward option;");
    tp(1, 9); printf("Click any key to start drawing.");
    tp(1, 10); setColor(0, 12); printf("DON'T MOUSE OVER RIGHT BOTTOM CORNER");
    images.push_back(image());
    getch(); //awaits for input
    
    i = 2;
    while(i < 36)
    {
        tp(i, 25);
        setColor(whatColor(toolbar[i - 2]), whatColor(toolbar[i - 2]));
        if(toolbar[i-2] == '#') setColor(8, 7);
        printf("%c", toolbar[i - 2]);
        if(i <= 33)
        {
            tp(i + 37, 25);
            setColor(0, whatColor(toolbar[i - 2]));
            printf("%c", tools[2]);
        }
        i++;
    }
    tp(72, 25);
    setColor(0, 15);
    printf("%c%c%c%c", tools[0], tools[1], tools[2], tools[3]);
    setColor(1, 8); 
    tp(0, 25); printf("%c%c", tools[1], tools[1]);
    tp(36, 25); printf("%c", tools[2]);
    tp(38, 25); printf("%c", tools[2]);
    tp(71, 25); printf("%c", tools[2]);
    tp(76, 25); printf("%c%c%c%c", tools[2], tools[2], tools[2], tools[2]);
    /* while to display whole map area */
    tp(0, 0);
    int i2 = 0; i = 0;
    while(i < 25)
    {
        while(i2 < 80)
        {
            area[i2][i] = '#';
            area2[i2][i] = '#';
            chars[i2][i] = ' ';
            setColor(whatColor(area[i2][i]), whatColor(area[i2][i]));
            if(area[mx][my] == '#') setColor(8, 7);
            printf("%c", area[i2][i]);
            i2++;
        }
        i2 = 0;
        i++;
    }
    mouse(clicked, doubleClicked, moved, keypressed);
    return 0;
}

void keypressed(char input)
{
    switch(input)
    {
        case ' ':
            saveDisk();
            tp(0, 0); setColor(0, 15); printf("saved");
            Sleep(250);
        break;
    }
}

void clicked()
{
    char tools[4] = {(char)176, (char)177, (char)178, (char)220};
    if(my < 25 && mx < 80)
    {
        tp(mx, my);
        setColor(currentColor, secondaryColor);
        if(area[mx][my] == '#') setColor(8, 7);
        printf("%c", currentChar);
        area[mx][my] = whatChar(currentColor);
        area2[mx][my] = whatChar(secondaryColor);
        chars[mx][my] = currentChar;
    }
    else if(my == 25 && mx > 1 && mx < 36)
    {
        currentColor = (mx - 2) / 2;
        if((mx - 2) / 2 > (mx - 1) / 2) currentColor = (mx - 1) / 2;
    }
    else if(my == 25 && mx > 38 && mx < 71)
    {
        secondaryColor = (mx - 38) / 2;
        if((mx - 38) / 2 > (mx - 49) / 2) secondaryColor = (mx - 39) / 2;
    }
    else if(my == 25 && mx > 71 && mx < 76)
    {
        currentChar = tools[mx - 72];
        displayChar();
    }
    else if(my == 25 && mx < 2)
    {
        menu();
    }
}

void doubleClicked()
{
    doClick = true;
}

void moved()
{
    char toolbar[34] =
    {
        '0', '0', '1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8', '9', '9', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', '#', '#'
    };
    char tools[4] = {(char)176, (char)177, (char)178, (char)220};
    if(doClick) clicked();

    /*pYpX*/
    if(py < 25 && px < 80)
    {
        setColor(whatColor(area[px][py]), whatColor(area2[px][py]));
        if(area[px][py] == '#') setColor(8, 7);
        tp(px, py);
        if(area[px][py] == '#') printf("#");
        else printf("%c", chars[px][py]);
    }
    else if(py == 25 && px < 2)
    {
        tp(0, 25);
        setColor(1, 8);
        printf("%c%c", tools[1], tools[1]);
        px = mx;
        py = my;
        displayChar();
    }
    else if(py == 25 && px > 1 && px < 36)
    {
        setColor(whatColor(toolbar[px - 2]), whatColor(toolbar[px - 2]));
        if(toolbar[px - 2] == '#')setColor(8, 7);
        tp(px, 25);
        if(toolbar[px - 2] == '#') printf("#");
        else printf("%c", currentChar);
    }
    else if(py == 25 && px > 38 && px < 71)
    {
        setColor(0, whatColor(toolbar[px - 39]));
        tp(px, 25);
        printf("%c", tools[2]);   
    }
    else if(py == 25 && px > 71 && px < 76)
    {
        tp(px, py); setColor(0, 15);
        printf("%c", tools[px - 72]);
    }

    /*mYmX*/
    if(my < 25 && mx < 80)
    {
        setColor(currentColor, secondaryColor);
        tp(mx, my);
        printf("X");
    }
    else if(my == 25 && mx < 2)
    {
        tp(0, 25);
        setColor(9, 7);
        printf("%c%c", tools[1], tools[1]);
        displayChar();
    }
    else if(my == 25 && mx > 1 && mx < 36)
    {
        tp(mx, my);
        setColor(whatColor(toolbar[mx - 2]), currentColor);
        if(toolbar[mx-2] == '#')setColor(8, currentColor);
        printf("X");
        displayChar();
    }
    else if(my == 25 && mx > 38 && mx < 71)
    {
        tp(mx, my);
        setColor(12, whatColor(toolbar[mx - 39]));
        printf("%c", tools[2]);
        displayChar();
    }
    else if(my == 25 && mx > 71 && mx < 76)
    {
        tp(mx, my); setColor(12, 15);
        printf("%c", tools[mx - 72]);
        displayChar();
    }
    px = mx; py = my;
}

void menu()
{
    char wybor;
    short i1 = 0, i2 = 0, Id;
    string name;
    doClick = false;

    setColor(0, 15); clear(); tp(0, 0);
    printf("What would you like to do?\n1. Load disk.wdd\n2. Save as disk.wdd\n3. Load picture\n4. Save picture\n5. Save as picture\n6. Make new picture");
    
    wybor = getch();
    if(wybor == '1') loadDisk();
    else if(wybor == '2') saveDisk();
    else if(wybor == '3')
    {
        printf("\n a/A. get by name\n b/B. get by Id");
        wybor = getch();

        if(wybor == 'a' || wybor == 'A')
        {
            cin >> name;
            Id = getId(name);
        }
        else if(wybor == 'b' || wybor == 'B') cin >> Id;
        currentId = Id;

        while(i1 < 25)
        {
            while(i2 < 80)
            {
                area[i2][i1] = '#';
                area2[i2][i1] = '#';
                chars[i2][i1] = '#';
                setColor(whatColor(area[i2][i1]), whatColor(area[i2][i1]));
                if(area[i2][i1] == '#') setColor(8, 7);
                printf("%c", area[i2][i1]);
                i2++;
            }
            i2 = 0;
            i1++;
        }
        i1 = 0;
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                if(images[Id].area[i2][i1] != '#')
                {
                    area[i2][i1] = images[Id].area[i2][i1];
                    area2[i2][i1] = images[Id].area2[i2][i1];
                    chars[i2][i1] = images[Id].chars[i2][i1];
                }
                i2++;
            }
            i2 = 0;
            i1++;
        }
    }
    else if(wybor == '4')
    {
        i1 = 0; i2 = 0;
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                images[currentId].area[i2][i1] = area[i2][i1];
                images[currentId].area2[i2][i1] = area2[i2][i1];
                images[currentId].chars[i2][i1] = chars[i2][i1];
                i2++;
            }
            i2 = 0;
            i1++;
        }
    }
    else if(wybor == '5')
    {
        printf("\n a/A. get by name\n b/B. get by Id");
        wybor = getch();

        if(wybor == 'a' || wybor == 'A')
        {
            cin >> name;
            Id = getId(name);
        }
        else if(wybor == 'b' || wybor == 'B') cin >> Id;
        currentId = Id;

        
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                images[currentId].area[i2][i1] = area[i2][i1];
                images[currentId].area2[i2][i1] = area2[i2][i1];
                images[currentId].chars[i2][i1] = chars[i2][i1];
                i2++;
            }
            i2 = 0;
            i1++;
        }
    }
    else if(wybor == '6')
    {
        currentId = images.size();
        images.push_back(image());
        printf("\n Set name of this picture:");
        cin >> images[currentId].name;
        printf("\n Id of this picture is: %s", images[currentId].name);

        i1 = 0; i2 = 0;
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                if(images[Id].area[i2][i1] != '#')
                {
                    area[i2][i1] = images[Id].area[i2][i1];
                    area2[i2][i1] = images[Id].area2[i2][i1];
                    chars[i2][i1] = images[Id].chars[i2][i1];
                }
                i2++;
            }
            i2 = 0;
            i1++;
        }
        i1 = 0;
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                setColor(whatColor(area[i2][i1]), whatColor(area[i2][i1]));
                if(area[i2][i1] == '#') setColor(8, 7);
                printf("%c", area[i2][i1]);
                i2++;
            }
            i2 = 0;
            i1++;
        }
    }
    draw();

}

char whatChar(short x)
{
    if(x == 1) return '1';
    else if(x == 2) return '2';
    else if(x == 3) return '3';
    else if(x == 4) return '4';
    else if(x == 5) return '5';
    else if(x == 6) return '6';
    else if(x == 7) return '7';
    else if(x == 8) return '8';
    else if(x == 9) return '9';
    else if(x == 10) return 'A';
    else if(x == 11) return 'B';
    else if(x == 12) return 'C';
    else if(x == 13) return 'D';
    else if(x == 14) return 'E';
    else if(x == 15) return 'F';
    else if(x == 16) return '#';
    else return '0';
}

void saveDisk()
{
    fstream openFile;
    short whatPic = 0, whatLine = 3, whatChar = 0;
    
    openFile.open("disk.wdd", ios::out);
    while(whatPic <= images.size() - 1)
    {
        if(whatPic != 0) openFile << endl;
        openFile << "Wer-Dar Disk v-1.5" << endl << images[whatPic].name << endl << "@" << endl;
        while(whatLine <= 79)
        {
            if(whatLine >= 3 && whatLine <= 27)
            {
                while(whatChar < 80)
                {
                    openFile << images[whatPic].area[whatChar][whatLine - 3];
                    whatChar++;
                }
                openFile << endl;
            }
            else if(whatLine >= 29 && whatLine <= 53)
            {
                while(whatChar < 80)
                {
                    openFile << images[whatPic].area2[whatChar][whatLine - 29];
                    whatChar++;
                }
                openFile << endl;
            }
            else if(whatLine >= 55 && whatLine <= 79)
            {
                openFile << endl;
                while(whatChar < 80)
                {
                    openFile << images[whatPic].chars[whatChar][whatLine - 55];
                    whatChar++;
                }
            }
            else if(whatLine == 28) openFile << endl;
            whatChar = 0;
            whatLine++;
        }
        whatLine = 3;
        whatPic++;
    }
    openFile.close();
}
void loadDisk()
{
    /*Wer-Dar Paint v-1.5*/
    images.clear();

    fstream openFile;
    string holder;
    int i1 = 0, i2 = 0, obraz = 0, line = 0;

    openFile.open("disk.wdd", ios::in);
    if(openFile.good() == false)
    {
        tp(0, 0); setColor(12, 15); printf("No disk.wdd found");
        getch();
        openFile.close();
        return;
    }
    while(!openFile.eof())
    {
        getline(openFile, holder);
        if(holder == "@") images.push_back(image());
    }
    
    openFile.close();
    
    openFile.open("disk.wdd", ios::in); //opens .wdd file
    while(!openFile.eof())
    {  
        getline(openFile, holder);
        line++;
        if(holder == "@") obraz++;

        if(line % 80 == 2)
        {
            images[obraz].name = holder;
        }
        else if(line % 80 >= 4 && line % 80 <= 28)
        {
            i2 = 0;
            while(i2 < 80)
            {
                images[obraz - 1].area[i2][line - (4 + (obraz - 1) * 80)] = holder[i2];
                i2++;
            }
        }
        else if(line % 80 >= 30 && line % 80 <= 54)
        {
            i2 = 0;
            while(i2 < 80)
            {
                images[obraz - 1].area2[i2][line - (30 + (obraz - 1) * 80)] = holder[i2]; //Loads chars to area2, similiar to area, this one reads lower part of .wdi file
                if(images[obraz - 1].area[i2][line - (30 + (obraz - 1) * 80)] == '#') images[obraz - 1].area2[i2][line - (30 + (obraz - 1) * 80)] = '#';
                i2++;
            }
        }
        else if(line % 80 >= 56 && line % 80 <= 79 || line % 80 == 0)
        {
            i2 = 0;
            while(i2 < 80)
            {
                images[obraz - 1].chars[i2][line - (56 + (obraz - 1) * 80)] = holder[i2]; //Loads chars to chars[x][y]
                if(images[obraz - 1].area[i2][line - (56 + (obraz - 1) * 80)] == '#') images[obraz - 1].chars[i2][line - (56 + (obraz - 1) * 80)] = ' ';
                i2++;
            }
        }
    }
    openFile.close();
}

void displayChar()
{
    tp(37, 25);
    setColor(currentColor, secondaryColor);
    printf("%c", currentChar); 
}

void draw()
{
    short i1 = 0, i2 = 0, howLong = 1, i = 2;
    char helper = chars[i2][i1];
    char helparea1 = area[i2][i1];
    char helparea2 = area2[i2][i1];
    char toolbar[34] =
    {
        '0', '0', '1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8', '9', '9', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', '#', '#'
    };
    char tools[4] = {(char)176, (char)177, (char)178, (char)220};
    string Display;

    while(i1 < 25)
    {
        while(i2 < 80)
        {
            if(area[i2][i1] == area[i2 + 1][i1] && area2[i2][i1] == area2[i2 + 1][i1] && chars[i2][i1] == chars[i2 + 1][i1] && i2 < 79) howLong++;
            else
            {
                tp(i2 - howLong + 1, i1);
                setColor(whatColor(helparea1), whatColor(helparea2));
                if(area[i2][i1] == '#') setColor(8, 7);
                for(int i = 1; i <= howLong; i++)
                {
                    Display += helper;
                }
                cout << Display;
                howLong = 1;
                if(i2 == 79)
                {
                    tp(i2, i1);
                    setColor(whatColor(area[i2][i1]), whatColor(area2[i2][i1]));
                    if(area[i2][i1] == '#') setColor(8, 7);
                    printf("%c", chars[i2][i1]);
                }
            }
            i2++;
            helper = chars[i2][i1];
            helparea1 = area[i2][i1];
            helparea2 = area2[i2][i1];
            Display.clear();
        }
        i1++; i2 = 0;
        helper = chars[i2][i1];
        helparea1 = area[i2][i1];
        helparea2 = area2[i2][i1];
        howLong = 1;
        Display.clear();
    }

    tp(0, 0);
    while(i < 36)
    {
        tp(i, 25);
        setColor(whatColor(toolbar[i - 2]), whatColor(toolbar[i - 2]));
        if(toolbar[i-2] == '#') setColor(8, 7);
        printf("%c", toolbar[i - 2]);
        if(i <= 33)
        {
            tp(i + 37, 25);
            setColor(0, whatColor(toolbar[i - 2]));
            printf("%c", tools[2]);
        }
        i++;
    }
    tp(72, 25);
    setColor(0, 15);
    printf("%c%c%c%c", tools[0], tools[1], tools[2], tools[3]);
    setColor(1, 8); 
    tp(0, 25); printf("%c%c", tools[1], tools[1]);
    tp(36, 25); printf("%c", tools[2]);
    tp(38, 25); printf("%c", tools[2]);
    tp(71, 25); printf("%c", tools[2]);
    tp(76, 25); printf("%c%c%c%c", tools[2], tools[2], tools[2], tools[2]);
    tp(0, 0);
}