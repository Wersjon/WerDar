#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class image
{
public:
    char area[80][25], area2[80][25], chars[80][25];
    string name;

    image()
    {
        short i1 = 0, i2 = 0;
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                area[i2][i1] = '1';
                area2[i2][i1] = '2';
                chars[i2][i1] = '3';
                i2++;
            }
            i1++;
            i2 = 0;
        }
        name = "placeholder";
    }
};

vector <image> images;

class mouser
{
public:
    short mx, my, currentId, currentColor = 15, secondaryColor = 15, px, py;
    bool doClick;
    char area[80][25], area2[80][25], chars[80][25], currentChar = (char)177, tools[4] = {(char)176, (char)177, (char)178, (char)220},
    toolbar[34] =
    {
        '0', '0', '1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8', '9', '9', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', '#', '#'
    };
        
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    void mouse(void click(), void doubleclick(), void moving(), void keypress(char input))
    {
        INPUT_RECORD Record; //Describes an input event.
        DWORD NumRead; //Creates 32-bit unsigned integer.
        bool doChar; //Function is running when key is pressed and unpressed, so it's for removing 2 function runs

        while(true)
        {
            Sleep(10);
            ReadConsoleInput(hIn, &Record, 1, &NumRead); //Read Input
            if(Record.EventType == KEY_EVENT) //If input is pressed key:
            { 
                doChar = (doChar) ?0 :1; //Records reads press & unpress, so it's nessesary to have this and if below:
                if(doChar == true) keypress(Record.Event.KeyEvent.uChar.AsciiChar); //runs function that contains char
            }
            if(Record.EventType == MOUSE_EVENT) //If mouse caused an effect:
            {
                if(Record.Event.MouseEvent.dwEventFlags == 0) //If user clicks:
                {
                    doClick = (doClick) ?0 :1; //Records reads press & unpress, so it's nessesary to have this and if below 
                    my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    if(doClick == true) click(); //runs click
                }
                else if(Record.Event.MouseEvent.dwEventFlags == 2) //if user DClicks:
                {
                    my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    doubleclick(); //runs doubleclick
                }
                else if(Record.Event.MouseEvent.dwEventFlags == 1) //Gets where mouse is located, it needs to be in bottom.
                {
                    my = Record.Event.MouseEvent.dwMousePosition.Y; //Saves cursor position (Y)
                    mx = Record.Event.MouseEvent.dwMousePosition.X; //Saves cursor position (X)
                    moving(); //runs moving
                }
            }
        }
    }

    short getId(string originalName)
    {
        short i = 0;
        while(i <= images.size() - 1)
        {
            if(images[i].name == originalName) return i;
            i++;
        }
        return 0;
    }

    void hideCursor() //Hides Cursor from user: (doesn't work if user resized window[?])
    {
        CONSOLE_CURSOR_INFO cursorInfo; //Sets variable called cursorInfo that contaisn cursors info
        cursorInfo.dwSize = 1; //Sets it's size to 1
        cursorInfo.bVisible = FALSE; //Makes it invisible
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //Sets value into cmd
    }

    void tp(int x, int y) //Teleports coordinates:
    {
        COORD coords; //Creates Coordinates variable named c.
        coords.X = x; //Sets X coordinate.
        coords.Y = y; //Sets Y coordinate.
        SetConsoleCursorPosition(hOut, coords); //Sets Cursor Position to c.X, c.Y.
    }

    void setColor(int bg, int c) //sets Console colors:
    {
        /*
            // Colors are implemented in numbers
            // After every 16*x there is new background, so it's: 0 - black; 16 - Blue; 32 - Green;
            // There is new color for char every 1, and it resets after hitting 16, so it's:  0 - black; 1 - Blue; 2 - Green;
        */
        SetConsoleTextAttribute(hOut, bg * 16 + c); //Sets color
    }

    void clear() //Clears 80x25 Screen:
    {
        tp(0, 0); //teleports to 0, 0
        printf("%2000d \n"); //Prints 2000 chars
    }

