#include <cstdio>
using namespace std;
FILE *fin=freopen("kafka.in","r",stdin);
FILE *fout=freopen("kafka.out","w",stdout);
struct { long Culoare, Birou ; } A[300][40], V[10000];
long B[300][40], nb, nc, bs,   k, t;
void Read()
{
    scanf("%d%d%d%lld",&nb,&nc,&bs,&t);
    for(int i=1 ; i<=nb ; ++i)
        for(int j=1 ; j<=nc ; ++j)
            scanf("%d%d",&A[i][j].Culoare,&A[i][j].Birou);
}
// Cum T poate sa fie foarte mare, observam ca nu sunt decat nb*nc posibilitati de a avea un bilet care te duce la o anumita camera si biletul sa aiba o anumita culoare
// Astfel, de la un moment dat deobicei o sa "cicleze" numerele birourilor
// Facem un vector V in care retinem numerele birourilor in care am fost
// In matricea B avem 0 daca nu am mai vizitat camera x avand in mana un bilet de culoarea y, altfel 1
// Daca dam de B[x][y] care era deja 1, inseamna ca am mai intalnit o situatie identica in trecut si se intrerupe whileul
// In cazul in care nu se cicleaza, rezolvarea e V[k].birou
// Altfel mergem cu variabila aux pana gasim "capatul" din fata al lantului.
// Scadem din t aux-1 pentru ca vrem de fapt sa vedem al catelea termen al lantului trebuie afisat, nu ne mai intereseaza primele aux-1 numere
// Scadem si din k aux-1 pentru a vedea cati termeni are lantul defapt
// Se afiseaza V[ aux + t % k - 1]


void Solve()
{
    int x, y, aux;
    x = bs;
    y = 1;
   do
    {
        B[x][y] = 1;
        V[++k].Birou = x;
        V[k].Culoare = y;
        aux = x;
        x = A[x][y].Birou;
        y = A[aux][y].Culoare;
    }while( k < t && ! B[x][y] );
    if( k == t )
        printf("%d\n",V[k].Birou);
    else
    {
        aux = 0;
        while( V[aux].Birou != x || V[aux].Culoare != y )
            ++aux;
        t -= (aux - 1);
        k -= (aux - 1);

        printf("%d\n",V[aux + t % k - 1 ].Birou);
    }
}
int main()
{
    Read();
    Solve();
    return 0;
}
