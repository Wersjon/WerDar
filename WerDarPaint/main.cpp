#include "mouser.hpp"

/*
####################################################################################################
##                                                                                                ##
##  Wer-Dar Paint v - 1.8 by Jakub Sobacki                                                        ##
##  Few things before you get started                                                             ##
##  This app requires special treatment for cmd, it's written when app is opened (main function)  ##
##                                                                                                ##
####################################################################################################
*/

void keypressed(char input);
void clicked();
void doubleClicked();
void moved();
void menu();

int main()
{
    SetConsoleOutputCP(852); //Setting CodePage to 852, to have all special (coded) characters
    SetConsoleTitleA("Wer-Dar Paint v - 1.8");
    Engine.hideCursor();

    Engine.loadfile("wdplogo"); //Loading wdplogo.wdi (read) / legacy
    for(short i = 0; i < 25; i++) //If KeyBoardHIT(), end while and start program (for 2,5 seconds).
    {
        if(kbhit()) 
        {
            getch();
            break;
        }
        Sleep(100);
    }

    Engine.clear(); //Clears screen / system("cls") is broken, and slower.
    Engine.loadfile("load");

    /*informational text for user */
    Engine.tp(1, 1); Engine.setColor(0, 15); printf("Edit modes: Turn off Quick edit mode;");
    Engine.setColor(12, 15); printf(" T");
    Engine.setColor(0, 15); printf("urn off insert mode; Turn rest on;");
    Engine.tp(1, 2); printf("Selecting Text: Everything off;");
    Engine.tp(1, 3); printf("Layout{");
    Engine.tp(1, 4); printf("- For buffer: Width: 80+; Height: 50+"); Engine.setColor(12, 15); printf(";"); Engine.setColor(0, 15);
    Engine.tp(1, 5); printf("- For window: Width: 80+; Height: 26+"); Engine.setColor(12, 15); printf(";"); Engine.setColor(0, 15);
    Engine.tp(1, 6); printf("- Turn off wrapping text on resize}");
    Engine.tp(1, 7); printf("Terminal(Windows 10 - experimental): ");
    Engine.setColor(12, 15); printf("Tu");
    Engine.setColor(0, 15); printf("rn off: Disable Scroll Forward option;");
    Engine.tp(1, 9); printf("Click any key to start drawing.");
    Engine.tp(1, 10); Engine.setColor(0, 12); printf("DON'T MOUSE OVER RIGHT BOTTOM CORNER");
    images.push_back(image());
    getch(); //awaits for input from user

    short whatChar = 0, whatLine = 0;
    while(whatLine < 25)
    {
        while(whatChar < 80)
        {
            //Sets default value for Layers 
            Paint.backgroundLayer[whatChar][whatLine] = '#';
            Paint.colorLayer[whatChar][whatLine] = '#';
            Paint.characterLayer[whatChar][whatLine] = '#';
            whatChar++;
        }
        whatChar = 0;
        whatLine++;
    }
    Paint.draw();
    //mouse(); is like loop in arduino, you can't leave it ;)
    Engine.mouse(clicked, doubleClicked, moved, keypressed);
    return 0;
}

void keypressed(char input)
{
    
}

