#include<iostream>
#include<ctime>
#include<windows.h>
#include<list>

using namespace std;

const int visina=20,sirina=20;
const char zid=char(219),zmija=char(178),hrana=char(254);
const int plava=9,crvena=4,bijela=7,roza=12,zelena=10;
const int smjerx[4]={-1,1, 0,0};//w s a d
const int smjery[4]={ 0,0,-1,1};

char igra[visina][sirina];
list<pair<int,int> >rep;
int x,y,score,smjer;
bool gameover;

void postavi_boju(int boja)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),boja);
}

void font(int x)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.dwFontSize.X=x;
    cfi.dwFontSize.Y=x;
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_LIGHT;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false,&cfi);
}
void stvori_hranu()
{
    while(true){
        int r1=rand()%visina+1;
        int r2=rand()%sirina+1;
        if(igra[r1][r2]==' '){
            igra[r1][r2]=hrana;
            score++;
            if(score>1)Beep(750,50);
            break;
        }
    }
}
void setup()
{
    for(int i=0;i<sirina;i++)
    {
        for(int j=0;j<sirina;j++)
        {
            if(!i || !j || i==visina-1 || j==sirina-1)igra[i][j]=zid;
            else igra[i][j]=' ';
        }
    }
    x=visina/2;
    y=sirina/2;
    smjer=3;
    igra[x][y]=zmija;
    rep.clear();
    rep.push_back(make_pair(x,y));
    score=0;
    gameover=false;
    stvori_hranu();
    ENABLE_MOUSE_INPUT;
}
void ispis()
{
    LockWindowUpdate(GetConsoleWindow());
    system("cls");
    for(int i=0;i<visina;i++){
        for(int j=0;j<sirina;j++){
            if(igra[i][j]==zmija){
                if(i==x && j==y){
                    postavi_boju(roza);cout<<igra[i][j];continue;
                }
                else {postavi_boju(crvena);cout<<igra[i][j];continue; }
            }
            else if(igra[i][j]==hrana){postavi_boju(zelena);cout<<igra[i][j]; continue;}
            else {postavi_boju(bijela);cout<<igra[i][j];}
        }
        cout<<endl;
    }
    cout<<"SCORE: "<<score<<endl;
    LockWindowUpdate(NULL);
    Sleep(50);
}
void pomjeri()
{
    x+=smjerx[smjer];
    y+=smjery[smjer];
    if(igra[x][y]==zid || igra[x][y]==zmija ){gameover=true;cout<<'\7';return;}
    else{
        if(igra[x][y]==hrana)stvori_hranu();
        else{
                igra[rep.front().first][rep.front().second]=' ';
                rep.pop_front();
        }
    }
        igra[x][y]=zmija;
        rep.push_back(make_pair(x,y));
}
void unos()
{
    if(GetAsyncKeyState(VK_UP))smjer=0;
    if(GetAsyncKeyState(VK_DOWN))smjer=1;
    if(GetAsyncKeyState(VK_LEFT))smjer=2;
    if(GetAsyncKeyState(VK_RIGHT))smjer=3;
    if(GetAsyncKeyState('p') || GetAsyncKeyState('P'))system("pause");
    pomjeri();
}
int main()
{
    srand(time(NULL));
    font(25);
    system("mode 20,26");
    ponovo:
    setup();
    while(!gameover){
          ispis();
          unos();
    }
    cout<<endl<<"GAME OVER"<<endl<<"PONOVO-enter"<<endl<<"KRAJ-esc"<<endl;
    while(true)
    {
        if(GetAsyncKeyState('\r'))goto ponovo;
        if(GetAsyncKeyState(VK_ESCAPE))break;
    }
    return 0;
}
