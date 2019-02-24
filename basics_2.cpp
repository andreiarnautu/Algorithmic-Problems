//Generare codul Morse
#include <iostream>
using namespace std;
int n,v[50];
void afiseaza()
{
    for(int i=1;i<=n;i++)
    {
        if(v[i]==0)
            cout<<".";
        else
            cout<<"-";
    }
    cout<<'\n';
}
void genereaza(int x)
{
    if(x==n)
    {
        v[x]=0;
        afiseaza();
        v[x]=1;
        afiseaza();
        return;
    }
    v[x]=0;
    genereaza(x+1);
    v[x]=1;
    genereaza(x+1);
}
int main()
{
    cin>>n;
    genereaza(1);
    return 0;
}
