#include "mouser.hpp" // Including mouser.hpp with functions

/*
####################################################################################################
##                                                                                                ##
##  Wer-Dar Paint v - 1.10_2 by Jakub Sobacki                                                     ##
##  Few things before you get started                                                             ##
##  This app requires special treatment for cmd, it's written when app is opened (main function)  ##
##                                                                                                ##
####################################################################################################
*/

// Calling functions
void keypressed(char input);
void clicked();
void doubleClicked();
void moved();
void menu();

int main()
{
    SetConsoleOutputCP(65001); // Setting CodePage to 65001, to have all special (coded) characters in UTF-8 (Previously: 852)
    SetConsoleTitleA("Wer-Dar Paint v - 1.10_2"); // Setting console Title with name and version
    Engine.hideCursor();

    Engine.loadfile("wdplogo"); // Loading wdplogo.wdi (read) / legacy
    for(short i = 0; i < 25; i++) // If user clicks keyboard, it starts to load loading screen
    {
        if(kbhit()) 
        {
            getch();
            break;
        }
        Sleep(100);
    }

    Engine.clear(); // Clears the screen / system("cls") is broken, and slower.
    Engine.loadfile("load");

    /*informational text for user */
    Engine.tp(1, 1); Engine.setColor(BLACK, WHITE); printf("Edit modes: Turn off Quick edit mode;");
    Engine.setColor(RED, WHITE); printf(" T");
    Engine.setColor(BLACK, WHITE); printf("urn off insert mode; Turn rest on;");
    Engine.tp(1, 2); printf("Selecting Text: Everything off;");
    Engine.tp(1, 3); printf("Layout{");
    Engine.tp(1, 4); printf("- For buffer: Width: 80; Height: 50+;");
    Engine.tp(1, 5); Engine.setColor(BLACK, WHITE); printf("- For window: Width: 80; Height: 26+;");
    Engine.tp(1, 6); printf("- Turn off wrapping text on resize}");
    Engine.tp(1, 7); printf("Terminal(Windows 10 - experimental): ");
    Engine.setColor(RED, WHITE); printf("Tu");
    Engine.setColor(BLACK, WHITE); printf("rn off: Disable Scroll Forward option;");
    Engine.tp(1, 9); printf("Click any key to start drawing.");
    Engine.tp(1, 10); Engine.setColor(BLACK, RED); printf("DON'T MOUSE OVER RIGHT BOTTOM CORNER");
    images.push_back(image()); // Creates additional image
    getch(); // awaits for input from user

    /* Sets default value to Paint Layers */
    for(short whatLine = 0; whatLine < 25;  whatLine++)
    {
        for(short whatChar = 0; whatChar < 80;  whatChar++)
        {
            // Sets default value for Layers
            Paint.backgroundLayer[whatChar][whatLine] = '`';
            Paint.colorLayer[whatChar][whatLine] = '`';
            Paint.characterLayer[whatChar][whatLine] = '`';
        }
    }

    Paint.draw(); // Draws current Layers
    Engine.mouse(clicked, doubleClicked, moved, keypressed); // mouse(); is like loop in arduino, you can't leave it ;)
    // Semi-error message
    printf("You weren't supposed to be here, somehow you ended main(); click any key to quit");
    getch();
    return 0; // If somehow user ends here, it's
}

void keypressed(char input)
{
    // Currently there are no key functions
}

