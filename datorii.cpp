#include <cstdio>
#define zeros(x) (x ^ (x - 1)) & x
#define Dim 100013
using namespace std;

FILE *fin=freopen("datorii.in","r",stdin);
FILE *fout=freopen("datorii.out","w",stdout);

int AIB[Dim];
int n, m;

void Add(int pos, int val)
{
    int i;
    for(i = pos ; i <= n ; i += zeros(i) )
        AIB[i] += val;
}

int Compute(int pos)
{
    int i, val = 0;
    for(i = pos ; i > 0 ; i -= zeros(i) )
        val += AIB[i];
    return val;
}

void Read_and_Initialize()
{
    int i, x;
    scanf("%d%d", &n, &m);

    for(i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &x);
        Add(i, x);
    }
}

void Solve_the_Problem()
{
    int op, a, b;

    for(int i = 1 ; i <= m ; ++i )
    {
        scanf("%d%d%d", &op, &a, &b);

        if( op == 0 )
            Add(a, -b);
        else
            printf("%d\n", Compute(b) - Compute(a - 1));
    }
}


int main()
{
    Read_and_Initialize();
    Solve_the_Problem();
    return 0;
}
