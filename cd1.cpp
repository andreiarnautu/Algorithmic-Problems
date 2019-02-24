#include <cstdio>
#define Mod 9901
using namespace std;
FILE *fin=freopen("cd1.in","r",stdin);
FILE *fout=freopen("cd1.out","w",stdout);
int S, N, Nr[400];

void Read()
{
    int x, y;
    scanf("%d%d", &N, &S);
    for(int i = 1 ; i <= N ; ++i )
        Nr[i] = S / N;
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d%d", &x, &y);
        Nr[i] += x;
        Nr[y] -= x;
    }
}

void Solve()
{
    long Sol = 1;
    for(int i = 1 ; i <= N ; ++i )
        Sol = (1ll * Sol * (Nr[i] - 1)) % Mod;
    printf("%d", Sol);
}

int main()
{
    Read();
    Solve();
    return 0;
}
