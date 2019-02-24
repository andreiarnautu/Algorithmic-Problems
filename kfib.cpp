#include <cstdio>
#include <cstring>
#define Mod 666013
using namespace std;

FILE *fin=freopen("kfib.in","r",stdin);
FILE *fout=freopen("kfib.out","w",stdout);

int Sol[2][2], M[2][2], Aux[2][2], n;


void Multiply_1()
{
    int i, j, l;
    memset(Aux, 0, sizeof(Aux));

    for(i = 0; i < 2; ++i)
        for(j = 0; j < 2; ++j)
            for(l = 0; l < 2; ++l)
                Aux[i][j] = (1LL * Aux[i][j] + 1LL * Sol[i][l] * M[l][j]) % Mod;

    memcpy(Sol, Aux, sizeof(Sol));
}

void Multiply_2()
{
    int i, j, l;
    memset(Aux, 0, sizeof(Aux));

    for(i = 0; i < 2; ++i)
        for(j = 0; j < 2; ++j)
            for(l = 0; l < 2; ++l)
                Aux[i][j] = (1LL * Aux[i][j] + 1LL * M[i][l] * M[l][j]) % Mod;

    memcpy(M, Aux, sizeof(M));
}

void Pow(int p)
{
    int i = 1;
    M[0][0] = 0, M[0][1] = M[1][0] = M[1][1] = 1;

    for( ; i <= p; i <<= 1 )
    {
        if( i & p )
        {
            Multiply_1();
        }
        Multiply_2();
    }
}

int main()
{
    Sol[0][0] = Sol[1][1] = 1;
    scanf("%d", &n);

    Pow(n - 1);
    printf("%d", Sol[1][1]);

    return 0;
}
