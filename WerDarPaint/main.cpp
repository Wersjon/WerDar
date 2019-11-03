#include "mouser.hpp"

using namespace std;

char area[80][25];

void exists();
void clicked();
void doubleClicked();
void moved();
int whatColor(char x);
char whatChar(short x);
void save();
void load();

int px, py;
short currentColor = 15;

int main()
{
HANDLE hOut;
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    COORD NewSBSize;
    int Status;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleScreenBufferInfo(hOut, &SBInfo);
    NewSBSize.X = SBInfo.dwSize.X - 2;
    NewSBSize.Y = SBInfo.dwSize.Y;

    Status = SetConsoleScreenBufferSize(hOut, NewSBSize);

    int i=0;
    int i2 = 0;
    while(i<25)
    {
        while(i2<80)
        {
            area[i2][i] = '#';
            setColor(whatColor(area[i2][i]), whatColor(area[i2][i]));
            if(area[mx][my]=='#')setColor(8, 7);
            printf("%c", area[i2][i]);
            i2++;
        }
        i2 = 0;
        i++;
    }
    SetConsoleTitleA("Wer-Dar Paint");
    mouse(exists, clicked, doubleClicked,  moved);
    return 0;
}

void exists()
{
    if(kbhit())
    {
        char znak = getch();
        if(znak == ' ')cout<<" ";//toolbar
        if(znak == ']')
        {
            currentColor++;
            if(currentColor == 17)currentColor = 0;
            setColor(whatColor(area[mx][my]), currentColor);
            tp(mx, my);
            printf("X");
        }
        if(znak == '[')
        {
            currentColor--;
            if(currentColor == -1)currentColor = 16;
            setColor(whatColor(area[mx][my]), currentColor);
            tp(mx, my);
            printf("X");
        }
        else if(znak == ' ')
        {
            save();
        }
        else if(znak == 'L' || znak == 'l')
        {
            load();
        }
    }
}
void clicked()
{
    tp(mx, my);
    setColor(currentColor, currentColor);
    if(area[mx][my]=='#')setColor(8, 7);
    printf("%c", whatChar(currentColor));
    setColor(0,15);
    area[mx][my] = whatChar(currentColor);
}
void doubleClicked()
{
    //nothingness
}
void moved()
{
    if(doClick)clicked();
    setColor(whatColor(area[px][py]), whatColor(area[px][py]));
    if(area[px][py]=='#')setColor(8, 7);
    tp(px, py);
    printf("%c", area[px][py]);
    setColor(whatColor(area[mx][my]), currentColor);
    if(area[mx][my]=='#')setColor(8, currentColor);
    tp(mx, my);
    printf("X");
    px = mx;
    py = my;
    tp(0, 0);
}
int whatColor(char x)
{
    //if(x == '0')return 0;
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
    short whatchar=0, whatline=0;
    newfile.open("export.wdi", ios::out);
    newfile << "Wer-Dar Image v-1.1"<<endl;
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
    /*Wer-Dar Paint v-1.1*/
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
                if(area[i2][i1-1]=='#')setColor(8, 7);
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