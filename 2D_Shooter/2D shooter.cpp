#include<iostream>
#include<ctime>
#include<windows.h>
#include<cstdlib>
#include<vector>

using namespace std;

int visina=40,sirina=50;
char blok=char(219),cMetak=char(254),dBlok=220,gBlok=223;
string sIgrac,sRobot,sObrisi;

HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);

void PostaviBoju(int boja)
{
    SetConsoleTextAttribute(handle,boja);
}
void font(short VelicinaFonta,bool Vidljivost)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize=sizeof(cfi);
    cfi.dwFontSize.X=VelicinaFonta;
    cfi.dwFontSize.Y=VelicinaFonta;
    cfi.FontFamily=FF_DONTCARE;
    cfi.FontWeight=FW_NORMAL;
    SetCurrentConsoleFontEx(handle,false,&cfi);

    CONSOLE_CURSOR_INFO cci;
    cci.bVisible=Vidljivost;
    cci.dwSize=100;
    SetConsoleCursorInfo(handle,&cci);
}
void crtaj(char znak,int x,int y){
    COORD pozicija={x,y};
    SetConsoleCursorPosition(handle,pozicija);
    cout<<znak;
}
class Metak{
    public:
  int metakX,metakY;
  int smjer;
  void pomjeri_metak();
}novi_metak;

class Igraci{

 public:
 int pozX,pozY;
 int zivoti;
 int boja;
 float BrzinaPucanja;
 int SmjerPucanja,smjer;
 clock_t vrijeme; //za kontrolu brzine pucanja
 vector<Metak> metak;

 void ispis(int pozX,int pozY,string s);
 void pomjeri(int smjer);
 void stvori_robota(int y);

}igrac={1,visina/2,3,11,500,1,1,clock()},robot[3];//inicijalizacija igraca i robota

void Igraci::ispis(int x,int y,string s){

  PostaviBoju(boja);
  int brojac=0;
  while(brojac<s.size()){
        for(int i=y;i<y+3;i++){
            for(int j=x;j<x+3;j++){
                crtaj(s[brojac++],j,i);
            }
         }
     }

}
void Igraci::stvori_robota(int x){

   pozX=x;///x osa je uvjek ista
   pozY=rand()%(visina-5)+1; //y osa je na pocetku nasumicna
   boja=rand()%14+1;
   zivoti=1;
   BrzinaPucanja=float(rand()%400+300 );
   SmjerPucanja=-1;  //smjer pucanja je ucjek prema igracu tj lijevo
   int rSmjer[2]={1,-1};
   smjer=rSmjer[rand()%2]; //pocetni smjer kretanja robota je nasumican
   vrijeme=clock();
}
void Igraci::pomjeri(int novismjer){
   smjer=novismjer;// smjer = novi smjer zbog igraca
   ispis(pozX,pozY,sObrisi);
   if(pozY+smjer==0 || pozY+smjer==visina-3){
        if(smjer==1)smjer=-1;else smjer=1;}
   pozY+=smjer;
   ispis(pozX,pozY,pozX<5?sIgrac:sRobot); //ako je pocija x manja od 5 onda se radi o igracu
                                          //te ce se ispisati string igraca
}
void Metak::pomjeri_metak()
{
    if((metakX+smjer>=igrac.pozX && metakX<=igrac.pozX+3) && (metakY>=igrac.pozY && metakY<=igrac.pozY+3) && smjer==-1){ igrac.zivoti--; cout<<'\7'; }
    for(int i=0;i<3;i++){
        crtaj(' ',metakX,metakY);
        if((metakX+smjer>=robot[i].pozX && metakX<=robot[i].pozX+3) && (metakY>=robot[i].pozY && metakY<=robot[i].pozY+3) && smjer==1)robot[i].zivoti--;
         else{
            metakX+=smjer;
            crtaj(cMetak,metakX,metakY);
         }
    }
}