void clicked()
{
    if(Paint.doMenu == false)
    {
        /* if menu isn't ON, do those: */
        /* the default template is this:
        # if(Engine.my <= lowest_my && Engine.mx >= bigest_my && Engine.mx <= lowest_mx && Engine.mx >= bigest_mx)
        # {
        #     // Do onClick   
        # }
        */
        if(Engine.my < 25 && Engine.mx < 80) // If user clicked on drawing area:
        {
            Engine.tp(Engine.mx, Engine.my); // Teleports to cursor
            std::cout << Engine.convertCharToUTF(Paint.currentChar); // Couts current char on clicked element
            Paint.backgroundLayer[Engine.mx][Engine.my] = Engine.getChar(Paint.mainColor); // sets new bgL
            Paint.colorLayer[Engine.mx][Engine.my] = Engine.getChar(Paint.secondaryColor); // sets new cL
            Paint.characterLayer[Engine.mx][Engine.my] = Paint.currentChar; // sets new chL
        }
        /* Else if's here are basicly the bottom bar area */
        else if(Engine.my == 25 && Engine.mx < 2) // If user clicks on "start" icon; it:
        {
            Paint.doMenu = true; // Says to the program that it should be on Menu mode
            Paint.menu_Drawed = false; // Asks MENU to draw menu
        }
        else if(Engine.my == 25 && Engine.mx > 1 && Engine.mx < 36)
        {
            // Sets current BackGroundColor depending on which color user clicked:
            if(Paint.mainColor == 16 && Paint.secondaryColor == 16 && Engine.mx < 34) Paint.currentChar = Paint.previousChar;
            else if(Engine.mx >= 34 && Paint.secondaryColor == 16) Paint.previousChar = Paint.currentChar;
            Paint.mainColor = (Engine.mx - 2) / 2; // 
            if((Engine.mx - 2) / 2 > (Engine.mx - 1) / 2) Paint.mainColor = (Engine.mx - 1) / 2;
            if(Paint.secondaryColor == 16 && Paint.mainColor == 16) Paint.currentChar = '`';
            Paint.displayChar(); // Draws char on bottom bar
        }
        else if(Engine.my == 25 && Engine.mx > 38 && Engine.mx < 73)
        {
            // Sets current Color depending on which color user clicked:
            if(Paint.mainColor == 16 && Paint.secondaryColor == 16 && Engine.mx < 71) Paint.currentChar = Paint.previousChar;    
            else if(Engine.mx >= 71 && Paint.mainColor == 16) Paint.previousChar = Paint.currentChar;
            Paint.secondaryColor = (Engine.mx - 38) / 2;
            if((Engine.mx - 38) / 2 > (Engine.mx - 49) / 2) Paint.secondaryColor = (Engine.mx - 39) / 2;
            if(Paint.mainColor == 16 && Paint.secondaryColor == 16) Paint.currentChar = '`';
            Paint.displayChar();
        }
        else if(Engine.my == 25 && Engine.mx > 73 && Engine.mx < 78)
        {
            // Sets current tool
            Paint.currentChar = Paint.tools[Engine.mx - 74];
            Paint.displayChar();
        }
        else if(Engine.my == 25 && Engine.mx == 78)
        {
            Paint.tyldaMenu(); // Runs tylda menu with 2 suboptions for user
        }
    }
    else menu(); // if menu is on, run menu :v
}

void doubleClicked()
{
    Engine.doClick = true; // Prevents from d_click bug
}

