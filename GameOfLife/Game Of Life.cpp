#include<iostream>
#include<windows.h>
#include<cstdlib>
#include<ctime>

using namespace std;

const int visina=50,sirina=50;
bool stanje[sirina][visina],stanje2[sirina][visina];
///
const char cell=char(219);

int toIndex(int x,int y)
{
    return y*sirina+x;
}
void PostaviFont(int Velicina,bool Vidljivost)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.dwFontSize.X=Velicina;
    cfi.dwFontSize.Y=Velicina;
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false,&cfi);

    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=Vidljivost;
    cci.dwSize=100;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cci);
}
int PrebrojSusjede(int x,int y)
{
    int zbir=0;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            zbir+=stanje[x+i][y+j];
        }
    }
    return zbir-stanje[x][y];
}
void UpdateState()
{
    for(int i=1;i<visina-1;i++){
        for(int j=1;j<sirina-1;j++){
            int BrSusjeda=PrebrojSusjede(i,j);
            if(stanje[i][j]==0 && BrSusjeda==3)stanje2[i][j]=1;
            if(stanje[i][j]==1 && (BrSusjeda<2 || BrSusjeda>3))stanje2[i][j]=0;
        }
    }
    for(int i=0;i<visina;i++)for(int j=0;j<sirina;j++)stanje[i][j]=stanje2[i][j];
}
int main()
{
    wchar_t *prikaz= new wchar_t[visina*sirina];
    HANDLE cHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,0,NULL,CONSOLE_TEXTMODE_BUFFER,NULL);
    DWORD dwBitovaNapisano=0;
    prikaz[visina*sirina-1]='\0';

    srand(time(NULL));
    PostaviFont(10,false);
    system("mode 55,55");
    for(int i=0;i<1000;i++){int rx=rand()%sirina,ry=rand()%visina; stanje[rx][ry]=true;}
    int brojac=0;
    while(true){
    UpdateState();
    for(int i=0;i<visina;i++)
        for(int j=0;j<sirina;j++)
            prikaz[toIndex(i,j)]=stanje[i][j]?L'#':L' ';

    for(int i=0;i<visina;i++){
        for(int j=0;j<sirina;j++){
            if(stanje[i][j])cout<<char(219);
            else cout<<" ";
        }
        cout<<endl;
    }
    cout<<"Generacija: "<<brojac++<<endl;

//     WriteConsoleOutputCharacterW(cHandle,prikaz,visina*sirina,{0,0},&dwBitovaNapisano);
      LockWindowUpdate(NULL);
      Sleep(10);
      LockWindowUpdate(GetConsoleWindow());
      system("cls");

    }
    return 0;
}
