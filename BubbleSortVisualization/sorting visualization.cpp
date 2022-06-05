//inspiracija za program: https://www.youtube.com/watch?v=kPRA0W1kECg
#include<iostream>
#include<windows.h>
#include<ctime>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> linije;
const int zelena=10,crvena=12,bijela=7;

void postavi_boju(int boja)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),boja);
}
void ispis(int x,int y)
{
    LockWindowUpdate(GetConsoleWindow());
    system("cls");
    cout<<"Bubble sort:"<<endl;
    for(int i=0;i<linije.size();i++)
    {
        if(i==x){
            postavi_boju(zelena);cout<<linije[i]<<endl;postavi_boju(bijela);continue;
        }
        if(i==y){
            postavi_boju(crvena);cout<<linije[i]<<endl;postavi_boju(bijela);continue;
        }
        else cout<<linije[i]<<endl;
    }
    LockWindowUpdate(NULL);
    Sleep(30);
}
void bubble_sort()
{
    for(int i=0;i<linije.size();i++){
        for(int j=i+1;j<linije.size();j++){
            if(linije[i].length() > linije[j].length() ){swap(linije[i],linije[j]);
            Beep(800,50);}
            ispis(i,j);
        }
    }
}
int main()
{
    cout<<"Unesite broj clanova za sortirati"<<endl;
    int n;cin>>n;string s="";
    for(int i=0;i<n;i++){
        s+=char(254);
        linije.push_back(s);
    }
    random_shuffle(linije.begin(),linije.end());
    ispis(-1,-1);
    system("pause");
    bubble_sort();
    for(int i=0;i<=n;i++){Beep(i*150+200,50);ispis(i,-1);};
    cout<<endl<<"Sortirano :)"<<endl;
    return 0;
}
/*
PSEUDO KOD:
pocetak
vector<string> linije
const int zelena=10,crvena=12,bijela=7;
unesi n
za i od 0 do n
(
 string s=""
 r=rand()%50+1
 za j od 0 do r (s+=(char)254)
 linije gurni nazad s
 )
ispis(-1,-1)
(
 poslati: int x,int y
 narediti sistemu da zakoči console window update
 narediti sistemu da očisti ekran
 dok je i < linije.size()
 (
  ako je i==x onda
  (
   pozvati funkciju postavi_boju(zelena)
   (
    poslati: int boja
    narediti sistemu da postavi boju teksta na boja
    vrati: nista
    )
   ispisi linije[i],'\7'
   pozvati funkciju postavi_boju(bijela)
   nastavi
   )
  ako je i==y onda
  (
   pozvati funkciju postavi_boju(crvena)
   ispisi linije[i],'\7'
   pozvati funkciju postavi_boju(bijela)
    )
  inace ispisi linije[i]
  )
 naredi sistemu da otkoci console window update
 narediti sistemu da spava 50 milisekundi
 vratiti: nista
 )
 narediti sistemu  da se pauzira
 pozvati funkciju bubble_sort()
(
 poslati: nista
 dok je i<linije.size()
 (
  za j=i sve dok je j<linije.size()
  (
   ako je linije[i] > linije[j] zamjeni linije[i],linije[j]
   pozvati funkciju Beep(400,50)
   pozvati funkciju ispis(i,j)
   )
  )
 )
 dok je i<linije.size() (pozvati funkciju Beep(i*150+200,50),pozvati funkciju bubble_sort(i,-1) )
kraj

*/
