#include <cstdio>
#include <cmath>
using namespace std;

FILE *fin=freopen("chiftea.in","r",stdin);
FILE *fout=freopen("chiftea.out","w",stdout);

int a;

int main()
{
    int x, sol, rest, t;
    for(scanf("%d", &t); t > 0; --t)
    {
        scanf("%d", &a);
        x = sqrt((double)a);
        sol = 4 * x;
        rest = a - x * x;
        if(rest)
        {
            if(rest > x)
                sol += 4;
            else
                sol += 2;
        }
        printf("%d\n", sol);
    }
    return 0;
}
