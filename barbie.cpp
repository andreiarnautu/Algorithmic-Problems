#include <algorithm>
#include <cstdio>
#define Max 1000000000
using namespace std;
FILE *fin = freopen("barbie.in" , "r" , stdin);
FILE *fout = freopen("barbie.out" , "w", stdout);

int GP, PP, N, V, G, Greutate[10009], A[10009];

void Read()
{
    scanf("%d", &GP);
    scanf("%d", &N);
    for(int i = 1 ; i <= 10000 ; ++i )
        Greutate[i] = Max;
    for(int i = 1 ; i <= N; ++i )
    {
        scanf("%d%d", &V, &G);
        Greutate[G] = min( Greutate[G] , V);
    }
}

void Solve()
{
    A[0] =  Max;
    A[1] = Greutate[1];
    for(int i = 2 ; i <= GP ; ++i )
    {
        A[i] = Greutate[i];
        for(int j = i / 2 ; j < i ; ++j )
            A[i] = min(A[i], A[j] + A[i - j]);
    }
    printf("%d", A[GP]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
