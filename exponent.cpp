#include <cstdio>
using namespace std;
FILE *fin=freopen("exponent.in","r",stdin);
FILE *fout=freopen("exponent.out","w",stdout);
bool viz[32005];
int Pr[30000], k, F[30000], Need[30000];
int N, D;
void Ciur()
{
    int i, j, DD, aux;
    if( D % 2 == 0)
        Pr[++k] = 2;
    for( i = 3 ; i*i <= 32000 ; i += 2)
        if( !viz[i] )
        {
            for( j = i*i ; j<=32000 ; j+=2*i)
                viz[j] = 1;
            if( D % i == 0 )
                Pr[++k] = i;
        }
    for( i=1; i<=k ; ++i)
    {
        DD = D;
        aux = Pr[i];
        while( DD % aux == 0 )
        {
            ++Need[i];
            DD /= aux;
        }
    }
  //  for(int i=1; i<=k ; ++i)
    //    printf("%d %d\n",Pr[i],Need[i]);
}
void Plus(int a)
{
    for(int i=1 ; i<=k ; ++i)
    {
        if( a % Pr[i] == 0 && a > 0)
            while( a % Pr[i] == 0 && a > 0)
            {
                a /= Pr[i];
                F[i] += 1;
            }
    }
}
void Solve()
{
    int i, j, x, Min = 1000000;
    for( i=1 ; i<=N ; ++i)
    {
        scanf("%d",&x);
        Plus(x);
    }
    for(int i=1; i<=k ; ++i)
        if( F[i] / Need[i] < Min)
            Min = F[i] / Need[i];
    printf("%d",Min);
}
int main()
{
    scanf("%d%d",&N,&D);
    Ciur();
    Solve();
    return 0;
}
