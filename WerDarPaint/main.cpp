#include "mouser.hpp"

using namespace std;

/*

// Wer-Dar Paint v-1.4_02 by Jakub Sobacki
// Few things before you get started
// This app requires special treatment for cmd, it's written when app is opened (main function)

*/

/* Layers for painting */
char area[80][25], area2[80][25], chars[80][25];

/* Declaration for functions */
void keypressed(char input);
void clicked();
void doubleClicked();
void moved();

int whatColor(char x);
char whatChar(short x);
void save();
void load();
void displayChar();

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
            if(area[mx][my]=='#') setColor(8, 7);
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
        /*case ']':
            currentColor++; // Zwi©ksza si© zmienna o 1
            if(currentColor == 17) currentColor = 0; // Unikanie overflow tej zmiennej
            setColor(currentColor, secondaryColor); // Zmiana koloru na aktualny
            tp(mx, my);
            printf("X");
            displayChar();
        break;
        case '[':
            currentColor--;
            if(currentColor == -1) currentColor = 16;
            setColor(currentColor, secondaryColor);
            tp(mx, my);
            printf("X");
            displayChar();
        break;
        case '\'':
        case '\"':
            secondaryColor++;
            if(secondaryColor == 17) secondaryColor = 0;
            setColor(currentColor, secondaryColor);
            tp(mx, my);
            printf("X");
            displayChar();
        break;
        case ';': 
        case ':':
            secondaryColor--;
            if(secondaryColor == -1)secondaryColor = 16;
            setColor(currentColor, secondaryColor);
            tp(mx, my);
            printf("X");
            displayChar();
        break;*/
        case ' ':
            save();
            tp(0, 0); setColor(0, 15); printf("saved");
            Sleep(250);
            load();
        break;
        case 'L': 
        case 'l':
            load();
        break;
    }
    /*else if(input == 'C' || input == 'c')
    {
        short nmb;
        cin >> nmb;
        currentChar = nmb;
        load();
    }*/
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
char whatChar(short x)
{
    //if(x == '0')return 0;
    if(x == 1)return '1';
    else if(x == 2)return '2';
    else if(x == 3)return '3';
    else if(x == 4)return '4';
    else if(x == 5)return '5';
    else if(x == 6)return '6';
    else if(x == 7)return '7';
    else if(x == 8)return '8';
    else if(x == 9)return '9';
    else if(x == 10)return 'A';
    else if(x == 11)return 'B';
    else if(x == 12)return 'C';
    else if(x == 13)return 'D';
    else if(x == 14)return 'E';
    else if(x == 15)return 'F';
    else if(x == 16)return '#';
    else return '0';
}

void save()
{
    fstream newfile;
    short whatchar = 0, whatline = 0;
    newfile.open("export.wdi", ios::out);
    newfile << "Wer-Dar Image v-1.4" << endl;
    newfile.close();

    tp(0, 0);
    newfile.open("export.wdi", ios::app);
    while(whatline < 25)
    {
        while(whatchar < 80)
        {  
            newfile << area[whatchar][whatline];
            whatchar++;
        }
        newfile<<endl;
        whatchar = 0;
        whatline++;
    }
    newfile << endl << endl;
    whatchar = 0; whatline = 0;
    while(whatline < 25)
    {
        while(whatchar < 80)
        {  
            newfile << area2[whatchar][whatline];
            whatchar++;
        }
        newfile << endl;
        whatchar = 0;
        whatline++;
    }
    newfile << endl << endl;
    whatchar = 0; whatline = 0;
    while(whatline < 25)
    {
        while(whatchar < 80)
        {  
            newfile << chars[whatchar][whatline];
            whatchar++;
        }
        newfile << endl;
        whatchar = 0;
        whatline++;
    }
    newfile.close();
}
void load()
{
    /*Wer-Dar Paint v-1.4*/
    fstream openfile;
    string holder;
    int i1 = 0, i2 = 0;

    openfile.open("export.wdi", ios::in);
    if(openfile.good() == false)
    {
        tp(0, 0); setColor(0, 15); printf("error 404");
        openfile.close();
        return;
    }
    openfile.close();
    openfile.open("export.wdi", ios::in);
    while(getline(openfile, holder))
    {
        if(i1 < 26 && i1 > 0)
        {
            while(i2 < 80)
            {
                area[i2][i1 - 1] = holder[i2];
                i2++;
            }
        }
        if(i1 > 27 && i1 < 53)
        {
            while(i2 < 80)
            {
                area2[i2][i1 - 28] = holder[i2];
                i2++;
            }
        }
        if(i1 > 54 && i1 < 80)
        {
            while(i2 < 80)
            {
                chars[i2][i1 - 55] = holder[i2];
                i2++;
            }
        }
    i2 = 0;
    i1++;
    }
    i1 = 0; i2 = 0;
    while(i1 < 25)
    {
        tp(0, i1);
        while(i2 < 80)
        {
            if(area[i2][i1] == '#') setColor(8, 7);
            else setColor(whatColor(area[i2][i1]), whatColor(area2[i2][i1]));
            if(area[i2][i1] == '#') printf("#");
            else printf("%c", chars[i2][i1]);
            i2++;
        }
        i1++; i2 = 0;
    }
    /*setColor(0,0);
    printf("%70s");*/
    openfile.close();
}

void displayChar()
{
    tp(37, 25);
    setColor(currentColor, secondaryColor);
    printf("%c", currentChar); 
}