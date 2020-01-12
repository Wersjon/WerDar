#include "mouser.hpp"

using namespace std;

/*

// Wer-Dar Paint v-1.5 by Jakub Sobacki
// Few things before you get started
// This app requires special treatment for cmd, it's written when app is opened (main function)

*/

/* Layers for painting */

/* Declaration for functions */
void keypressed(char input);
void clicked();
void doubleClicked();
void moved();
void menu();

int main()
{
    /* Declaration of variables */
    short i = 0;

    SetConsoleOutputCP(852); //Setting CodePage to 852, to have all characters
    SetConsoleTitleA("Wer-Dar Paint"); //Setting title
    Engine.hideCursor(); //Hiding cursor

    Engine.loadfile("wdplogo"); //Loading wdplogo.wdi (read)
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

    Engine.clear(); //Clears screen / system("cls") is broken, and slower.
    Engine.loadfile("load");

    /*informational text for user */
    Engine.tp(1, 1); Engine.setColor(0, 15); printf("Edit modes: Turn off Quick edit mode;"); //teleports cursor to 1, 1;  Sets color for text; and printfs the text
    Engine.setColor(12, 15); printf(" T");
    Engine.setColor(0, 15); printf("urn off insert mode; Turn rest on;");
    Engine.tp(1, 2); printf("Selecting Text: Everything off;");
    Engine.tp(1, 3); printf("Layout{");
    Engine.tp(1, 4); printf("- For buffer: Width: 80+; Height: 50+");Engine.setColor(12, 15); printf(";"); Engine.setColor(0, 15);
    Engine.tp(1, 5); printf("- For window: Width: 80+; Height: 26+");Engine.setColor(12, 15); printf(";"); Engine.setColor(0, 15);
    Engine.tp(1, 6); printf("- Turn off wrapping text on resize}");
    Engine.tp(1, 7); printf("Terminal(Windows 10 - experimental): ");
    Engine.setColor(12, 15); printf("Tu");
    Engine.setColor(0, 15); printf("rn off: Disable Scroll Forward option;");
    Engine.tp(1, 9); printf("Click any key to start drawing.");
    Engine.tp(1, 10); Engine.setColor(0, 12); printf("DON'T MOUSE OVER RIGHT BOTTOM CORNER");
    images.push_back(image());
    getch(); //awaits for input
    
    i = 2;
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
    /* while to display whole map area */
    Engine.tp(0, 0);
    int i2 = 0; i = 0;
    while(i < 25)
    {
        while(i2 < 80)
        {
            Engine.area[i2][i] = '#';
            Engine.area2[i2][i] = '#';
            Engine.chars[i2][i] = ' ';
            Engine.setColor(Engine.whatColor(Engine.area[i2][i]), Engine.whatColor(Engine.area[i2][i]));
            if(Engine.area[Engine.mx][Engine.my] == '#') Engine.setColor(8, 7);
            printf("%c", Engine.area[i2][i]);
            i2++;
        }
        i2 = 0;
        i++;
    }
    Engine.mouse(clicked, doubleClicked, moved, keypressed);
    return 0;
}

void keypressed(char input)
{
    switch(input)
    {
        case ' ':
            paint.saveDisk();
            Engine.tp(0, 0); Engine.setColor(0, 15); printf("saved");
            Sleep(250);
        break;
    }
}

