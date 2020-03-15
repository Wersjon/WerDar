#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <cmath> 

// Defining basic values
#define BLACK 0
#define DARK_BLUE 1
#define DARK_GREEN 2
#define DARK_AQUA 3
#define DARK_RED 4
#define PURPLE 5
#define DARK_YELLOW 6
#define LIGHT_GRAY 7
#define GRAY 8
#define BLUE 9
#define GREEN 10
#define AQUA 11
#define RED 12
#define PINK 13
#define YELLOW 14
#define WHITE 15

#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67
#define KEY_F10 68
#define KEY_HOME 71
#define KEY_ARROW_UP 72
#define KEY_PGUP 73
#define KEY_ARROW_LEFT 75
#define KEY_ARROW_RIGHT 77
#define KEY_END 79
#define KEY_ARROW_DOWN 80
#define KEY_PGDOWN 81
#define KEY_INS 82
#define KEY_DEL 83

// special keys - some might not work; they are for tests
#define KEY_F11 -123
#define KEY_F12 -122
#define KEY_BACKSPACE 9
#define KEY_TAB 9
#define KEY_SPACE 32 

#define debugVar(var) std::cout << #var << "=" << var << ";" // DarXe's changed debug function <3

/*
####################################################################################################
##                                                                                                ##
##  Wer-Dar Paint v - 1.10_2 by Jakub Sobacki                                                     ##
##  Few things before you get started                                                             ##
##  This app requires special treatment for cmd, it's written when app is opened (main function)  ##
##                                                                                                ##
####################################################################################################
*/

/* Altho, this is seperate class, this still belongs to mouser family */
class image
{
public:
    char backgroundLayer[80][25], colorLayer[80][25], characterLayer[80][25]; // Layers of painting
    std::string name; // Holds the name of the image

    image() // Initiates the class for vector
    {
        short whatLine = 0, whatChar = 0;
        while(whatLine < 25)
        {
            while(whatChar < 80)
            {
                backgroundLayer[whatChar][whatLine] = '`';  // |
                colorLayer[whatChar][whatLine] = '`'; // +} Those Lines are setting default values for image 
                characterLayer[whatChar][whatLine] = '`'; // |
                whatChar++;
            }
            whatLine++;
            whatChar = 0;
        }
        name = "placeholder"; // Sets the name to placeholder
    }
};

std::vector <image> images; // Creates vector for images to hold a lot of them

/*
#                     Few words of introduction to MOUSER.
#
# mouser is mouse based "engine", that's based on mouse.
# It's based on few function and base function on 4 (onMove, onClick, onDClick, keyPress).
# The other functions are essentials to work on & with mouser.
# Created By Jakub 'Wersjon' Sobacki
*/

class mouser
{
public:
    short mx, my; // Holds the value of mouse position
    short px, py; // Holds the value of previous mouse position, useful for hovers.
    bool doClick; // Holds value of click, if user clicks, this changes into true, and when unclicks to false,
    // it prevents from double click - hold bug.
        
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    void mouse(void click(), void doubleclick(), void moving(), void keyPress(char input))
    {
        INPUT_RECORD Record; // Describes an input event.
        DWORD NumRead; // Creates 32-bit unsigned integer.
        bool doChar; // Function is running when key is pressed and unpressed, so it's for removing 2 function runs,
        // Similiar to click and unclick with mouse.

        while(true)
        {
            ReadConsoleInput(hIn, &Record, 1, &NumRead);
            if(Record.EventType == KEY_EVENT) // If input is a pressed key:
            { 
                doChar = (doChar) ?0 :1; // Records reads press & unpress, so it's nessesary to have this and if below:
                if(doChar) keyPress(Record.Event.KeyEvent.uChar.AsciiChar); 
            }
            if(Record.EventType == MOUSE_EVENT) // If mouse caused an event:
            {
                py = my;
                px = mx;
                my = Record.Event.MouseEvent.dwMousePosition.Y; // Saves cursor position (Y)
                mx = Record.Event.MouseEvent.dwMousePosition.X; // Saves cursor position (X)
                if(Record.Event.MouseEvent.dwEventFlags == 0) // If user clicks:
                {
                    doClick = (doClick) ?0 :1; // Records reads press & unpress, so it's nessesary to have this and if below  
                    if(doClick == true) click();
                }
                else if(Record.Event.MouseEvent.dwEventFlags == 1) moving();
                else if(Record.Event.MouseEvent.dwEventFlags == 2) doubleclick();
            }
            Sleep(10); // Every 10 seconds it recives information about mouse (It can't go higher than 100FPS)
        }
    }

