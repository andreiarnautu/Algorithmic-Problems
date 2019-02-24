#include <cstdio>
#include <algorithm>
#define Dim 1000001
const int Mod = 666013;
using namespace std;

FILE *fin=freopen("cntper.in","r",stdin);
FILE *fout=freopen("cntper.out","w",stdout);

int Nr;
long long int Number[Dim];


void Generate()
{
    long long int last = 1;
    for(int i = 1; i <= 1000000 ; ++i )
    {
        last = ( last * 26 ) % Mod;
        Number[i] = last - Number[i] % Mod;
        if( Number[i] < 0 )
            Number[i] += Mod;
        for(int j = 2 ; i * j <= 1000000; ++j )
            Number[j * i] += Number[i];
    }

}

void Solve()
{
    int T, N;
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
    {
        scanf("%d", &N);
        printf("%d\n", Number[N]);
    }
}

int main()
{
    Generate();
    Solve();
    return 0;
}