void clicked()
{
    if(Engine.my < 25 && Engine.mx < 80)
    {
        Engine.tp(Engine.mx, Engine.my);
        Engine.setColor(Engine.currentColor, Engine.secondaryColor);
        if(Engine.area[Engine.mx][Engine.my] == '#') Engine.setColor(8, 7);
        printf("%c", Engine.currentChar);
        Engine.area[Engine.mx][Engine.my] = Engine.whatChar(Engine.currentColor);
        Engine.area2[Engine.mx][Engine.my] = Engine.whatChar(Engine.secondaryColor);
        Engine.chars[Engine.mx][Engine.my] = Engine.currentChar;
    }
    else if(Engine.my == 25 && Engine.mx > 1 && Engine.mx < 36)
    {
        Engine.currentColor = (Engine.mx - 2) / 2;
        if((Engine.mx - 2) / 2 > (Engine.mx - 1) / 2) Engine.currentColor = (Engine.mx - 1) / 2;
    }
    else if(Engine.my == 25 && Engine.mx > 38 && Engine.mx < 71)
    {
        Engine.secondaryColor = (Engine.mx - 38) / 2;
        if((Engine.mx - 38) / 2 > (Engine.mx - 49) / 2) Engine.secondaryColor = (Engine.mx - 39) / 2;
    }
    else if(Engine.my == 25 && Engine.mx > 71 && Engine.mx < 76)
    {
        Engine.currentChar = Engine.tools[Engine.mx - 72];
        paint.displayChar();
    }
    else if(Engine.my == 25 && Engine.mx < 2)
    {
        menu();
    }
}

void doubleClicked()
{
    Engine.doClick = true;
}

void moved()
{
    if(Engine.doClick) clicked();

    /*pYpX*/
    if(Engine.py < 25 && Engine.px < 80)
    {
        Engine.setColor(Engine.whatColor(Engine.area[Engine.px][Engine.py]), Engine.whatColor(Engine.area2[Engine.px][Engine.py]));
        if(Engine.area[Engine.px][Engine.py] == '#') Engine.setColor(8, 7);
        Engine.tp(Engine.px, Engine.py);
        if(Engine.area[Engine.px][Engine.py] == '#') printf("#");
        else printf("%c", Engine.chars[Engine.px][Engine.py]);
    }
    else if(Engine.py == 25 && Engine.px < 2)
    {
        Engine.tp(0, 25);
        Engine.setColor(1, 8);
        printf("%c%c", Engine.tools[1], Engine.tools[1]);
        Engine.px = Engine.mx;
        Engine.py = Engine.my;
        paint.displayChar();
    }
    else if(Engine.py == 25 && Engine.px > 1 && Engine.px < 36)
    {
        Engine.setColor(Engine.whatColor(Engine.toolbar[Engine.px - 2]), Engine.whatColor(Engine.toolbar[Engine.px - 2]));
        if(Engine.toolbar[Engine.px - 2] == '#') Engine.setColor(8, 7);
        Engine.tp(Engine.px, 25);
        if(Engine.toolbar[Engine.px - 2] == '#') printf("#");
        else printf("%c", Engine.currentChar);
    }
    else if(Engine.py == 25 && Engine.px > 38 && Engine.px < 71)
    {
        Engine.setColor(0, Engine.whatColor(Engine.toolbar[Engine.px - 39]));
        Engine.tp(Engine.px, 25);
        printf("%c", Engine.tools[2]);   
    }
    else if(Engine.py == 25 && Engine.px > 71 && Engine.px < 76)
    {
        Engine.tp(Engine.px, Engine.py); Engine.setColor(0, 15);
        printf("%c", Engine.tools[Engine.px - 72]);
    }

    /*mYmX*/
    if(Engine.my < 25 && Engine.mx < 80)
    {
        Engine.setColor(Engine.currentColor, Engine.secondaryColor);
        Engine.tp(Engine.mx, Engine.my);
        printf("X");
    }
    else if(Engine.my == 25 && Engine.mx < 2)
    {
        Engine.tp(0, 25);
        Engine.setColor(9, 7);
        printf("%c%c", Engine.tools[1], Engine.tools[1]);
        paint.displayChar();
    }
    else if(Engine.my == 25 && Engine.mx > 1 && Engine.mx < 36)
    {
        Engine.tp(Engine.mx, Engine.my);
        Engine.setColor(Engine.whatColor(Engine.toolbar[Engine.mx - 2]), Engine.currentColor);
        if(Engine.toolbar[Engine.mx-2] == '#')Engine.setColor(8, Engine.currentColor);
        printf("X");
        paint.displayChar();
    }
    else if(Engine.my == 25 && Engine.mx > 38 && Engine.mx < 71)
    {
        Engine.tp(Engine.mx, Engine.my);
        Engine.setColor(12, Engine.whatColor(Engine.toolbar[Engine.mx - 39]));
        printf("%c", Engine.tools[2]);
        paint.displayChar();
    }
    else if(Engine.my == 25 && Engine.mx > 71 && Engine.mx < 76)
    {
        Engine.tp(Engine.mx, Engine.my); Engine.setColor(12, 15);
        printf("%c", Engine.tools[Engine.mx - 72]);
        paint.displayChar();
    }
    Engine.px = Engine.mx; Engine.py = Engine.my;
}

