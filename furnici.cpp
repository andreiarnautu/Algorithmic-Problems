// How about a coding trick?
#include <cstdio>
#include <algorithm>
using namespace std;

FILE *fin=freopen("furnici.in","r",stdin);
FILE *fout=freopen("furnici.out","w",stdout);

int main()
{
    int n, l, i, x;
    char c;
    int dCount = 0;
    scanf("%d %d", &l, &n);
    for(i = 1; i <= n; ++i)
    {
        scanf("%d %c", &x, &c);
        if( c == 'S' )
            dCount = max( dCount, x );
        else
            dCount = max( dCount, l - x );
    }
    printf("%d", dCount);
    return 0;
}
