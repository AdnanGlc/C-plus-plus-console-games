///inspiracija za program:  https://humanbenchmark.com/tests/reactiontime/

#include<iostream>
#include<windows.h>
#include<ctime>
#include<iomanip>

using namespace std;

string Zelena="    ZELENA    ",cekaj=" CEKAJ ZELENU ";

const int crvena=207,zelena=160,bijela=7;
double vrijeme;

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
void ispis(int boja)
{
    system("cls");
    cout<<endl;
    if(boja==crvena){
      cout<<"        ";
      postavi_boju(crvena);
      cout<<cekaj<<endl;
      postavi_boju(bijela);
    }
    else{
        cout<<"        ";
        postavi_boju(zelena);
        cout<<Zelena<<endl;
        postavi_boju(bijela);
    }
}
void unos()
{
    clock_t start=clock(),kraj;
    if(GetAsyncKeyState(VK_SPACE));
    while(true){
        if(GetAsyncKeyState(VK_SPACE)){kraj=clock();break;}
    }
    vrijeme=(double)(kraj-start)/(double)(CLOCKS_PER_SEC/1000);
}
int main()
{
    font(30);
    system("mode 31,15");
    int brojac=0;
    double prosjek=0;
    cout<<"Rules:\nwait for green color,\n then press SPACE\n\nto continue press SPACE...";
    do{
    if(GetAsyncKeyState(VK_SPACE))break;
   }while(true);
   ispis(crvena);
   system("pause");
   srand(time(NULL));
   do{
       pocetak:
       if(GetAsyncKeyState(VK_SPACE));
       ispis(crvena);
       Sleep(1000+rand()%5000);
       if(GetAsyncKeyState(VK_SPACE))//detektuje ako je prerano pritisnuto space
            {
                postavi_boju(bijela);
                cout<<"PRERANO"<<endl;
               cout<<system("pause");
                goto pocetak;
            }
      ispis(zelena);
      unos();
       postavi_boju(bijela);
        cout<<"VRIJEME: "<<vrijeme<<" ms"<<endl;
        prosjek+=vrijeme;
        system("pause");
        brojac++;
   }while(brojac!=5);

     postavi_boju(bijela);
    cout<<endl<<"PROSJEK: "<<prosjek/brojac<<" ms"<<endl;

    return 0;
}
