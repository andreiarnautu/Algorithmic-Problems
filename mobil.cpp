#include <cstdio>
#include <cmath>
using namespace std;
FILE *fin=freopen("mobil.in", "r", stdin);
FILE *fout=freopen("mobil.out", "w", stdout);

long long M,  Nr[31], S[31], Optim;

void Read()
{
    scanf("%lld", &M);
    for(int i = 0 ; i <= 30 ; ++i )
        scanf("%lld", &Nr[i]);
}

long long Putere(long long a, long long b)
{
    long long p = 1 ;
    for(long long i = 1 ; i <= b ; ++i )
        p *= a;
    return p;
}

void Procesare()
{
    long long k;
  //  for(int i = 0 ; i <= 30 ; ++i )
     //   V[i] = -1;
    S[0] = Nr[0];
    for(int i = 1 ; i <= 30 ; ++i )
    {
        k = Nr[i];
        if( S[i - 1] * 2 > k )
            k = S[i - 1] * 2;
        S[i] = k;
        if( S[i] >= M && M > S[i - 1] )
            Optim = Putere(2, i);
    }
  //  printf("%lld",Optim);
}

long long Suma(long long x)
{
    long long q = 0;
    long long Sum = 0;
    while( x )
    {
        if( x % 2 == 1 )
            Sum += S[q];
        ++q;
        x /= 2;
    }
    return Sum;
}

void Cautare_Binara()
{
    long long st, dr, m;
    st = Optim / 2;
    dr = Optim;
  /*  if(Optim == 2)
    {
        printf("2");
        return;
    }*/
    while( st + 1 < dr )
    {
        m = (st + dr) / 2;
       // printf("%lld\n",Suma(m));
        if( Suma(m) >= M && Suma(m - 1) < M )
        {
            printf("%lld", m);
            return;
        }
        if( Suma(m) > M )
        {
            dr = m;
        }
        else
            st = m;
    }
    printf("%lld ", st + 1);
}

int main()
{
    Read();
    if( M <= Nr[0] )
    {
        printf("1");
        return 0;
    }
    Procesare();
   // printf("%lld", Suma(100));
    Cautare_Binara();
    return 0;
}
