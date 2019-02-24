/*
    Worg
*/
#include <cstdio>
#include <vector>
#include <cstring>

#define MOD 100003
#define MOD_2 666013
#define DIM 10000010
#define sigma 3

using namespace std;
FILE *fin = freopen("abc2.in","r",stdin);
FILE *fout = freopen("abc2.out","w",stdout);

vector <unsigned int> Hash[ MOD ];
char T[ DIM ], F[ 30 ];
int len_1, len_2;
unsigned int x1, x2, rest_1;

inline int val( char x )
{
    return (int) x - 'a';
}

inline void giveValues()
{
    x1 = 0;
    for(int i = 0; i < len_2; ++i)
    {
        x1 = (x1 * sigma + val( F[i] ));
    }
}

inline bool Find(unsigned int q1)
{
    unsigned int q2 = q1 % MOD;
    for(int i = 0; i < Hash[q2].size(); ++i)
        if( Hash[q2][i] == q1 )
            return 1;
    return 0;
}

void Read()
{
    scanf("%s", T);
    len_1 = strlen( T );
    while( scanf("%s", F) )
    {
        len_2 = strlen( F );
        giveValues();
        Hash[x1 % MOD].push_back(x1);
    }
}

void Solve()
{
    int i, ans = 0;
    unsigned int q1 = 0;

    rest_1 = sigma;
    for(i = 0; i < len_2; ++i)
    {
        q1 = (q1 * sigma + val( T[i] ) );
        if( i > 1 )
            rest_1 = (rest_1 * sigma);
    }

    ans += Find(q1);

    for(i = len_2; i < len_1; ++i)
    {
        q1 -= val( T[i - len_2] ) * rest_1;
        q1 = (q1 * sigma + val( T[i] ) );

        ans += Find(q1);
    }
    printf("%d", ans);
}

int main()
{
    Read();
    Solve();
    return 0;
}