void moved()
{
    if(Engine.doClick) clicked(); // It's simple spell, but quite unbreakable; mouse reads 2 inputs: click and unclick; it simply makes them as one

    if(Paint.doMenu == false)
    {
        /*pYpX*/ // previous y and previous x are the previous location of mouse; template is the same for click but with .px and .py
        if(Engine.py < 25 && Engine.px < 80)
        {
            Engine.setColor(Engine.getColor(Paint.backgroundLayer[Engine.px][Engine.py]), Engine.getColor(Paint.colorLayer[Engine.px][Engine.py]));
            if(Paint.colorLayer[Engine.px][Engine.py] == '`') Engine.setColor(Engine.getColor(Paint.backgroundLayer[Engine.px][Engine.py]), LIGHT_GRAY);
            Engine.tp(Engine.px, Engine.py);
            std::cout << Engine.convertCharToUTF(Paint.characterLayer[Engine.px][Engine.py]);
        }
        else if(Engine.py == 25 && Engine.px < 2)
        {
            Engine.tp(0, 25);
            Engine.setColor(DARK_BLUE, GRAY);
            std::cout << Engine.convertCharToUTF(Paint.tools[1]) << Engine.convertCharToUTF(Paint.tools[1]);
            Paint.displayChar();
        }
        else if(Engine.py == 25 && Engine.px > 1 && Engine.px < 36)
        {
            Engine.setColor(Engine.getColor(Paint.toolbar[Engine.px - 2]), Engine.getColor(Paint.toolbar[Engine.px - 2]));
            if(Paint.toolbar[Engine.px - 2] == '`') Engine.setColor(GRAY, LIGHT_GRAY);
            Engine.tp(Engine.px, 25);
            if(Paint.toolbar[Engine.px - 2] == '`') printf("`");
            else std::cout << Engine.convertCharToUTF(Paint.currentChar);
        }
        else if(Engine.py == 25 && Engine.px > 38 && Engine.px < 71)
        {
            Engine.setColor(BLACK, Engine.getColor(Paint.toolbar[Engine.px - 39]));
            Engine.tp(Engine.px, 25);
            std::cout << Engine.convertCharToUTF(Paint.tools[2]);
        }
        else if(Engine.py == 25 && Engine.px > 70 && Engine.px < 73)
        {
            Engine.setColor(GRAY, LIGHT_GRAY);
            Engine.tp(Engine.px, 25);
            printf("`");
        }
        else if(Engine.py == 25 && Engine.px > 73 && Engine.px < 79)
        {
            Engine.tp(Engine.px, Engine.py); Engine.setColor(BLACK, WHITE);
            if(Engine.px < 78) std::cout << Engine.convertCharToUTF(Paint.tools[Engine.px - 74]);
            else printf("~");
        }

        /*mYmX*/ // Changing color of char that mouse is in
        if(Engine.my < 25 && Engine.mx < 80)
        {
            Engine.setColor(Paint.mainColor, Paint.secondaryColor);
            Engine.tp(Engine.mx, Engine.my);
            printf("X");
        }
        else if(Engine.my == 25 && Engine.mx < 2)
        {
            Engine.tp(0, 25);
            Engine.setColor(BLUE, LIGHT_GRAY);
            std::cout << Engine.convertCharToUTF(Paint.tools[1]) << Engine.convertCharToUTF(Paint.tools[1]);
            Paint.displayChar();
        }
        else if(Engine.my == 25 && Engine.mx > 1 && Engine.mx < 36)
        {
            Engine.tp(Engine.mx, Engine.my);
            Engine.setColor(Engine.getColor(Paint.toolbar[Engine.mx - 2]), Paint.mainColor);
            if(Paint.toolbar[Engine.mx - 2] == '`')Engine.setColor(GRAY, Paint.mainColor);
            printf("X");
        }
        else if(Engine.my == 25 && Engine.mx > 38 && Engine.mx < 71)
        {
            Engine.tp(Engine.mx, 25);
            Engine.setColor(RED, Engine.getColor(Paint.toolbar[Engine.mx - 39]));
            std::cout << Engine.convertCharToUTF(Paint.tools[2]);
        }
        else if(Engine.my == 25 && Engine.mx > 70 && Engine.mx < 73)
        {
            Engine.tp(Engine.mx, 25);
            Engine.setColor(RED, LIGHT_GRAY);
            printf("`");
        }
        else if(Engine.my == 25 && Engine.mx > 73 && Engine.mx < 79)
        {
            Engine.tp(Engine.mx, Engine.my); Engine.setColor(RED, WHITE);
            if(Engine.px < 78) std::cout << Engine.convertCharToUTF(Paint.tools[Engine.mx - 74]);
            else printf("~");
        }
    }
    else menu(); // run menu if it should be on
}

