#include <cstdio>
#include <cstring>
#define zeros(x) (x ^ (x - 1)) & x
#define MaxN 100013

using namespace std;

FILE *fin=freopen("baruri.in","r",stdin);
FILE *fout=freopen("baruri.out","w",stdout);

int AIB[MaxN];
int m, n;

void Add(int pos, int val)
{
    int i;
    for(i = pos; i <= n ; i += zeros(i) )
        AIB[i] += val;
}

int Compute(int pos)
{
    int i, val = 0;

    if(pos < 0)
        return 0;

    if(pos > n)
        pos = n;

    for(i = pos ; i > 0 ; i -= zeros(i))
        val += AIB[i];
    return val;
}

void Solve_the_Problem()
{
    int x, i, op, a, b, c;
    memset(AIB, 0, sizeof(AIB));

    scanf("%d", &n);
    for( i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &x);
        Add(i, x);
    }

    scanf("%d", &m);

    for(i = 1 ; i <= m ; ++i )
    {
        scanf("%d%d%d", &op, &a, &b);

        if( op == 0 )
        {
            printf("%d\n", Compute(a + b) - Compute(a) + Compute(a - 1) - Compute(a - b - 1));
        }

        else if( op == 1 )
        {
            Add(b, a);
        }

        else if( op == 2 )
        {
            Add(b, -a);
        }

        else
        {
            scanf("%d", &c);
            Add(b, -a);
            Add(c, a);
        }
    }
}

int main()
{
    int t;
    for(scanf("%d", &t); t > 0 ; --t )
        Solve_the_Problem();
    return 0;
}
