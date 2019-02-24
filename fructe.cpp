#include <cstdio>
using namespace std;
FILE *fin=freopen("fructe.in","r",stdin);
FILE *fout=freopen("fructe.out","w",stdout);

int main()
{
    int p, b, t;
    for(scanf("%d", &t); t > 0 ; --t)
    {
        scanf("%d%d", &p, &b);
        if( b % 2 == 0 )
            printf("0\n");
        else printf("1\n");
    }
    return 0;
}