void menu()
{
    char choice; // This variable stores information about clicked key
    std::string name; // This variable gets the name from user, and then converts it to the image ID

    if(Paint.menu_Drawed == false)
    {
        // Shows menu
        Engine.clear(); Engine.setColor(BLACK, WHITE);
        Engine.tp(2, 1); printf("Wer-Dar Paint v - 1.10_2");
        Engine.tp(31, 1); printf("What would you like to do?");
        Engine.setColor(WHITE, WHITE);
        Engine.tp(27, 0); printf("  ");
        Engine.tp(27, 1); printf("  ");
        Engine.tp(27, 2); printf("  ");
        Engine.tp(0, 3); printf("%80i");
        Engine.tp(0, 0);

        // This shows text for buttons
        Engine.setColor(DARK_BLUE, BLACK);
        Engine.tp(2, 5); printf("                 ");
        Engine.tp(2, 6); printf("  Load disk.wdd  ");
        Engine.tp(2, 7); printf("                 ");

        Engine.setColor(DARK_GREEN, BLACK);
        Engine.tp(21, 5); printf("                    ");
        Engine.tp(21, 6); printf("  Save as disk.wdd  ");
        Engine.tp(21, 7); printf("                    ");

        Engine.setColor(DARK_AQUA, BLACK);
        Engine.tp(44, 5); printf("                ");
        Engine.tp(44, 6); printf("  Load picture  ");
        Engine.tp(44, 7); printf("                ");

        Engine.setColor(DARK_RED, BLACK);
        Engine.tp(62, 5); printf("                ");
        Engine.tp(62, 6); printf("  Save Picture  ");
        Engine.tp(62, 7); printf("                ");

        Engine.setColor(PURPLE, BLACK);
        Engine.tp(2, 9); printf("                   ");
        Engine.tp(2, 10); printf("  Save as picture  ");
        Engine.tp(2, 11); printf("                   ");

        Engine.setColor(DARK_YELLOW, BLACK);
        Engine.tp(58, 9); printf("                    ");
        Engine.tp(58, 10); printf("  Make new picutre  ");
        Engine.tp(58, 11); printf("                    ");

        Engine.setColor(WHITE, WHITE);
        Engine.tp(0, 13); printf("%80d");
    }
    Paint.menu_Drawed = true; // Says that menu was drawn
    
    // show image/text that was before mouse hover
    if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 2 && Engine.px <= 18 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 2 || Engine.mx > 18))
    {
        Engine.setColor(DARK_BLUE, BLACK);
        Engine.tp(2, 5); printf("                 ");
        Engine.tp(2, 6); printf("  Load disk.wdd  ");
        Engine.tp(2, 7); printf("                 ");
    }
    else if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 21 && Engine.px <= 41 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 21 || Engine.mx > 41))
    {
        Engine.setColor(DARK_GREEN, BLACK);
        Engine.tp(21, 5); printf("                    ");
        Engine.tp(21, 6); printf("  Save as disk.wdd  ");
        Engine.tp(21, 7); printf("                    ");
    }
    else if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 44 && Engine.px <= 60 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 44 || Engine.mx > 60))
    {
        Engine.setColor(DARK_AQUA, BLACK);
        Engine.tp(44, 5); printf("                ");
        Engine.tp(44, 6); printf("  Load picture  ");
        Engine.tp(44, 7); printf("                ");
    }
    else if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 62 && Engine.px <= 77 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 62 || Engine.mx > 77))
    {
        Engine.setColor(DARK_RED, BLACK);
        Engine.tp(62, 5); printf("                ");
        Engine.tp(62, 6); printf("  Save Picture  ");
        Engine.tp(62, 7); printf("                ");
    }
    else if(Engine.py >= 9 && Engine.py <= 11 && Engine.px >= 2 && Engine.px <= 20 && (Engine.my < 9 || Engine.my > 11 || Engine.mx < 2 || Engine.mx > 20))
    {
        Engine.setColor(PURPLE, BLACK);
        Engine.tp(2, 9); printf("                   ");
        Engine.tp(2, 10); printf("  Save as picture  ");
        Engine.tp(2, 11); printf("                   ");
    }
    else if(Engine.py >= 9 && Engine.py <= 11 && Engine.px >= 58 && Engine.px <= 78 && (Engine.my < 9 || Engine.my > 11 || Engine.mx < 58 || Engine.mx > 78))
    {
        Engine.setColor(DARK_YELLOW, BLACK);
        Engine.tp(58, 9); printf("                    ");
        Engine.tp(58, 10); printf("  Make new picutre  ");
        Engine.tp(58, 11); printf("                    ");
    }

    // show image/text ::onHover
    if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 2 && Engine.mx <= 18)
    {
        Engine.setColor(BLUE, BLACK);
        Engine.tp(2, 5); printf("                 ");
        Engine.tp(2, 6); printf("  Load disk.wdd  ");
        Engine.tp(2, 7); printf("                 ");
        if(Engine.doClick)
        {
            // And if clicked, turn off menu, set doClick to correct value, and does:
            Paint.doMenu = false;
            Engine.doClick = true;
            // loads Disk.wdd and draws painting.
            Paint.loadDisk();
            Paint.draw();
        } 
    }
    else if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 21 && Engine.mx <= 41)
    {
        Engine.setColor(GREEN, BLACK);
        Engine.tp(21, 5); printf("                    ");
        Engine.tp(21, 6); printf("  Save as disk.wdd  ");
        Engine.tp(21, 7); printf("                    ");

        if(Engine.doClick)
        {
            Paint.doMenu = false;
            Engine.doClick = true;
            // saves Disk.wdd and draws painting.
            Paint.saveDisk();
            Paint.draw();
        }
    }
    else if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 44 && Engine.mx <= 60)
    {
        Engine.setColor(AQUA, BLACK);
        Engine.tp(44, 5); printf("                ");
        Engine.tp(44, 6); printf("  Load picture  ");
        Engine.tp(44, 7); printf("                ");

        if(Engine.doClick)
        {
            Paint.doMenu = false;
            Engine.doClick = false;

            // Asks how it should get image
            Engine.tp(2, 15);
            Engine.setColor(BLACK, DARK_AQUA);
            printf("Click key:\n a/A. Get by name\n b/B. Get by Id\n c/C. Search via Image Chooser\n Other key. Cancel");

            Engine.tp(2, 19);
            Engine.setColor(BLACK, AQUA);
            choice = getch();

            switch(choice)
            {
                case 'a':
                case 'A':
                    // Ask from name
                    printf("Enter here: ");
                    std::cin >> name;
                    Paint.currentId = Engine.getId(name);
                break;
                case 'b':
                case 'B':
                    // Ask from id
                    printf("Enter here: ");
                    std::cin >> Paint.currentId;
                break;
                case 'c':
                case 'C':
                    // Ask from imageChooser
                    Paint.currentId = Paint.imageChooser();
                break;
            }

            if(Paint.currentId >= images.size() || Paint.currentId < 0) Paint.currentId = 0; // If somehow user manages to overflow currentId, it resets it

            // Write canvas Layers from images[P.cID]
            for(short whatLine = 0; whatLine < 25;  whatLine++)
            {
                for(short whatChar = 0; whatChar < 80;  whatChar++)
                {
                    Paint.backgroundLayer[whatChar][whatLine] = images[Paint.currentId].backgroundLayer[whatChar][whatLine];
                    Paint.colorLayer[whatChar][whatLine] = images[Paint.currentId].colorLayer[whatChar][whatLine];
                    Paint.characterLayer[whatChar][whatLine] = images[Paint.currentId].characterLayer[whatChar][whatLine];
                }
            }
            Paint.draw();
        }
    }
    else if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 62 && Engine.mx <= 77)
    {
        Engine.setColor(RED, BLACK);
        Engine.tp(62, 5); printf("                ");
        Engine.tp(62, 6); printf("  Save Picture  ");
        Engine.tp(62, 7); printf("                ");

        if(Engine.doClick)
        {
            // It saves current image to images.layers[x][y]
            Paint.doMenu = false;
            Engine.doClick = true;

            // Saves current picture into images[P.cID]
            for(short whatLine = 0; whatLine < 25;  whatLine++)
            {
                for(short whatChar = 0; whatChar < 80;  whatChar++)
                {
                    images[Paint.currentId].backgroundLayer[whatChar][whatLine] = Paint.backgroundLayer[whatChar][whatLine];
                    images[Paint.currentId].colorLayer[whatChar][whatLine] = Paint.colorLayer[whatChar][whatLine];
                    images[Paint.currentId].characterLayer[whatChar][whatLine] = Paint.characterLayer[whatChar][whatLine];
                }
            }
            Paint.draw();
        }
    }
    
    else if(Engine.my >= 9 && Engine.my <= 11 && Engine.mx >= 2 && Engine.mx <= 20)
    {
        Engine.setColor(PINK, BLACK);
        Engine.tp(2, 9); printf("                   ");
        Engine.tp(2, 10); printf("  Save as picture  ");
        Engine.tp(2, 11); printf("                   ");

        if(Engine.doClick)
        {
            Paint.doMenu = false;
            Engine.doClick = false;

            // Almost the same as in Load as
            Engine.tp(2, 15); Engine.setColor(BLACK, PURPLE);
            printf("Click key:\n a/A. get by name\n b/B. get by Id\n c/C. Search via Image Chooser\n Other key. Cancel");

            Engine.setColor(BLACK, PINK);

            choice = getch();

            switch(choice)
            {
                case 'a':
                case 'A':
                    printf("Enter here: ");
                    std::cin >> name;
                    Paint.currentId = Engine.getId(name);
                break;
                case 'b':
                case 'B':
                    printf("Enter here: ");
                    std::cin >> Paint.currentId;
                break;
                case 'c':
                case 'C':
                    Paint.currentId = Paint.imageChooser();
                break;
            }
            if(Paint.currentId >= images.size() || Paint.currentId < 0) Paint.currentId = 0;

            for(short whatLine = 0; whatLine < 25;  whatLine++)
            {
                for(short whatChar = 0; whatChar < 80;  whatChar++)
                {
                    images[Paint.currentId].backgroundLayer[whatChar][whatLine] = Paint.backgroundLayer[whatChar][whatLine];
                    images[Paint.currentId].colorLayer[whatChar][whatLine] = Paint.colorLayer[whatChar][whatLine];
                    images[Paint.currentId].characterLayer[whatChar][whatLine] = Paint.characterLayer[whatChar][whatLine];
                }
            }
            Paint.draw();
        }
    }
    else if(Engine.my >= 9 && Engine.my <= 11 && Engine.mx >= 58 && Engine.mx <= 78)
    {
        Engine.setColor(YELLOW, BLACK);
        Engine.tp(58, 9); printf("                    ");
        Engine.tp(58, 10); printf("  Make new picutre  ");
        Engine.tp(58, 11); printf("                    ");
        
        if(Engine.doClick)
        {
            // Makes new picture
            Paint.doMenu = false;
            Engine.doClick = false;
            Paint.currentId = images.size(); // Sets currentId to the new picture

            images.push_back(image()); // Creates new picture

            Engine.tp(2, 15); 
            Engine.setColor(BLACK, DARK_YELLOW); printf("Set name of this picture: "); // user sets the name of new picture
            std::cin >> images[Paint.currentId].name; // Asks for writing name

            Engine.setColor(BLACK, YELLOW);
            Engine.tp(2, 16); printf("Id of this picture is: %i", Paint.currentId); // Couts currentId
            Sleep(750); // Waits 0.75ms and sets values and then draws canvas

            for(short whatLine = 0; whatLine < 25;  whatLine++)
            {
                for(short whatChar = 0; whatChar < 80;  whatChar++)
                {
                    Paint.backgroundLayer[whatChar][whatLine] = images[Paint.currentId].backgroundLayer[whatChar][whatLine];
                    Paint.colorLayer[whatChar][whatLine] = images[Paint.currentId].colorLayer[whatChar][whatLine];
                    Paint.characterLayer[whatChar][whatLine] = images[Paint.currentId].characterLayer[whatChar][whatLine];
                }
            }
            Paint.draw();
        }
    }
}