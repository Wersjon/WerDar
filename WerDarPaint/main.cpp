#include "mouser.hpp"

using namespace std;

/*

// Few things before you get started
// This app requires special treatment for cmd, it's written when app is opened (main function)

*/

char area[80][25];

void keypressed(char input);
void clicked();
void doubleClicked();
void moved();
int whatColor(char x);
char whatChar(short x);
void save();
void load();

int px, py;
short currentColor = 15;
char invisible = 177; // Replace invisible with '#' if needed

char toolbar[34] =
{
    '0', '0', '1', '1', '2', '2', '3', '3', '4', '4', '5', '5', '6', '6', '7', '7', '8', '8', '9', '9', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'E', 'E', 'F', 'F', invisible, invisible
};

int main()
{
    load("load");
    setColor(0, 15);
    tp(1,1); printf("Edit modes: Turn off Quick edit mode;");
    setColor(12, 15); printf(" T");
    setColor(0, 15); printf("urn off insert mode; Turn rest on;");
    tp(1,2); printf("Selecting Text: Everything off;");
    tp(1,3); printf("Layout{");
    tp(1,4); printf("- For buffer: Width: 80; Height: 50+;");
    tp(1,5); printf("- For window: Width: 80; Height: 26;");
    tp(1,6); printf("- Turn off wrapping text on resize}");
    tp(1,7); printf("Terminal(Windows 10 - experimental): ");
    setColor(12, 15); printf("Tu");
    setColor(0, 15); printf("rn off: Disable Scroll Forward option;");
    tp(1,9); printf("Click any key to start drawing.");
    tp(1,10); setColor(0, 12); printf("DON'T MOUSE OVER RIGHT BOTTOM CORNER");
    getch();
    int i=0;
    while(i<34)
    {
        tp(i, 25);
        setColor(whatColor(toolbar[i]), whatColor(toolbar[i]));
        if(toolbar[i] == invisible)setColor(8, 7);
        printf("%c", toolbar[i]);
        i++;
    }
    /* while to display whole map area */
    tp(0,0);
    int i2 = 0; i=0;
    while(i<25)
    {
        while(i2<80)
        {
            area[i2][i] = invisible;
            setColor(whatColor(area[i2][i]), whatColor(area[i2][i]));
            if(area[mx][my]==invisible)setColor(8, 7);
            printf("%c", area[i2][i]);
            i2++;
        }
        i2 = 0;
        i++;
    }
    SetConsoleTitleA("Wer-Dar Paint");
    mouse(clicked, doubleClicked, moved, keypressed);
    return 0;
}

void keypressed(char input)
{
    if(input == ']')
    {
        currentColor++;
        if(currentColor == 17)currentColor = 0;
        setColor(whatColor(area[mx][my]), currentColor);
        tp(mx, my);
        printf("X");
    }
    else if(input == '[')
    {
        currentColor--;
        if(currentColor == -1)currentColor = 16;
        setColor(whatColor(area[mx][my]), currentColor);
        if(currentColor == 16 && area[mx][my] == '0')setColor(0, 15);
        tp(mx, my);
        printf("X");
    }
    else if(input == ' ')
    {
        save();
        tp(0, 0); setColor(0, 15); cout << "saved";
        Sleep(250); tp(0, 0);
        load();
    }
    else if(input == 'L' || input == 'l')
    {
        load();
    }
}
void clicked()
{
    
    if(my < 25 && mx < 80)
    {
        tp(mx, my);
        setColor(currentColor, currentColor);
        if(area[mx][my]==invisible)setColor(8, 7);
        printf("%c", whatChar(currentColor));
        setColor(0,15);
        area[mx][my] = whatChar(currentColor);
    }
    if(my == 25 && mx < 34)
    {
        currentColor = mx/2;
        if(mx/2 > (mx+1)/2)currentColor = (mx+1)/2;
    }
}
void doubleClicked()
{
    //nothingness
}
void moved()
{
    if(doClick)clicked();
    if(py < 25)
    {
        setColor(whatColor(area[px][py]), whatColor(area[px][py]));
        if(area[px][py]==invisible)setColor(8, 7);
        tp(px, py);
        printf("%c", area[px][py]);
    }
    if(py == 25)
    {
        setColor(whatColor(toolbar[px]), whatColor(toolbar[px]));
        if(toolbar[px]==invisible)setColor(8, 7);
        tp(px, 25);
        printf("%c", toolbar[px]);
    }
    if(my < 25 && mx < 80)
    {
        setColor(whatColor(area[mx][my]), currentColor);
        if(area[mx][my]==invisible)setColor(8, currentColor);
        tp(mx, my);
        printf("X");
        px = mx;
        py = my;
        tp(0, 0);
    }
    if(my == 25 && mx < 34)
    {
        tp(mx, my);
        setColor(whatColor(toolbar[mx]), currentColor);
        if(toolbar[mx] == invisible)setColor(8, currentColor);
        printf("X");
        px = mx;
        py = my;
        //currentColor = (mx+1)/2
    }
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
    else if(x == 16)return invisible;
    else return '0';
}

void save()
{
    fstream newfile;
    short whatchar=0, whatline=0;
    newfile.open("export.wdi", ios::out);
    newfile << "Wer-Dar Image v-1.2"<<endl;
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
    newfile.close();
}
void load()
{
    /*Wer-Dar Paint v-1.2*/
    fstream openfile;
    string holder;
    int i1=0, i2=0;

    openfile.open("export.wdi", ios::in);
    if(openfile.good() == false)
    {
        cout << "error 404";
        openfile.close();
        return;
    }
    openfile.close();
    openfile.open("export.wdi", ios::in);
    while(getline(openfile, holder))
    {
        if(i1>0)
        {
            while(i2<80)
            {
                area[i2][i1-1] = holder[i2];
                setColor(whatColor(area[i2][i1-1]), whatColor(area[i2][i1-1]));
                if(area[i2][i1-1]==invisible)setColor(8, 7);
                printf("%c", area[i2][i1-1]);
                i2++;
            }
        }
        i2=0;
        i1++;
    }
    setColor(0,0);
    printf("%70s");
    tp(0, 0);
    openfile.close();
}