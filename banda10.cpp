#include <cstdio>
using namespace std;
FILE *fin=freopen("banda10.in","r",stdin);
FILE *fout=freopen("banda10.out","w",stdout);
int N;
char S[1001];
int Sol[1001], Aux[1001];

void Read()
{
    scanf("%d", &N);
    getchar();
    gets(S);
}

void Modify(int k)
{
    int i, t = 0, j;
    for( i = 1 ; i <= Aux[0] ; ++i )
        Aux[i] = 0;
    Aux[0] = Aux[1] = 1;
    for( i = 1 ; i <= k ; ++i )
    {
        t = 0;
        for( j = 1 ; j <= Aux[0] || t ; t /= 10 , ++j )
            Aux[j] = ( t += Aux[j] * 2 ) % 10;
        Aux[0] = j - 1;
    }
    t = 0;
    for( i = 1 ; i <= Sol[0] || i <= Aux[0] || t ; t /= 10 , ++i )
        Sol[i] = ( t += Sol[i] + Aux[i] ) % 10;
    Sol[0] = i - 1;
}

void Solve()
{
    Sol[0] = 1;
    for(int i = 0 ; i < N ; ++i )
        if( S[i] - 48 == 1 )
            Modify( N - i - 1 );
    printf("%d", Sol[0] );
}

int main()
{
    Read();
    Solve();
    return 0;
}
