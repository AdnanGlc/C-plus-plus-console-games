#include<iostream>
#include<windows.h>
#include<time.h>
#include<list>
#include<vector>
#include<algorithm>
#include<conio.h>

using namespace std;

vector<string> rtt{"         ","         ","         "};
float vrijeme=0;

void pozicija(int x,int y)
{
   COORD c;
   c.X=x;
   c.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
   if(y!=6)cout<<char(249);
}
void font(int a)
{
     CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont=0;
    cfi.dwFontSize.X=a;
    cfi.dwFontSize.Y=a;
    cfi.FontFamily=FF_MODERN;
    cfi.FontWeight=FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false ,&cfi);
}
void postavi_boju(int boja)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),boja);
}
void ispis(int x,int y)
{
    system("cls");
    int boja=12;//crvena
    for(int i=0;i<3;i++){
        if(x==i){
                cout<<"   ";
            for(int j=0;j<rtt[0].size();j++){
                if(j==y){
                    postavi_boju(boja);cout<<rtt[i][j];
                    postavi_boju(7);//bijela
                }
                else cout<<rtt[i][j];
            }
            cout<<endl<<endl;
        }
        else  cout<<"   "<<rtt[i]<<endl<<endl;;
    }

}
void unos(char smjer)
{
    char znak;
    clock_t start=clock(),kraj;
    if(GetAsyncKeyState(VK_UP))   ;
    if(GetAsyncKeyState(VK_DOWN)) ;
    if(GetAsyncKeyState(VK_LEFT)) ;
    if(GetAsyncKeyState(VK_RIGHT));
    if(GetAsyncKeyState(VK_SPACE));
    while(true)
    {
        int y=2,x=rtt[0].size()/2+3;
        if(GetAsyncKeyState(VK_UP))   {y--;pozicija(x,y);znak='w';break;}
        if(GetAsyncKeyState(VK_DOWN)) {y++;pozicija(x,y);znak='s';break;}
        if(GetAsyncKeyState(VK_LEFT)) {x--;pozicija(x,y);znak='a';break;}
        if(GetAsyncKeyState(VK_RIGHT)){x++;pozicija(x,y);znak='d';break;}
    }
    kraj=clock();
    vrijeme=double(kraj-start)/double(CLOCKS_PER_SEC/1000);
    pozicija(0,6);
    if(znak!=smjer)cout<<"POGRESAN SMJER"<<endl;
}
int main()
{
    system("mode 10,10");
    font(20);
    srand(time(NULL));
    int s=rtt[0].size();
    rtt[0][s/2]=(char)219;
    rtt[1][s/2]=(char)254;
    rtt[2][s/2]=(char)219;
    rtt[1][0]=(char)219;
    rtt[1][s-1]=(char)219;

     ispis(-1,-1);
     cout<<"Pritisni SPACE DA NASTAVIS..."<<endl;
    while(true){if(GetAsyncKeyState(VK_SPACE))break;}
    ispis(-1,-1);
    vector<pair<pair<int,int>,char> > mjesto;
    mjesto.push_back(make_pair(make_pair(0,s/2),'w'));//(0,s/2),'w'
    mjesto.push_back(make_pair(make_pair(1,0),'a'));
    mjesto.push_back(make_pair(make_pair(1,s-1),'d'));
    mjesto.push_back(make_pair(make_pair(2,s/2),'s'));
    while(true)
    {
        random_shuffle(mjesto.begin(),mjesto.end());
        Sleep(500+rand()%3000);
        int x=mjesto.back().first.first;
        int y=mjesto.back().first.second;
        ispis(x,y);
        unos(mjesto.back().second);
        cout<<"VRIJEME: "<<vrijeme<<"ms"<<endl;
        vrijeme=0;
         cout<<"Pritisni SPACE DA NASTAVIS..."<<endl;
    while(true){if(GetAsyncKeyState(VK_SPACE))break;}
    ispis(-1,-1);
    }
    return 0;

}