void clicked()
{
    if(Paint.doMenu == false)
    {
        /* if menu isn't ON, do those: */
        /* the default template is this:
        # if(Engine.my <= lowest_my && Engine.mx >= bigest_my && Engine.mx <= lowest_mx && Engine.mx >= bigest_mx)
        # {
        #     //Do onClick   
        # }
        */
        if(Engine.my < 25 && Engine.mx < 80)
        {
            Engine.tp(Engine.mx, Engine.my);
            printf("%c", Paint.currentChar);
            Paint.backgroundLayer[Engine.mx][Engine.my] = Engine.whatChar(Paint.mainColor);
            Paint.colorLayer[Engine.mx][Engine.my] = Engine.whatChar(Paint.secondaryColor);
            Paint.characterLayer[Engine.mx][Engine.my] = Paint.currentChar;
        }
        else if(Engine.my == 25 && Engine.mx > 1 && Engine.mx < 36)
        {
            if(Paint.mainColor == 16 && Paint.secondaryColor == 16 && Engine.mx < 34) Paint.currentChar = Paint.previousChar;    
            else if(Engine.mx >= 34 && Paint.secondaryColor == 16) Paint.previousChar = Paint.currentChar;
            Paint.mainColor = (Engine.mx - 2) / 2;
            if((Engine.mx - 2) / 2 > (Engine.mx - 1) / 2) Paint.mainColor = (Engine.mx - 1) / 2;
            if(Paint.secondaryColor == 16 && Paint.mainColor == 16) Paint.currentChar = '#';
        }
        else if(Engine.my == 25 && Engine.mx > 38 && Engine.mx < 73)
        {     
            if(Paint.mainColor == 16 && Paint.secondaryColor == 16 && Engine.mx < 71) Paint.currentChar = Paint.previousChar;    
            else if(Engine.mx >= 71 && Paint.mainColor == 16) Paint.previousChar = Paint.currentChar;
            Paint.secondaryColor = (Engine.mx - 38) / 2;
            if((Engine.mx - 38) / 2 > (Engine.mx - 49) / 2) Paint.secondaryColor = (Engine.mx - 39) / 2;
            if(Paint.mainColor == 16 && Paint.secondaryColor == 16) Paint.currentChar = '#';
        }
        else if(Engine.my == 25 && Engine.mx > 73 && Engine.mx < 78)
        {
            Paint.currentChar = Paint.tools[Engine.mx - 74];
            Paint.displayChar();
        }
        else if(Engine.my == 25 && Engine.mx < 2)
        {
            Paint.doMenu = true;
            Paint.menu_Drawed = false;
        }
    }
    else menu(); //if menu is on, run menu :v
}

void doubleClicked()
{
    Engine.doClick = true; //Prevents from d_click bug
}