    short getId(std::string imageName) // Gets an ID of the image from it's name
    {
        for(short whatPic = 0; whatPic++; whatPic <= images.size() - 1)
        {
            if(images[whatPic].name == imageName) return whatPic; // Checks for name of image,
            // if it's true it returns the ID, if not it checks next ID.
        }
        return 0;
    }

    void hideCursor() // Hides Cursor from user: (doesn't work if user resized the window)
    {
        CONSOLE_CURSOR_INFO cursorInfo; // Sets variable that contains information about CursorInfo
        cursorInfo.dwSize = 1; // Sets it size to 1
        cursorInfo.bVisible = FALSE; // Makes it invisible
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); // Sets CursorInfo
    }

    void tp(int x, int y) // Teleports coordinates:
    {
        COORD coords; // Creates variable that contains coords
        coords.X = x;
        coords.Y = y;
        SetConsoleCursorPosition(hOut, coords); // Sets cursor position to coords.x | y.
    }

    void setColor(int bg, int c) // sets Console colors:
    {
        /*
            // Colors are implemented in numbers
            // After every 16*x there is new background, so it's: 0 - black; 16 - Blue; 32 - Green; ...
            // There is new color for char every 1, and it resets after hitting 16, so it's:  0 - black; 1 - Blue; 2 - Green; ...
        */
        SetConsoleTextAttribute(hOut, bg * 16 + c);
    }

    void clear() // Clears 80x25 Screen:
    {
        setColor(BLACK, BLACK);
        tp(0, 0);
        printf("%2000i"); // Prints 2000 characters of double value.
        tp(0, 0);
    }

    int getColor(char x) // Says about color of "char x". Colors are stored in HEX value in .wdi files:
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
        else if(x == '`') return 8;

        else return 0;
    }
    
    char getChar(short x) // Says what char, should be color stored in short.
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
        else if(x == 16) return '`';
        else return '0';
    }

    std::string convertToUTF(std::string strBefore)
    {
        // This function converts basic strings into UTF-8 strings with special characters
        std::string strAfter = "";
        // 176 - \u2591
        // 177 - \u2592
        // 178 - \u2593
        // 220 - \u2584

        // Checks every char and checks if it is special one, if so it remakes it into new one
        for(short i = 0; i < strBefore.length(); i++)
        {
            if(strBefore[i] == (char)176) strAfter += "\u2591";
            else if(strBefore[i] == (char)177) strAfter += "\u2592";
            else if(strBefore[i] == (char)178) strAfter += "\u2593";
            else if(strBefore[i] == (char)220) strAfter += "\u2584";
            else strAfter += strBefore[i];
        }
        return strAfter; // returns value of this string, ready for a display
    }
    
    std::string convertCharToUTF(char charBefore)
    {
        // This function converts char into UTF-8 string with special characters
        std::string strAfter = "";
        if(charBefore == (char)176) strAfter += "\u2591"; // Checks char and checks if it is special one, if so it transfers it into string
        else if(charBefore == (char)177) strAfter += "\u2592";
        else if(charBefore == (char)178) strAfter += "\u2593";
        else if(charBefore == (char)220) strAfter += "\u2584";
        else strAfter += charBefore;

        return strAfter; // returns value of this char, ready for a display
    }
    
    /* Legacy fileloader, don't touch */
    void loadfile(std::string filename) // Loads .wdi file from version 1.5
    {
        /*Wer-Dar Paint v - 1.5*/
        char area[80][25], area2[80][25], chars[80][25]; // sets variable for 3 painting layers
        std::fstream openfile;
        std::string holder;
        int i1 = 0, i2 = 0;

        openfile.open(filename + ".wdi", std::ios::in); // opens .wdi file
        if(openfile.good() == false) // if it doesn't exist, it displays "error 404"(file not found).
        {
            tp(0, 0); setColor(BLACK, WHITE);
            printf("error 404");
            openfile.close();
            return;
        }
        openfile.close();
        openfile.open(filename + ".wdi", std::ios::in);
        while(getline(openfile, holder)) // Opens file, and gets to every line value to holder
        {
            if(i1 < 26 && i1 > 0)
            {
                while(i2 < 80)
                {
                    area[i2][i1 - 1] = holder[i2]; // Loads to area[x][y] holder[x] value, every iteration, there is new y in holder.
                    i2++; // x is 1 higher
                }
            }
            if(i1 > 27 && i1 < 53)
            {
                while(i2 < 80)
                {
                    area2[i2][i1 - 28] = holder[i2]; // Loads chars to area2, similiar to area, this one reads lower part of .wdi file
                    i2++;
                }
            }
            if(i1 > 54 && i1 < 80)
            {
                while(i2 < 80)
                {
                    chars[i2][i1 - 55] = holder[i2]; // Loads chars to chars[x][y]
                    i2++;
                }
            }
            i2=0;
            i1++;
        }
        i1=0; i2=0;
        while(i1 < 25) // Displays paiting on canvas
        {
            while(i2 < 80)
            {
                tp(i2, i1);
                setColor(getColor(area[i2][i1]), getColor(area2[i2][i1])); // Sets color of area and area2 by getColor
                if(area[i2][i1]!='`') std::cout << convertCharToUTF(chars[i2][i1]); // If char isn't "invisible", it doesn't print it.
                i2++;
            }
            i1++; i2 = 0;
        }
        openfile.close();
    }
}Engine;  //creates mouser Engine;

