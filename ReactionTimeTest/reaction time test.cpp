///inspiracija za program: https://humanbenchmark.com/tests/reactiontime
#include<iostream>
#include<windows.h>
#include<ctime>
#include<vector>

using namespace std;

const int visina=10,sirina=20;
vector<string> s;
string cekaj="     ",z="     ";
const int crvena=12,crvena2=207,zelena=10,zelena2=160,bijela=7;
double vrijeme;

void promjeni_boju(int boja)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),boja);
}
void font(int a,int b)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont=0;
    cfi.dwFontSize.X=a;
    cfi.dwFontSize.Y=b;
    cfi.FontFamily=FF_MODERN;
    cfi.FontWeight=FW_NORMAL;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false ,&cfi);
}
void setup()
{
    string linija="    ";
    for(int i=0;i<sirina;i++)linija+=(char)219;
    s.insert(s.begin(),visina,linija);

    for(int i=0;i<sirina+5;i++){
            if(i==7){z+="ZELENA";i+=6;}
    else z+=(char)219;
    }
     for(int i=0;i<sirina+4;i++){
            if(i==4){cekaj+="CEKAJ ZELENU";i+=11;}
    else cekaj+=(char)219;
    }
}
void ispis(int boja)
{
    system("cls");
    promjeni_boju(boja);
    cout<<endl<<endl;
    for(int i=0;i<visina;i++){
        if(i!=visina/2-1){promjeni_boju(boja);cout<<s[i];}
        else
            for(int j=0;j<sirina+4;j++){
            if(boja==crvena){
                if(j<4)cout<<" ";
                else if(cekaj[j]==(char)219 || cekaj[j]==' '){
                    promjeni_boju(crvena);cout<<(char)219;
                }
                else {
                    promjeni_boju(crvena2);cout<<cekaj[j];
                }
            }
            if(boja==zelena){
                if(j<4)cout<<" ";
                else if(z[j]==(char)219){
                    promjeni_boju(zelena);cout<<(char)219;
                }
                else {
                    promjeni_boju(zelena2);cout<<z[j];
                }
            }
        }
        cout<<endl;
    }
}
void unos()
{
    clock_t start=clock(),kraj;
    while(true){
        if(GetAsyncKeyState(VK_SPACE)){kraj=clock();break;}
    }
    vrijeme=(double)(kraj-start)/(double)(CLOCKS_PER_SEC/1000);
}
int main()
{
    font(35,35);
    system("mode 32,20");
    setup();
    ispis(crvena);
    int brojac=0;
    double prosjek=0;
    system("pause");
    if(GetAsyncKeyState(VK_SPACE));
    srand(time(NULL));
    do
    {
        pocetak:
        if(GetAsyncKeyState(VK_SPACE));
        ispis(crvena);
        promjeni_boju(bijela);
        Sleep(1000+rand()%4000);
          if(GetAsyncKeyState(VK_SPACE))
            {
                promjeni_boju(bijela);
                cout<<"PRERANO"<<endl;
                system("pause");
                goto pocetak;
            }
        ispis(zelena);
        unos();

        promjeni_boju(bijela);
        cout<<"VRIJEME: "<<vrijeme<<" ms"<<endl;
        prosjek+=vrijeme;

        system("pause"); if(GetAsyncKeyState(VK_SPACE));

    }while(brojac++!=7);

    promjeni_boju(bijela);
    cout<<endl<<"PROSJEK: "<<prosjek/brojac<<" ms"<<endl;
    return 0;
}
