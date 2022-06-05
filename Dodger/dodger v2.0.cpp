#include<iostream>
#include<windows.h>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<algorithm>

using namespace std;

const int visina=20,sirina=20;
const char igrac=char(254);
const int zuta=14,bijela=15,crvena=12;
const pair<int,int> desno={1,0},lijevo={-1,0},gore={0,-1},dole={0,1};

short x=sirina/2,y=visina/2;
bool gameover=false;

struct metak{
    int a,b;
    pair<int,int> smjer;
};
vector<metak> m;

void postaviboju(int boja)
{
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),boja);
}
void font(int a)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.dwFontSize.X=a;
    cfi.dwFontSize.Y=a;
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_LIGHT;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false,&cfi);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
}
void ispis(char c,short X,short Y)
{
    COORD poz={X,Y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
    if(c=='O')postaviboju(crvena);
    cout<<c;
    postaviboju(bijela);
    poz={0,visina+1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),poz);
}
void setup()
{
    font(25);
    system("mode 30,35");
    for(int i=0;i<visina;i++){
        for(int j=0;j<sirina;j++){
            if(!i || !j || i==visina-1 || j==sirina-1){postaviboju(zuta); cout<<char(178);}
            else {postaviboju(bijela);cout<<" ";}
        }
           postaviboju(bijela);
        cout<<endl;
    }
    ispis(igrac,x,y);
}
void pomjeri()
{
    if(GetAsyncKeyState(VK_UP) && y!=1){ispis(' ',x,y); ispis(igrac,x,--y);}
    if(GetAsyncKeyState(VK_DOWN) && y!=visina-2){ispis(' ',x,y);ispis(igrac,x,++y);}
    if(GetAsyncKeyState(VK_LEFT) && x!=1){ispis(' ',x,y);ispis(igrac,--x,y);}
    if(GetAsyncKeyState(VK_RIGHT) && x!=sirina-2){ispis(' ',x,y);ispis(igrac,++x,y);}
    if(GetAsyncKeyState('p') || GetAsyncKeyState('P'))system("pause");
}
void novi_metak()
{
    metak temp;
    vector<metak> vtemp;
    vtemp.clear();
    ///slucaj 1
    temp.a=x;
    temp.b=1;
    temp.smjer=dole;
    vtemp.push_back(temp);
    ///slucaj 2
    temp.a=x;
    temp.b=visina-2;
    temp.smjer=gore;
    vtemp.push_back(temp);
    ///slucaj 3
    temp.a=1;
    temp.b=y;
    temp.smjer=desno;
    vtemp.push_back(temp);
    ///slucaj 4
    temp.a=sirina-2;
    temp.b=y;
    temp.smjer=lijevo;
    vtemp.push_back(temp);
    ///uzimanje nasumicne pocetne pozicije metka
    random_shuffle(vtemp.begin(),vtemp.end());
    metak novi= vtemp[0];
    m.push_back(novi);
}
void pucaj()
{
    random_shuffle(m.begin(),m.end());
    for(int i=0;i<m.size();i++)
    {
        if( (m[i].b==sirina-2 && m[i].smjer==dole) || (m[i].b==2 && m[i].smjer==gore) ||
            (m[i].a==visina-2 && m[i].smjer==desno) || (m[i].a==2 && m[i].smjer==lijevo) )continue;
       ispis(' ',m[i].a,m[i].b);
       m[i].a+=m[i].smjer.first;
       m[i].b+=m[i].smjer.second;
       if( (m[i].b==sirina-2 && m[i].smjer==dole) || (m[i].b==2 && m[i].smjer==gore) ||
           (m[i].a==visina-2 && m[i].smjer==desno) || (m[i].a==2 && m[i].smjer==lijevo) )continue;
       else if(m[i].a==x && m[i].b==y)gameover=true;
       else ispis('O',m[i].a,m[i].b);
       if(m[i].a==x && m[i].b==y)gameover=true;
    }
    for(int i=0;i<m.size()-1;i++){
       if(m[i].a==visina-2 || m[i].b==sirina-1 || m[i].a==1 || m[i].b==1
          || (m[i].a==m[i+1].a && m[i].b==m[i+1].b) ){
            m.erase(m.begin()+i);
            i--;
          }
    }
}

int main()
{
    srand(time(NULL));
    setup();
    clock_t pocetak=clock(),kraj;
    novi_metak();
    while(!gameover){
        pomjeri();
        kraj=clock();
        pucaj();
        if(float(kraj-pocetak)/float(CLOCKS_PER_SEC/1000)>400){novi_metak();pocetak=clock();}
        Sleep(60);
    }
    system("pause");
    return 0;

}