void menu()
{
    char wybor;
    short i1 = 0, i2 = 0, Id;
    string name;
    Engine.doClick = false;

    Engine.setColor(0, 15); Engine.clear(); Engine.tp(0, 0);
    printf("What would you like to do?\n1. Load disk.wdd\n2. Save as disk.wdd\n3. Load picture\n4. Save picture\n5. Save as picture\n6. Make new picture");
    
    wybor = getch();
    if(wybor == '1') paint.loadDisk();
    else if(wybor == '2') paint.saveDisk();
    else if(wybor == '3')
    {
        printf("\n a/A. get by name\n b/B. get by Id");
        wybor = getch();

        if(wybor == 'a' || wybor == 'A')
        {
            cin >> name;
            Id = Engine.getId(name);
        }
        else if(wybor == 'b' || wybor == 'B') cin >> Id;
        Engine.currentId = Id;

        while(i1 < 25)
        {
            while(i2 < 80)
            {
                Engine.area[i2][i1] = '#';
                Engine.area2[i2][i1] = '#';
                Engine.chars[i2][i1] = '#';
                Engine.setColor(Engine.whatColor(Engine.area[i2][i1]), Engine.whatColor(Engine.area[i2][i1]));
                if(Engine.area[i2][i1] == '#') Engine.setColor(8, 7);
                printf("%c", Engine.area[i2][i1]);
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
                    Engine.area[i2][i1] = images[Id].area[i2][i1];
                    Engine.area2[i2][i1] = images[Id].area2[i2][i1];
                    Engine.chars[i2][i1] = images[Id].chars[i2][i1];
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
                images[Engine.currentId].area[i2][i1] = Engine.area[i2][i1];
                images[Engine.currentId].area2[i2][i1] = Engine.area2[i2][i1];
                images[Engine.currentId].chars[i2][i1] = Engine.chars[i2][i1];
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
            Id = Engine.getId(name);
        }
        else if(wybor == 'b' || wybor == 'B') cin >> Id;
        Engine.currentId = Id;

        
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                images[Engine.currentId].area[i2][i1] = Engine.area[i2][i1];
                images[Engine.currentId].area2[i2][i1] = Engine.area2[i2][i1];
                images[Engine.currentId].chars[i2][i1] = Engine.chars[i2][i1];
                i2++;
            }
            i2 = 0;
            i1++;
        }
    }
    else if(wybor == '6')
    {
        Engine.currentId = images.size();
        images.push_back(image());
        printf("\n Set name of this picture:");
        cin >> images[Engine.currentId].name;
        printf("\n Id of this picture is: %s", images[Engine.currentId].name);

        i1 = 0; i2 = 0;
        while(i1 < 25)
        {
            while(i2 < 80)
            {
                if(images[Id].area[i2][i1] != '#')
                {
                    Engine.area[i2][i1] = images[Id].area[i2][i1];
                    Engine.area2[i2][i1] = images[Id].area2[i2][i1];
                    Engine.chars[i2][i1] = images[Id].chars[i2][i1];
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
                Engine.setColor(Engine.whatColor(Engine.area[i2][i1]), Engine.whatColor(Engine.area[i2][i1]));
                if(Engine.area[i2][i1] == '#') Engine.setColor(8, 7);
                printf("%c", Engine.area[i2][i1]);
                i2++;
            }
            i2 = 0;
            i1++;
        }
    }
    paint.draw();
}