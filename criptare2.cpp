/*
    Worg
*/
#include <cstdio>
#include <set>
#include <cstring>

#define I64 long long int
#define MOD_1 100003
#define MOD_2 104003
#define coef 1000000
#define sigma 27

using namespace std;
FILE *fin=freopen("criptare2.in","r",stdin);
FILE *fout=freopen("criptare2.out","w",stdout);

set < I64 > myset;
int n, m;
int F[sigma];
char S[30];

inline long long int giveValue()
{
    for(int i = 0; i <= 26; ++i)
        F[i] = 0;
    int nr = 0, len = strlen(S);
    int val_1 = 0, val_2 = 0;
    long long int ret;


    for(int i = 0; i < len; ++i)
    {
        if( !F[ S[i] - 'a'] )
            F[ S[i] - 'a' ] = ++nr;
        val_1 = ( val_1 * (sigma + 1) + F[ S[i] - 'a'] ) % MOD_1;
        val_2 = ( val_2 * (sigma + 1) + F[ S[i] - 'a'] ) % MOD_2;
    }
    ret = 1LL * val_1 * coef + 1LL * val_2;
    return ret;
}

void Set()
{
    scanf("%d", &n);

    long long int val;
    for(int i = 1; i <= n; ++i)
    {
        scanf("%s", S);
        val = giveValue();
        myset.insert( val );
    }
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i)
    {
        scanf("%s", S);
        val = giveValue();
        if( myset.find( val ) != myset.end() )
            printf("1\n");
        else
            printf("0\n");
    }
}

int main()
{
    Set();
    return 0;
}