void setup()
{
    font(16,false);
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    for(int i=0;i<visina;i++)
    {
        for(int j=0;j<=sirina+2;j++)
        {
            if(!i || !j || j==sirina+2 || i==visina-1)cout<<'#';
            else cout<< " ";
        }
        cout<<endl;
    }
    ///string za ispis igraca
    sIgrac+=dBlok; sIgrac+=dBlok; sIgrac+=' ';
    sIgrac+=blok; sIgrac+=blok; sIgrac+=blok;
    sIgrac+=gBlok; sIgrac+=gBlok; sIgrac+=' ';
    ///string za ispis robota
    sRobot+=' '; sRobot+=dBlok; sRobot+=dBlok;
    sRobot+=blok; sRobot+=blok; sRobot+=blok;
    sRobot+=' '; sRobot+=gBlok; sRobot+=gBlok;
    ///string za brisanje
    sObrisi="         ";
    ///stvaranje i ispisivanje robota
     for(int i=0;i<3;i++){
        robot[i].stvori_robota(sirina-4-i*3);
        robot[i].ispis(robot[i].pozX,robot[i].pozY,sRobot);
    }
    igrac.ispis(igrac.pozX,igrac.pozY,sIgrac);
    PostaviBoju(7);
    crtaj('#',sirina+2,2);
    cout<<"Kratanje-strelice gore/dole"<<endl;
    crtaj('#',sirina+2,3);
    cout<<"Pucanje - SPACE"<<endl;
}
int main()
{
    system("mode 120,50");
    srand(time(NULL));
    setup();

    ///vrijeme za kontrolosanje pucanja
    clock_t tIgrac=clock(),tRobot[3]={clock(),clock(),clock()};
    int score=0;
    while(igrac.zivoti){
            LockWindowUpdate(GetConsoleWindow());
            //update vremena
            igrac.vrijeme=clock();
            for(int i=0;i<3;i++)robot[i].vrijeme=clock();
            //pomjeranje igraca
        if(GetAsyncKeyState(VK_UP))igrac.pomjeri(-1);
        if(GetAsyncKeyState(VK_DOWN))igrac.pomjeri(1);
        if(GetAsyncKeyState(VK_SPACE)){
            if(float(igrac.vrijeme-tIgrac)/float(CLOCKS_PER_SEC/1000)>igrac.BrzinaPucanja)
                {novi_metak={igrac.pozX+3,igrac.pozY+1,igrac.SmjerPucanja};
                igrac.metak.push_back(novi_metak);
                tIgrac=clock();
                }
        }
        ///pomjeranje robota
        for(int i=0;i<3;i++)robot[i].pomjeri(robot[i].smjer);
        ///pucanje robota
          for(int i=0;i<3;i++)
        if(float(robot[i].vrijeme-tRobot[i])/float(CLOCKS_PER_SEC/1000)>robot[i].BrzinaPucanja)
                {novi_metak={robot[i].pozX,robot[i].pozY+1,robot[i].SmjerPucanja};
                robot[i].metak.push_back(novi_metak);
                tRobot[i]=clock();
                }
        ///pomjeranje metaka za igraca
        PostaviBoju(igrac.boja);
        for(int i=0;i<igrac.metak.size();i++)igrac.metak[i].pomjeri_metak();
        for(int i=0;i<igrac.metak.size();i++)if(igrac.metak[i].metakX>sirina-2){
            crtaj(' ',igrac.metak[i].metakX,igrac.metak[i].metakY);
            igrac.metak.erase(igrac.metak.begin()+i);if(i)i--;
         }
        ///pomjeranje metaka za robota
        for(int i=0;i<3;i++){
                PostaviBoju(robot[i].boja);
            for(int j=0;j<robot[i].metak.size();j++)robot[i].metak[j].pomjeri_metak();
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<robot[i].metak.size();j++)if(robot[i].metak[j].metakX<2){
                crtaj(' ',robot[i].metak[j].metakX,robot[i].metak[j].metakY);
                robot[i].metak.erase(robot[i].metak.begin()+j);if(j)j--;
            }
        }
        for(int i=0;i<3;i++)if(robot[i].zivoti<=0){robot[i].ispis(robot[i].pozX,robot[i].pozY,sObrisi);robot[i].stvori_robota(robot[i].pozX);score+=100*(3-i);}

        crtaj(' ',0,visina+1);
        PostaviBoju(7);
        cout<<endl<<"SCORE: "<<score<<endl;
        cout<<"ZIVOTI:"<<igrac.zivoti<<endl;
        LockWindowUpdate(NULL);
        Sleep(50);
    }
    cout<<"GAME OVER"<<endl;
    getchar();
    return 0;
}
