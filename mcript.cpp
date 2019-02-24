#include <cstdio>
#include <vector>
#include <cstring>
#define Mod 100003

using namespace std;

FILE *fin=freopen("mcript.in","r",stdin);
FILE *fout=freopen("mcript.out","w",stdout);

vector <int> Hash[Mod + 3];
int C[12], n, m, k, Nr[12], nrcif;

void Read()
{
    int i, x;
    char s[11];
    scanf("%d", &n);getchar();gets(s);

    for( i = 0 ; i < strlen(s) ; ++i )
        C[i + 1] = s[i] - 48;


    for(i = 0 ; i <= Mod ; ++i)
        Hash[i].push_back(0);

    scanf("%d", &m);
    for(i = 1 ; i <= m ; ++i )
    {
        scanf("%d", &x);
        Hash[x % Mod][0]++;
        Hash[x % Mod].push_back(x / Mod);
    }

}

inline bool Search(int x)
{
    int i, last, c, r;

    last = Hash[x % Mod][0];
    c = x / Mod;
    r = x % Mod;
    for(i = 1; i <= last ; ++i )
        if(Hash[r][i] == c)
            return 1;
    return 0;
}

int Code(int k)
{
    int i, ret = 0;

    for(i = 0 ; i < 11 ; ++i)
        Nr[i] = 0;

    nrcif = 0;
    while( k )
    {
        Nr[++nrcif] = k % 10;
        k /= 10;
    }
    for(i = 1 ; i <= nrcif ; ++i)
        Nr[i] = C[Nr[i]];

    for(i = nrcif ; i > 0 ; --i)
        ret = ret * 10 + Nr[i];

    return ret;
}

void Solve_it()
{
    int k, nr, i, x;
    bool ok;

    for(scanf("%d", &k); k > 0 ; --k)
    {
        scanf("%d", &nr);
        ok = 1;

        for(i = 1; i <= nr ; ++i)
        {
            scanf("%d", &x);
            x = Code(x);
            if(!Search(x))
            {
                ok = 0;
            }
        }

        printf("%d\n",ok);
    }

}

int main()
{
    Read();
    Solve_it();
    return 0;
}