    int whatColor(char x) //Says about color of "char x". Colors are stored in HEX value in .wdi files:
    {
        if(x == '1') return 1;
        else if(x == '2') return 2;
        else if(x == '3') return 3;
        else if(x == '4') return 4;
        else if(x == '5') return 5;
        else if(x == '6') return 6;
        else if(x == '7') return 7;
        else if(x == '8') return 8;
        else if(x == '9') return 9;
        else if(x == 'A') return 10;
        else if(x == 'B') return 11;
        else if(x == 'C') return 12;
        else if(x == 'D') return 13;
        else if(x == 'E') return 14;
        else if(x == 'F') return 15;
        else return 0;
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

    void loadfile(string filename)
    {
        /*Wer-Dar Paint v-1.5*/
        char area[80][25], area2[80][25], chars[80][25]; //sets variable for 3 painting layers
        fstream openfile;
        string holder;
        int i1 = 0, i2 = 0;

        openfile.open(filename + ".wdi", ios::in); //opens .wdi file
        if(openfile.good() == false) //if it doesn't exist, it displays "error 404"(file not found).
        {
            tp(0, 0); setColor(0, 15);
            cout << "error 404";
            openfile.close();
            return;
        }
        openfile.close();
        openfile.open(filename + ".wdi", ios::in);
        while(getline(openfile, holder)) //Opens file, and gets to every line value to holder
        {
            if(i1 < 26 && i1 > 0)
            {
                while(i2 < 80)
                {
                    area[i2][i1 - 1] = holder[i2]; //Loads to area[x][y] holder[x] value, every iteration, there is new y in holder.
                    i2++; //x is 1 higher
                }
            }
            if(i1 > 27 && i1 < 53)
            {
                while(i2 < 80)
                {
                    area2[i2][i1 - 28] = holder[i2]; //Loads chars to area2, similiar to area, this one reads lower part of .wdi file
                    i2++;
                }
            }
            if(i1 > 54 && i1 < 80)
            {
                while(i2 < 80)
                {
                    chars[i2][i1 - 55] = holder[i2]; //Loads chars to chars[x][y]
                    i2++;
                }
            }
            i2=0;
            i1++;
        }
        i1=0; i2=0;
        while(i1 < 25) //Displays paiting on canvas
        {
            while(i2 < 80)
            {
                tp(i2, i1);
                setColor(whatColor(area[i2][i1]), whatColor(area2[i2][i1])); //Sets color of area and area2 by whatColor
                if(area[i2][i1]!='#') printf("%c", chars[i2][i1]); //If char isn't "invisible", it doesn't print it.
                i2++;
            }
            i1++; i2 = 0;
        }
        openfile.close();
    }
}Engine;

class essentials
{
public:
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
            Engine.tp(0, 0); Engine.setColor(12, 15); printf("No disk.wdd found");
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
        Engine.tp(37, 25);
        Engine.setColor(Engine.currentColor, Engine.secondaryColor);
        printf("%c", Engine.currentChar); 
    }

    void draw()
    {
        short i1 = 0, i2 = 0, howLong = 1, i = 2;
        char helper = Engine.chars[i2][i1];
        char helparea1 = Engine.area[i2][i1];
        char helparea2 = Engine.area2[i2][i1];
        string Display;

        while(i1 < 25)
        {
            while(i2 < 80)
            {
                if(Engine.area[i2][i1] == Engine.area[i2 + 1][i1] && Engine.area2[i2][i1] == Engine.area2[i2 + 1][i1] && Engine.chars[i2][i1] == Engine.chars[i2 + 1][i1] && i2 < 79) howLong++;
                else
                {
                    Engine.tp(i2 - howLong + 1, i1);
                    Engine.setColor(Engine.whatColor(helparea1), Engine.whatColor(helparea2));
                    if(Engine.area[i2][i1] == '#') Engine.setColor(8, 7);
                    for(int i = 1; i <= howLong; i++)
                    {
                        Display += helper;
                    }
                    cout << Display;
                    howLong = 1;
                    if(i2 == 79)
                    {
                        Engine.tp(i2, i1);
                        Engine.setColor(Engine.whatColor(Engine.area[i2][i1]), Engine.whatColor(Engine.area2[i2][i1]));
                        if(Engine.area[i2][i1] == '#') Engine.setColor(8, 7);
                        printf("%c", Engine.chars[i2][i1]);
                    }
                }
                i2++;
                helper = Engine.chars[i2][i1];
                helparea1 = Engine.area[i2][i1];
                helparea2 = Engine.area2[i2][i1];
                Display.clear();
            }
            i1++; i2 = 0;
            helper = Engine.chars[i2][i1];
            helparea1 = Engine.area[i2][i1];
            helparea2 = Engine.area2[i2][i1];
            howLong = 1;
            Display.clear();
        }

        Engine.tp(0, 0);
        while(i < 36)
        {
            Engine.tp(i, 25);
            Engine.setColor(Engine.whatColor(Engine.toolbar[i - 2]), Engine.whatColor(Engine.toolbar[i - 2]));
            if(Engine.toolbar[i-2] == '#') Engine.setColor(8, 7);
            printf("%c", Engine.toolbar[i - 2]);
            if(i <= 33)
            {
                Engine.tp(i + 37, 25);
                Engine.setColor(0, Engine.whatColor(Engine.toolbar[i - 2]));
                printf("%c", Engine.tools[2]);
            }
            i++;
        }
        Engine.tp(72, 25);
        Engine.setColor(0, 15);
        printf("%c%c%c%c", Engine.tools[0], Engine.tools[1], Engine.tools[2], Engine.tools[3]);
        Engine.setColor(1, 8); 
        Engine.tp(0, 25); printf("%c%c", Engine.tools[1], Engine.tools[1]);
        Engine.tp(36, 25); printf("%c", Engine.tools[2]);
        Engine.tp(38, 25); printf("%c", Engine.tools[2]);
        Engine.tp(71, 25); printf("%c", Engine.tools[2]);
        Engine.tp(76, 25); printf("%c%c%c%c", Engine.tools[2], Engine.tools[2], Engine.tools[2], Engine.tools[2]);
        Engine.tp(0, 0);
    }
}paint;