void moved()
{
    if(Engine.doClick) clicked();

    if(Paint.doMenu == false)
    {
        /*pYpX*/ //previous y and previous x are the previous location of mouse; template is the same for click but with .px and .py
        if(Engine.py < 25 && Engine.px < 80)
        {
            Engine.setColor(Engine.whatColor(Paint.backgroundLayer[Engine.px][Engine.py]), Engine.whatColor(Paint.colorLayer[Engine.px][Engine.py]));
            if(Paint.colorLayer[Engine.px][Engine.py] == '#') Engine.setColor(Engine.whatColor(Paint.backgroundLayer[Engine.px][Engine.py]), 7);
            Engine.tp(Engine.px, Engine.py);
            printf("%c", Paint.characterLayer[Engine.px][Engine.py]);
        }
        else if(Engine.py == 25 && Engine.px < 2)
        {
            Engine.tp(0, 25);
            Engine.setColor(1, 8);
            printf("%c%c", Paint.tools[1], Paint.tools[1]);
            Paint.displayChar();
        }
        else if(Engine.py == 25 && Engine.px > 1 && Engine.px < 36)
        {
            Engine.setColor(Engine.whatColor(Paint.toolbar[Engine.px - 2]), Engine.whatColor(Paint.toolbar[Engine.px - 2]));
            if(Paint.toolbar[Engine.px - 2] == '#') Engine.setColor(8, 7);
            Engine.tp(Engine.px, 25);
            if(Paint.toolbar[Engine.px - 2] == '#') printf("#");
            else printf("%c", Paint.currentChar);
        }
        else if(Engine.py == 25 && Engine.px > 38 && Engine.px < 71)
        {
            Engine.setColor(0, Engine.whatColor(Paint.toolbar[Engine.px - 39]));
            Engine.tp(Engine.px, 25);
            printf("%c", Paint.tools[2]);
        }
        else if(Engine.py == 25 && Engine.px > 70 && Engine.px < 73)
        {
            Engine.setColor(8, 7);
            Engine.tp(Engine.px, 25);
            printf("#");
        }
        else if(Engine.py == 25 && Engine.px > 73 && Engine.px < 78)
        {
            Engine.tp(Engine.px, Engine.py); Engine.setColor(0, 15);
            printf("%c", Paint.tools[Engine.px - 74]);
        }

        /*mYmX*/
        if(Engine.my < 25 && Engine.mx < 80)
        {
            Engine.setColor(Paint.mainColor, Paint.secondaryColor);
            Engine.tp(Engine.mx, Engine.my);
            printf("X");
        }
        else if(Engine.my == 25 && Engine.mx < 2)
        {
            Engine.tp(0, 25);
            Engine.setColor(9, 7);
            printf("%c%c", Paint.tools[1], Paint.tools[1]);
            Paint.displayChar();
        }
        else if(Engine.my == 25 && Engine.mx > 1 && Engine.mx < 36)
        {
            Engine.tp(Engine.mx, Engine.my);
            Engine.setColor(Engine.whatColor(Paint.toolbar[Engine.mx - 2]), Paint.mainColor);
            if(Paint.toolbar[Engine.mx - 2] == '#')Engine.setColor(8, Paint.mainColor);
            printf("X");
        }
        else if(Engine.my == 25 && Engine.mx > 38 && Engine.mx < 71)
        {
            Engine.tp(Engine.mx, 25);
            Engine.setColor(12, Engine.whatColor(Paint.toolbar[Engine.mx - 39]));
            printf("%c", Paint.tools[2]);
        }
        else if(Engine.my == 25 && Engine.mx > 70 && Engine.mx < 73)
        {
            Engine.tp(Engine.mx, 25);
            Engine.setColor(12, 7);
            printf("#");
        }
        else if(Engine.my == 25 && Engine.mx > 73 && Engine.mx < 78)
        {
            Engine.tp(Engine.mx, Engine.my); Engine.setColor(12, 15);
            printf("%c", Paint.tools[Engine.mx - 74]);
        }
    }
    else menu();
}
void menu()
{
    char wybor;
    short whatChar = 0, whatLine = 0;
    std::string name;

    if(Paint.menu_Drawed == false)
    {
        //Shows menu
        Engine.clear(); Engine.setColor(0, 15);
        Engine.tp(2, 1); printf("Wer-Dar Paint v - 1.8");
        Engine.tp(27, 1); printf("What would you like to do?");
        Engine.setColor(15, 15);
        Engine.tp(23, 0); printf("  ");
        Engine.tp(23, 1); printf("  ");
        Engine.tp(23, 2); printf("  ");
        Engine.tp(0, 3); printf("%80d");
        Engine.tp(0, 0);

        //Show image / text for buttons
        Engine.setColor(1, 0);
        Engine.tp(2, 5); printf("                 ");
        Engine.tp(2, 6); printf("  Load disk.wdd  ");
        Engine.tp(2, 7); printf("                 ");

        Engine.setColor(2, 0);
        Engine.tp(21, 5); printf("                    ");
        Engine.tp(21, 6); printf("  Save as disk.wdd  ");
        Engine.tp(21, 7); printf("                    ");

        Engine.setColor(3, 0);
        Engine.tp(44, 5); printf("                ");
        Engine.tp(44, 6); printf("  Load picture  ");
        Engine.tp(44, 7); printf("                ");

        Engine.setColor(4, 0);
        Engine.tp(62, 5); printf("                ");
        Engine.tp(62, 6); printf("  Save Picture  ");
        Engine.tp(62, 7); printf("                ");

        Engine.setColor(5, 0);
        Engine.tp(2, 9); printf("                   ");
        Engine.tp(2, 10); printf("  Save as picture  ");
        Engine.tp(2, 11); printf("                   ");

        Engine.setColor(6, 0);
        Engine.tp(58, 9); printf("                    ");
        Engine.tp(58, 10); printf("  Make new picutre  ");
        Engine.tp(58, 11); printf("                    ");

        Engine.setColor(15, 15);
        Engine.tp(0, 13); printf("%80d");
    }
    Paint.menu_Drawed = true;
    
    if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 2 && Engine.px <= 18 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 2 || Engine.mx > 18))
    {
        //show previous image/text
        Engine.setColor(1, 0);
        Engine.tp(2, 5); printf("                 ");
        Engine.tp(2, 6); printf("  Load disk.wdd  ");
        Engine.tp(2, 7); printf("                 ");
    }
    else if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 21 && Engine.px <= 41 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 21 || Engine.mx > 41))
    {
        Engine.setColor(2, 0);
        Engine.tp(21, 5); printf("                    ");
        Engine.tp(21, 6); printf("  Save as disk.wdd  ");
        Engine.tp(21, 7); printf("                    ");
    }
    else if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 44 && Engine.px <= 60 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 44 || Engine.mx > 60))
    {
        Engine.setColor(3, 0);
        Engine.tp(44, 5); printf("                ");
        Engine.tp(44, 6); printf("  Load picture  ");
        Engine.tp(44, 7); printf("                ");
    }
    else if(Engine.py >= 5 && Engine.py <= 7 && Engine.px >= 62 && Engine.px <= 77 && (Engine.my < 5 || Engine.my > 7 || Engine.mx < 62 || Engine.mx > 77))
    {
        Engine.setColor(4, 0);
        Engine.tp(62, 5); printf("                ");
        Engine.tp(62, 6); printf("  Save Picture  ");
        Engine.tp(62, 7); printf("                ");
    }
    else if(Engine.py >= 9 && Engine.py <= 11 && Engine.px >= 2 && Engine.px <= 20 && (Engine.my < 9 || Engine.my > 11 || Engine.mx < 2 || Engine.mx > 20))
    {
        Engine.setColor(5, 0);
        Engine.tp(2, 9); printf("                   ");
        Engine.tp(2, 10); printf("  Save as picture  ");
        Engine.tp(2, 11); printf("                   ");
    }
    else if(Engine.py >= 9 && Engine.py <= 11 && Engine.px >= 58 && Engine.px <= 78 && (Engine.my < 9 || Engine.my > 11 || Engine.mx < 58 || Engine.mx > 78))
    {
        Engine.setColor(6, 0);
        Engine.tp(58, 9); printf("                    ");
        Engine.tp(58, 10); printf("  Make new picutre  ");
        Engine.tp(58, 11); printf("                    ");
    }

    if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 2 && Engine.mx <= 18)
    {
        //show image/text ::onHover
        Engine.setColor(9, 0);
        Engine.tp(2, 5); printf("                 ");
        Engine.tp(2, 6); printf("  Load disk.wdd  ");
        Engine.tp(2, 7); printf("                 ");
        if(Engine.doClick)
        {
            Paint.doMenu = false;
            Engine.doClick = true;
            Paint.loadDisk();
            Paint.draw();
        } 
    }
    else if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 21 && Engine.mx <= 41)
    {
        Engine.setColor(10, 0);
        Engine.tp(21, 5); printf("                    ");
        Engine.tp(21, 6); printf("  Save as disk.wdd  ");
        Engine.tp(21, 7); printf("                    ");
        if(Engine.doClick)
        {
            Paint.doMenu = false;
            Engine.doClick = true;
            Paint.saveDisk();
            Paint.draw();
        }
    }
    else if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 44 && Engine.mx <= 60)
    {
        Engine.setColor(11, 0);
        Engine.tp(44, 5); printf("                ");
        Engine.tp(44, 6); printf("  Load picture  ");
        Engine.tp(44, 7); printf("                ");
        if(Engine.doClick)
        {
            Paint.doMenu = false;
            Engine.doClick = false;

            Engine.tp(2, 15);
            Engine.setColor(0, 3);
            printf("Click key:\n a/A. get by name\n b/B. get by Id");
            wybor = getch();

            Engine.tp(2, 19);
            Engine.setColor(0, 11);
            printf("Enter here: ");
            if(wybor == 'a' || wybor == 'A') //If choice is equal to a/A, it searches for the Id
            {
                cin >> name;
                Paint.currentId = Engine.getId(name);
            }
            else if(wybor == 'b' || wybor == 'B') cin >> Paint.currentId; //Else if choice is equal to b/B, it simply gets the name

            if(Paint.currentId >= images.size() || Paint.currentId < 0) Paint.currentId = 0;

            whatLine = 0; whatChar = 0;
            while(whatLine < 25)
            {
                while(whatChar < 80)
                {
                    Paint.backgroundLayer[whatChar][whatLine] = images[Paint.currentId].backgroundLayer[whatChar][whatLine];
                    Paint.colorLayer[whatChar][whatLine] = images[Paint.currentId].colorLayer[whatChar][whatLine];
                    Paint.characterLayer[whatChar][whatLine] = images[Paint.currentId].characterLayer[whatChar][whatLine];
                    whatChar++;
                }
                whatChar = 0;
                whatLine++;
            }
            Paint.draw();
        }
    }
    else if(Engine.my >= 5 && Engine.my <= 7 && Engine.mx >= 62 && Engine.mx <= 77)
    {
        Engine.setColor(12, 0);
        Engine.tp(62, 5); printf("                ");
        Engine.tp(62, 6); printf("  Save Picture  ");
        Engine.tp(62, 7); printf("                ");
        if(Engine.doClick)
        {
            //It saves current image to images.layers[x][y]
            Paint.doMenu = false;
            Engine.doClick = true;
            whatLine = 0; whatChar = 0;
            while(whatLine < 25)
            {
                while(whatChar < 80)
                {
                    images[Paint.currentId].backgroundLayer[whatChar][whatLine] = Paint.backgroundLayer[whatChar][whatLine];
                    images[Paint.currentId].colorLayer[whatChar][whatLine] = Paint.colorLayer[whatChar][whatLine];
                    images[Paint.currentId].characterLayer[whatChar][whatLine] = Paint.characterLayer[whatChar][whatLine];
                    whatChar++;
                }
                whatChar = 0;
                whatLine++;
            }
            Paint.draw();
        }
    }
    else if(Engine.my >= 9 && Engine.my <= 11 && Engine.mx >= 2 && Engine.mx <= 20)
    {
        Engine.setColor(13, 0);
        Engine.tp(2, 9); printf("                   ");
        Engine.tp(2, 10); printf("  Save as picture  ");
        Engine.tp(2, 11); printf("                   ");
        if(Engine.doClick)
        {
            Paint.doMenu = false;
            Engine.doClick = false;

            Engine.tp(2, 15); Engine.setColor(0, 5);
            printf("Click key:\n a/A. get by name\n b/B. get by Id");
            wybor = getch();

            Engine.setColor(0, 13);
            Engine.tp(2, 19); printf("Enter here: ");
            if(wybor == 'a' || wybor == 'A')
            {
                cin >> name;
                Paint.currentId = Engine.getId(name);
            }
            else if(wybor == 'b' || wybor == 'B') cin >> Paint.currentId;

            if(Paint.currentId >= images.size() || Paint.currentId < 0) Paint.currentId = 0;

            whatLine = 0; whatChar = 0;
            while(whatLine < 25)
            {
                while(whatChar < 80)
                {
                    images[Paint.currentId].backgroundLayer[whatChar][whatLine] = Paint.backgroundLayer[whatChar][whatLine];
                    images[Paint.currentId].colorLayer[whatChar][whatLine] = Paint.colorLayer[whatChar][whatLine];
                    images[Paint.currentId].characterLayer[whatChar][whatLine] = Paint.characterLayer[whatChar][whatLine];
                    whatChar++;
                }
                whatChar = 0;
                whatLine++;
            }
            Paint.draw();
        }
    }
    else if(Engine.my >= 9 && Engine.my <= 11 && Engine.mx >= 58 && Engine.mx <= 78)
    {
        Engine.setColor(14, 0);
        Engine.tp(58, 9); printf("                    ");
        Engine.tp(58, 10); printf("  Make new picutre  ");
        Engine.tp(58, 11); printf("                    ");
        
        if(Engine.doClick)
        {
            //Makes new picture
            Paint.doMenu = false;
            Engine.doClick = false;
            Paint.currentId = images.size();

            images.push_back(image());

            Engine.tp(2, 15); 
            Engine.setColor(0, 6); printf("Set name of this picture: ");
            cin >> images[Paint.currentId].name;

            Engine.setColor(0, 14);
            Engine.tp(2, 16); printf("Id of this picture is: %s", Engine.getId(images[Paint.currentId].name));
            Sleep(750);

            whatLine = 0; whatChar = 0;
            while(whatLine < 25)
            {
                while(whatChar < 80)
                {
                    if(images[Paint.currentId].backgroundLayer[whatChar][whatLine] != '#')
                    {
                        Paint.backgroundLayer[whatChar][whatLine] = images[Paint.currentId].backgroundLayer[whatChar][whatLine];
                        Paint.colorLayer[whatChar][whatLine] = images[Paint.currentId].colorLayer[whatChar][whatLine];
                        Paint.characterLayer[whatChar][whatLine] = images[Paint.currentId].characterLayer[whatChar][whatLine];
                    }
                    whatChar++;
                }
                whatChar = 0;
                whatLine++;
            }
            Paint.draw();
        }
    }
}