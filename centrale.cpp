#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin=freopen("centrale.in","r",stdin);
FILE *fout=freopen("centrale.out","w",stdout);

char s[10];
int n;

void Solve()
{
    int ansCount = 0, ok;

    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i)
    {
        scanf("%s", s);
        ok = 1;
        for(int j = 2; j < strlen(s) - 1; ++j)
            if( s[j] != s[j - 1] )
                ok = 0;
        if( ok )
            ++ansCount;
    }

    printf("%d", ansCount);
}

int main()
{
    Solve();
    return 0;
}
