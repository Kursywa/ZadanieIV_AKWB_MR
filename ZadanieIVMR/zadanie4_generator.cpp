#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    srand(time(NULL));
    ofstream mapa,instancja;
    string plik_mapa,plik_instancja;
    cout<<"Podaj plik do zapisu mapy:"<<endl;
    cin>>plik_mapa;
    cout<<"Podaj plik do zapisu instancji:"<<endl;
    cin>>plik_instancja;
    plik_mapa += ".txt";
    plik_instancja += ".txt";
    mapa.open(plik_mapa);
    instancja.open(plik_instancja);
    int a,b,ilosc;
    cout<<"Podaj ilosc fragmentow:"<<endl;
    cin>>ilosc;
    cout<<"Podaj zakres, z ktorego losowana ma byc dlugosc fragmentow: (dwie liczby typu int)"<<endl;
    cin>>a>>b;
    vector<int> mapa_zbior,fragmenty;int suma=0;
    for(int i=0;i<ilosc;i++)
    {
        mapa_zbior.push_back(rand()%(b-a+1)+a);
        mapa<<mapa_zbior[i]<<" ";
    }
    for(int i=0;i<mapa_zbior.size();i++)
    {
        for(int j=i;j<mapa_zbior.size();j++)
        {
            suma+=mapa_zbior[j];
            fragmenty.push_back(suma);
        }
        suma=0;
    }
    sort(fragmenty.begin(),fragmenty.end());
    for(int i=0;i<fragmenty.size();i++)
    {
        instancja<<fragmenty[i]<<" ";
    }
}
