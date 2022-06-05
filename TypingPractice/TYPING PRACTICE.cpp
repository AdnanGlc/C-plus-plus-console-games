#include<iostream>
#include<ctime>
#include<windows.h>
#include<conio.h>>
#include<iomanip>
#include<map>

using namespace std;

map<int,pair<int,int> > prsti;
int x=0,y=0;

void font(int a)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.dwFontSize.X=a;
    cfi.dwFontSize.Y=a;
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_LIGHT;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),true,&cfi);
}
void crtaj(int a)
{
    COORD poz={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
    cout<<' ';
    x=prsti[a].first;
    y=prsti[a].second;
    poz={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);///zelena
    cout<<char(254);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);///bijela
    ///vrati cursor
    poz={0,1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
}
void unos(string s)
{
    string s2="";
    while(s2.size()!=s.size()){
       if(_kbhit()){
         s2+=char(_getch());
         COORD poz={0,1};
         SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
         cout<<"                 "<<s2<<endl;
         crtaj(int(s[s2.size()]));
         poz={s2.size()+17,1};
         SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
       }
    }
    COORD poz={1,1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
    cout<<"                                                 ";
}
void deklaracija_mape()
{
    ///lijeva ruka:
    ///mali lijevi
    prsti[int('a')]=make_pair(10,7);
    prsti[int('q')]=make_pair(10,7);
    prsti[int('y')]=make_pair(10,7);
    ///lijevi prstenjak
    prsti[int('s')]=make_pair(12,6);
    prsti[int('w')]=make_pair(12,6);
    prsti[int('x')]=make_pair(12,6);
    ///ljievi srednjak
    prsti[int('d')]=make_pair(14,6);
    prsti[int('e')]=make_pair(14,6);
    prsti[int('c')]=make_pair(14,6);
    ///ljievi kaziprst
    prsti[int('f')]=make_pair(16,6);
    prsti[int('r')]=make_pair(16,6);
    prsti[int('v')]=make_pair(16,6);
    prsti[int('g')]=make_pair(16,6);
    prsti[int('t')]=make_pair(16,6);
    prsti[int('b')]=make_pair(16,6);
    //lijevi palac
    prsti[int(' ')]=make_pair(18,10);
    ///desna ruka:
    ///mali desni
    prsti[int('p')]=make_pair(32,7);
    ///desni kaziprst
    prsti[int('j')]=make_pair(26,6);
    prsti[int('u')]=make_pair(26,6);
    prsti[int('m')]=make_pair(26,6);
    prsti[int('n')]=make_pair(26,6);
    prsti[int('h')]=make_pair(26,6);
    prsti[int('z')]=make_pair(26,6);
    ///desni srednjak
    prsti[int('k')]=make_pair(28,6);
    prsti[int('i')]=make_pair(28,6);
    ///desni prstenjak
    prsti[int('o')]=make_pair(30,6);
    prsti[int('l')]=make_pair(30,6);

}
int main()
{
    font(20);
    system("title TYPING PRACTICE");
    system("mode 45,25");
    ///ispis ruku
    COORD poz={0,5};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
    cout<<"            _.-._         _.-._  "<<endl;
    cout<<"          _| | | |       | | | |_   "<<endl;
    cout<<"         | | | | |       | | | | | "<<endl;
    cout<<"         | | | | |       | | | | |   "<<endl;
    cout<<"         |       |_     _|       |  "<<endl;
    cout<<"         |       / /   ";cout<<char(92)<<" "<<char(92)<<"       |  "<<endl;
    cout<<"         |        /     ";cout<<char(92)<<"        |"<<endl;
    cout<<"          ";cout<<char(92)<<"      /       ";cout<<char(92)<<"      /"<<endl;
    cout<<"           |    |         |    |  "<<endl;
    cout<<"           |    |         |    |   "<<endl;
    deklaracija_mape();

    srand(time(NULL));
     string slova="";
      for(int i=97;i<97+26;i++)slova+=char(i);///engl abeceda

    while(true){
      string s="";
    for(int i=0;i<5;i++){
        s+=slova[rand()%26];
        s+=' ';
    }
    COORD poz={0,0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
    cout<<setw(27)<<s<<endl;
    crtaj(int(s[0]));
    unos(s);
   }
}
