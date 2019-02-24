// It's not the load that breaks you down, it's the way you carry it.
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define DIM 240000
using namespace std;
FILE *fin=freopen("momente.in","r",stdin);
FILE *fout=freopen("momente.out","w",stdout);

const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int pal[DIM], V[10];
int cnt, l1, z1, h1, m1, s1, l2, z2, h2, m2, s2, D;
char S[3];

inline bool palindrom(int nr)
{
    memset(V, 0, sizeof(V));
    while( nr )
    {
        ++V[0];
        V[V[0]] = nr % 10;
        nr /= 10;
    }

    for(int i = 1; i <= V[0] / 2; ++i)
        if( V[i] != V[V[0] - i + 1] )
            return 0;
    return 1;
}

void Gen()
{
    int i, j, l, nr;

    for(i = 0; i <= 23; ++i)
        for(j = 0; j < 60; ++j)
            for(l = 0; l < 60; ++l)
            {
                nr = l + j * 100 + i * 10000;

                if( palindrom(nr) )
                    ++cnt;

                pal[nr] = cnt;
            }
    pal[-1] = 0;

    for(i = 0; i <= DIM; ++i)
        if( !pal[i] )
            pal[i] = pal[i - 1];

}

void Finish()
{
    int i, nr1, nr2;
    long long int sol = 0;
    D = 0;

    if( l1 != l2 )
    {
        sol = 1LL * (days[l1] - z1) * cnt;
        sol += 1LL * (z2 - 1) * cnt;

        for(i = l1 + 1; i < l2; ++i)
            sol += 1LL * cnt * days[i];

        nr1 = h1 * 10000 + m1 * 100 + s1;
        nr2 = h2 * 10000 + m2 * 100 + s2;

        sol += 1LL * ( cnt - pal[nr1 - 1] );
        sol += 1LL * pal[nr2];
    }

    else
    {
        for(i = z1 + 1; i < z2; ++i)
            sol += cnt;

        nr1 = h1 * 10000 + m1 * 100 + s1;
        nr2 = h2 * 10000 + m2 * 100 + s2;

        if( z1 != z2 )
        {
            sol += 1LL * ( cnt - pal[nr1 - 1] );
            sol += 1LL * ( pal[nr2] );
        }

        else
            sol += pal[nr2] - pal[nr1 - 1];
    }
    printf("%lld\n", sol);
}

void Read()
{
    scanf("%s", S); l1 = atoi(S);
    scanf("%s", S); z1 = atoi(S);
    scanf("%s", S); h1 = atoi(S);
    scanf("%s", S); m1 = atoi(S);
    scanf("%s", S); s1 = atoi(S);

    scanf("%s", S); l2 = atoi(S);
    scanf("%s", S); z2 = atoi(S);
    scanf("%s", S); h2 = atoi(S);
    scanf("%s", S); m2 = atoi(S);
    scanf("%s", S); s2 = atoi(S);
}

int main()
{
    Gen();
    int k;
    for(scanf("%d", &k); k > 0; --k)
       {
           Read();
           Finish();
       }

    return 0;
}
