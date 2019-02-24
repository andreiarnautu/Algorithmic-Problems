#include <cstdio>
using namespace std;
FILE *fin=freopen("cifre1.in","r",stdin);
FILE *fout=freopen("cifre1.out","w",stdout);
unsigned long long n,t;
unsigned long long nrc;
// Ideea de baza a problemei e sa nu stai sa verifici pentru fiecare numar de la 1 la N sa vezi cate cifre are
// Trebuie sa iti dai seama de formula generala a problemei.

int putere(int x)
{
    long long p=1;
    for(int i=1;i<=x;i++)
        p*=10;
    return p;
}
int main()
{
    long long i,nn;
    scanf("%d",&n);
    nn=n;
    while(nn) // Calculam numarul de cifre al lui N
    {
        ++nrc;
        nn/=10;
    }
    // Pentru numerele care au mai putine cifre ca N, calculam dupa formula de mai jos
    for(i=1;i<nrc;i++)
        t+=i*9*putere(i-1);
    t+=nrc*(n-putere(nrc-1)+1); // Pentru numerele care au atatea cifre cate are N, inmultim numarul de cifre cu numarul de numere de nrc cifre
    printf("%lld",t);
    return 0;
}
