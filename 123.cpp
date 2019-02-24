#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *fin=freopen("123.in","r",stdin);
FILE *fout=freopen("123.out","w",stdout);

struct {int a, b, c;} Nr[10001];
int N, P, K;
int V[10001];

void Read()
{
    char c;
    scanf("%d%d%d", &N, &K, &P);
    getchar();
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%c", &c);
        Nr[i].a = Nr[i-1].a;
        Nr[i].b = Nr[i-1].b;
        Nr[i].c = Nr[i-1].c;
        if( c == '1' )
            Nr[i].a ++;
        else if( c == '2' )
            Nr[i].b ++;
        else
            Nr[i].c ++;
    }
}

int Check( int x, int y, int z)
{
    if( ! ( x == 0 || y == 0 || abs(x-y) <= P ) )
        return 0;
    if( ! ( x == 0 || z == 0 || abs(x-z) <= P ) )
        return 0;
    if( ! ( y == 0 || z == 0 || abs(y-z) <= P ) )
        return 0;
    return 1;
}

void Solve()
{
    V[1] = 1;
    for(int i = 2 ; i <= N ; ++i)
    {
        for(int j = max(1 , i - K + 1) ; j < i ; ++j)
            if( Check ( Nr[i].a - Nr[j-1].a , Nr[i].b - Nr[j-1].b , Nr[i].c - Nr[j-1].c ) && ( V[i] == 0 || V[i] > V[j - 1] + 1) )
                V[i] = V[j - 1] + 1;
    }
    printf("%d", V[N]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