class essentials
{
public:
    bool doMenu = false, menu_Drawed, modeText = false; // Information about menu and modeText.
    char currentChar = (char)177, previousChar; // Information about paints char
    short currentId, mainColor = 15, secondaryColor = 15; // Id of picture, and paint colors
    
    // Layers of image & helpers for drawing (tools & toolbar)
    char backgroundLayer[80][25], colorLayer[80][25], characterLayer[80][25],
    tools[4] = {(char)176, (char)177, (char)178, (char)220},
    toolbar[34] =
    {
        '0', '0', '1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8', '9', '9', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', '`', '`'
    };

    void saveDisk() // Saves every picture into disk.wdd
    {
        std::fstream openFile;
        short whatPic = 0, whatLine = 3, whatChar = 0; // whatPic is the ID of the picture that's currently worked on
        
        openFile.open("disk.wdd", std::ios::out);
        while(whatPic <= images.size() - 1) // Do this, while picture worked on is smaller || equal to the size of vector - 1.
        {
            if(whatPic != 0) openFile << std::endl; // Displays enter before almost every picture (not the first one)
            // Displays basic information about the picture, and version of paint it has been painted on.
            openFile << whatPic << " | Wer-Dar Disk v - 1.10_2" << std::endl << images[whatPic].name << std::endl << "@" << std::endl;
            // Saves every char into file
            while(whatLine <= 79)
            {
                if(whatLine >= 3 && whatLine <= 27)
                {
                    while(whatChar < 80)
                    {
                        openFile << images[whatPic].backgroundLayer[whatChar][whatLine - 3];
                        whatChar++;
                    }
                    openFile << std::endl;
                }
                else if(whatLine >= 29 && whatLine <= 53)
                {
                    while(whatChar < 80)
                    {
                        openFile << images[whatPic].colorLayer[whatChar][whatLine - 29];
                        whatChar++;
                    }
                    openFile << std::endl;
                }
                else if(whatLine >= 55 && whatLine <= 79)
                {
                    openFile << std::endl;
                    while(whatChar < 80)
                    {
                        openFile << images[whatPic].characterLayer[whatChar][whatLine - 55];
                        whatChar++;
                    }
                }
                else if(whatLine == 28) openFile << std::endl;
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
        /*Wer-Dar Paint v - 1.10_2*/
        std::fstream openFile;
        std::string holder; // Holds current line
        int whatChar = 0, whatPic = 0, line = 0;

        images.clear(); // Clears the image vector

        openFile.open("disk.wdd", std::ios::in);
        if(openFile.good() == false)
        {
            // Informs user about error
            Engine.tp(0, 0); Engine.setColor(RED, WHITE); printf("No disk.wdd found");
            getch();
            openFile.close();
            return; // Returns function
        }
        while(!openFile.eof())
        {
            // While there are lines, it does:
            getline(openFile, holder); // gets current line
            if(holder == "@") images.push_back(image()); // pushes @.ammount of images
        }
        
        openFile.seekg(0, openFile.beg); // Teleports cursor to the first char

        while(!openFile.eof()) // While file can read lines
        {  
            getline(openFile, holder); // get current line
            line++; // set current line number
            if(holder == "@") whatPic++; // If it's @, it's new picture

            if(line % 80 == 2) // If it can be devided by 2
            {
                images[whatPic].name = holder; // Set the name of picture on line 2
            }
            else if(line % 80 >= 4 && line % 80 <= 28)
            {
                whatChar = 0;
                while(whatChar < 80)
                {
                    // From line 4 to line 28 it stores backgroundLayer
                    images[whatPic - 1].backgroundLayer[whatChar][line - (4 + (whatPic - 1) * 80)] = holder[whatChar];
                    whatChar++;
                }
            }
            else if(line % 80 >= 30 && line % 80 <= 54)
            {
                whatChar = 0;
                while(whatChar < 80)
                {
                    // From line 30 to line 54 it stores colorLayer
                    images[whatPic - 1].colorLayer[whatChar][line - (30 + (whatPic - 1) * 80)] = holder[whatChar]; // Loads characterLayer to colorLayer, similiar to backgroundLayer, this one reads lower part of .wdi file
                    if(images[whatPic - 1].backgroundLayer[whatChar][line - (30 + (whatPic - 1) * 80)] == '`') images[whatPic - 1].colorLayer[whatChar][line - (30 + (whatPic - 1) * 80)] = '`';
                    whatChar++;
                }
            }
            else if(line % 80 >= 56 && line % 80 <= 79 || line % 80 == 0)
            {
                // From line 56 to line 79 it stores characterLayer
                whatChar = 0;
                while(whatChar < 80)
                {
                    images[whatPic - 1].characterLayer[whatChar][line - (56 + (whatPic - 1) * 80)] = holder[whatChar]; // Loads characterLayer to characterLayer[x][y]
                    if(images[whatPic - 1].backgroundLayer[whatChar][line - (56 + (whatPic - 1) * 80)] == '`') images[whatPic - 1].characterLayer[whatChar][line - (56 + (whatPic - 1) * 80)] = '`';
                    whatChar++;
                }
            }
        }
        openFile.close();
    }

    void displayChar() // Displays char on bottom of screen
    {
        short bgC_holder, C_holder; // Holds value for colors
        Engine.tp(37, 25);

        // if color is transparent, it sets color to "transparent"
        if(mainColor == 16) bgC_holder = 8;
        else bgC_holder = mainColor;
        if(secondaryColor == 16) C_holder = 7;
        else C_holder = secondaryColor;

        Engine.setColor(bgC_holder, C_holder); // Sets the color
        std::cout << Engine.convertCharToUTF(currentChar); // Couts the char
    }

    void draw()
    {
        short whatLine = 0, whatChar = 0, howLong = 1; // those works like i / i1 / i2
        short bgC_holder, C_holder; // Holds value for colors

        /* Helpers / holders for Layer values */
        char helpCharacterLayer = characterLayer[whatChar][whatLine];
        char helpBackgroundLayer = backgroundLayer[whatChar][whatLine];
        char helpColorLayer = colorLayer[whatChar][whatLine];

        std::string Display; // this std::string is displayed as a chain of chars

        while(whatLine < 25)
        {
            while(whatChar < 80)
            {
                // Checks if next Layer's chars are the same, if so it makes 
                if(backgroundLayer[whatChar][whatLine] == backgroundLayer[whatChar + 1][whatLine] && colorLayer[whatChar][whatLine] == colorLayer[whatChar + 1][whatLine] && characterLayer[whatChar][whatLine] == characterLayer[whatChar + 1][whatLine] && whatChar < 79) howLong++;
                else
                {
                    Engine.tp(whatChar - howLong + 1, whatLine); // Teleports to current char
                    bgC_holder = Engine.getColor(backgroundLayer[whatChar][whatLine]);
                    C_holder = Engine.getColor(colorLayer[whatChar][whatLine]);
                    // Sets transparent color:
                    if(backgroundLayer[whatChar][whatLine] == '`') bgC_holder = 8;
                    if(colorLayer[whatChar][whatLine] == '`') C_holder = 7;
                    Engine.setColor(bgC_holder, C_holder);

                    for(int i = 1; i <= howLong; i++) // Increate "howLong" times chars of Display with helpCharacterLayer;
                    {
                        Display += helpCharacterLayer;
                    }
                    std::cout << Engine.convertToUTF(Display); // Couts display - worth noting that printf doesn't work here.
                    howLong = 1;
                    if(whatChar == 79) // If character is 79th in any line:
                    {
                        // The reason, this if exists is basically bugs, it does pretty much same as above
                        Engine.tp(whatChar, whatLine);
                        bgC_holder = Engine.getColor(backgroundLayer[whatChar][whatLine]); 
                        C_holder = Engine.getColor(colorLayer[whatChar][whatLine]);
                        if(backgroundLayer[whatChar][whatLine] == '`') bgC_holder = 8;
                        if(colorLayer[whatChar][whatLine] == '`') C_holder = 7;
                        Engine.setColor(bgC_holder, C_holder);
                        std::cout << Engine.convertCharToUTF(characterLayer[whatChar][whatLine]);
                    }
                }
                whatChar++;
                helpCharacterLayer = characterLayer[whatChar][whatLine];
                helpBackgroundLayer = backgroundLayer[whatChar][whatLine];
                helpColorLayer = colorLayer[whatChar][whatLine];
                Display.clear(); // clears the std::string to NULL / "" value
            }
            whatLine++; whatChar = 0;
            helpCharacterLayer = characterLayer[whatChar][whatLine];
            helpBackgroundLayer = backgroundLayer[whatChar][whatLine];
            helpColorLayer = colorLayer[whatChar][whatLine];
            howLong = 1; // Sets howLong to default - 1 char to display
        }
        
        for(int i = 0; i < 36; i++) // Draw toolbar [p1]
        {
            Engine.tp(i, 25);
            Engine.setColor(Engine.getColor(toolbar[i - 2]), Engine.getColor(toolbar[i - 2]));
            if(toolbar[i-2] == '`') Engine.setColor(GRAY, LIGHT_GRAY);
            std::cout << Engine.convertCharToUTF(toolbar[i - 2]);
            if(i <= 33)
            {
                Engine.tp(i + 37, 25);
                Engine.setColor(BLACK, Engine.getColor(toolbar[i - 2]));
                std::cout << Engine.convertCharToUTF(tools[2]);
            }
        }
        // Draw toolbar [p2]
        Engine.setColor(GRAY, LIGHT_GRAY);
        Engine.tp(71, 25);
        printf("``");

        Engine.tp(74, 25);
        Engine.setColor(BLACK, WHITE);
        std::cout << Engine.convertCharToUTF(tools[0]) << Engine.convertCharToUTF(tools[1]) << Engine.convertCharToUTF(tools[2]) << Engine.convertCharToUTF(tools[3]) << "~";
        Engine.setColor(DARK_BLUE, GRAY); 
        Engine.tp(0, 25); std::cout << Engine.convertCharToUTF(tools[1]) << Engine.convertCharToUTF(tools[1]);
        Engine.tp(36, 25); std::cout << Engine.convertCharToUTF(tools[2]);
        Engine.tp(38, 25); std::cout << Engine.convertCharToUTF(tools[2]);
        Engine.tp(73, 25); std::cout << Engine.convertCharToUTF(tools[2]);
    }
    short imageChooser()
    {
        char oldArea[80][25], oldArea2[80][25], oldChars[80][25];
        char helper, helparea1, helparea2, option;
        
        short bgC_holder, c_holder;
        short whatLine, whatChar;
        short choosingPic = 0, howLong;

        std::string Display;

        while(true)
        {   
            for(short whatLineFor = 0; whatLineFor < 25; whatLineFor++)
            {
                for(short whatCharFor = 0; whatCharFor < 80; whatCharFor++)
                {
                    oldArea[whatCharFor][whatLineFor] = images[choosingPic].backgroundLayer[whatCharFor][whatLineFor];
                    oldArea2[whatCharFor][whatLineFor] = images[choosingPic].colorLayer[whatCharFor][whatLineFor];
                    oldChars[whatCharFor][whatLineFor] = images[choosingPic].characterLayer[whatCharFor][whatLineFor];
                }
            }
        
            // Setting values for display
            howLong = 1;
            whatLine = 0, whatChar = 0;
            helper = oldChars[whatChar][whatLine];
            helparea1 = oldArea[whatChar][whatLine];
            helparea2 = oldArea2[whatChar][whatLine];

            while(whatLine < 25) // Displays paiting on canvas
            {
                while(whatChar < 80)
                {
                    // Checks if next char is the same, if so howlong value is incremented
                    if(oldArea[whatChar][whatLine] == oldArea[whatChar + 1][whatLine] && oldArea2[whatChar][whatLine] == oldArea2[whatChar + 1][whatLine] && oldChars[whatChar][whatLine] == oldChars[whatChar + 1][whatLine] && whatChar < 79) howLong++;
                    else
                    {
                        // If it isn't it does this:
                        Engine.tp(whatChar - howLong + 1, whatLine); // teleports to starting char
                        // Color setting:
                        bgC_holder = Engine.getColor(helparea1);
                        c_holder = Engine.getColor(helparea2);
                        if(oldArea[whatChar][whatLine] == '`') bgC_holder = GRAY;
                        if(oldArea2[whatChar][whatLine] == '`') c_holder = LIGHT_GRAY;
                        Engine.setColor(bgC_holder, c_holder);

                        for(short i = 1; i <= howLong; i++)
                        {
                            Display += helper;
                        } // Making Display having howLong times of "helper" char.
                        std::cout << Engine.convertToUTF(Display); // couting Display with UTF-8
                        howLong = 1; // reseting howLong
                        if(whatChar == 79)
                        {
                            // If it's 79, it does practicaly the same:
                            Engine.tp(whatChar, whatLine);
                            bgC_holder = Engine.getColor(helparea1);
                            c_holder = Engine.getColor(helparea2);
                            if(oldArea[whatChar][whatLine] == '`') bgC_holder = GRAY;
                            if(oldArea2[whatChar][whatLine] == '`') c_holder = LIGHT_GRAY;
                            Engine.setColor(bgC_holder, c_holder);
                            std::cout << Engine.convertCharToUTF(oldChars[whatChar][whatLine]);
                        }
                    }
                    // Setting values
                    whatChar++;
                    helper = oldChars[whatChar][whatLine];
                    helparea1 = oldArea[whatChar][whatLine];
                    helparea2 = oldArea2[whatChar][whatLine];
                    Display.clear();
                }
                // Setting values
                whatLine++; whatChar = 0;
                helper = oldChars[whatChar][whatLine];
                helparea1 = oldArea[whatChar][whatLine];
                helparea2 = oldArea2[whatChar][whatLine];
                howLong = 1;
            }

            // Writing bottom bar with name of current Picture, and it's name
            Engine.tp(0, 25);
            Engine.setColor(BLACK, BLACK);
            printf("%80i");
            Engine.tp(0, 25);
            Engine.setColor(BLACK, WHITE);
            std::cout << " " << choosingPic << " | " << images[choosingPic].name << " ";
            Engine.tp(0, 0);

            // simple switch with char controls
            option = getch();
            switch(option)
            {
                case 'A':
                case 'a':
                case KEY_ARROW_LEFT: // <-
                    choosingPic--;
                    if(choosingPic < 0) choosingPic = images.size() - 1;
                break;

                case 'D':
                case 'd':
                case KEY_ARROW_RIGHT: // ->
                    choosingPic++;
                    if(choosingPic > images.size() - 1) choosingPic = 0;
                break;

                case ' ':
                case KEY_ENTER:
                    return choosingPic; // If user click one of those keys, it returns the value
                break;
            }
        }
    }

    void tyldaMenu()
    {
        char choice;
        bool choiceDrawn;
        short currentChoice = 1;
        int getIntForChar;
        
        Engine.doClick = false;

        // Display menu
        Engine.tp(32, 11);
        Engine.setColor(DARK_BLUE, LIGHT_GRAY);
        printf("╔══Other Menu══╗");

        Engine.tp(32, 14);
        printf("╚══════════════╝");

        Engine.tp(32, 12);
        printf("║");
        Engine.setColor(AQUA, BLACK);
        printf(" Text Option  ");
        Engine.setColor(DARK_BLUE, LIGHT_GRAY);
        printf("║");
        Engine.tp(32, 13);
        printf("║");
        Engine.setColor(DARK_AQUA, DARK_BLUE);
        printf(" Select Char  ");
        Engine.setColor(DARK_BLUE, LIGHT_GRAY);
        printf("║");

        while(true)
        {
            choice = getch();

            // choosing option from menu:
            switch(choice)
            {
                case KEY_ARROW_UP:
                case 'W':
                case 'w':
                    currentChoice--;
                    if(currentChoice < 1) currentChoice = 2;
                    choiceDrawn == false;
                break;
                case KEY_ARROW_DOWN:
                case 'S':
                case 's':
                    currentChoice++;
                    if(currentChoice > 2) currentChoice = 1;
                    choiceDrawn == false;
                break;
            }

            if(currentChoice == 1 && choiceDrawn == false)
            {
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                Engine.tp(32, 12);
                printf("║");
                Engine.setColor(AQUA, BLACK);
                // Highlight current option
                printf(" Text Option  ");
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                printf("║");
                
                // unHighlight other option
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                Engine.tp(32, 13);
                printf("║");
                Engine.setColor(DARK_AQUA, DARK_BLUE);
                printf(" Select Char  ");
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                printf("║");

                choiceDrawn == true;
            }
            else if(currentChoice == 2 && choiceDrawn == false)
            {
                // Highlight current option
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                Engine.tp(32, 13);
                printf("║");
                Engine.setColor(AQUA, BLACK);
                printf(" Select Char  ");
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                printf("║");

                // unHighlight other option
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                Engine.tp(32, 12);
                printf("║");
                Engine.setColor(DARK_AQUA, DARK_BLUE);
                printf(" Text Option  ");
                Engine.setColor(DARK_BLUE, LIGHT_GRAY);
                printf("║");

                choiceDrawn == true;
            }
            if(choice == KEY_SPACE || choice == KEY_ENTER) break; //If user clicks either keys it breaks the loop
        }
        if(currentChoice == 1) modeText = true; //turns modeText on; currently not implemented
        else if(currentChoice == 2)
        {
            //Asks user about what char they want; and how they want to get it:
            Engine.clear();
            Engine.setColor(BLACK, WHITE);
            Engine.tp(0, 0);
            printf("would you like to write it in char or int form?\n1.Char\n2.int");
            choice = getch();
            switch(choice)
            {
                case '1':
                    printf("Write proper Char:");
                    std::cin >> currentChar;
                break;
                case '2':
                    printf("Write proper Int:");
                    std::cin >> getIntForChar;
                    currentChar = getIntForChar;
                break;
            }
        }
        draw(); //Draws current canvas
        displayChar(); //Draws current char
    }
}Paint; //creates essentials Paint;