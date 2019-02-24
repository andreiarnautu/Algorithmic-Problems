#include <cstdio>
#define zeros(x) ((x ^ (x - 1) & x))
using namespace std;

FILE *fin=freopen("aib.in","r",stdin);
FILE *fout=freopen("aib.out","w",stdout);
int AIB[100013], n, m;


void Add(int x, int val)
{
    for(int i = x ; i <= n ; i += zeros(i) )
        AIB[i] += val;
}

int Compute(int x)
{
    int sol = 0, i;

    for(i = x ; i > 0 ; i -= zeros(i) )
        sol += AIB[i];

    return sol;
}

void Read()
{
    scanf("%d%d", &n, &m);

    int x;
    for(int i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &x);
        Add(i, x);
    }
}

void Solve_it()
{
    int i, op, a, b, j, power, aux, pos;

    for(power = 1 ; power < n ; power <<= 1 );

    for(i = 1 ; i <= m ; ++i )
    {
        scanf("%d%d", &op, &a);

        if( op == 0 )
        {
            scanf("%d", &b);
            Add(a, b);
        }

        else if( op == 1 )
        {
            scanf("%d", &b);
            printf("%d\n", Compute(b) - Compute(a - 1) );
        }


        else
        {
            pos = -1;
            for(j = 0, aux = power ; aux ; aux >>= 1)
                if(j + aux <= n)
                {
                    if(a >= AIB[j + aux])
                    {
                        j += aux;
                        a -= AIB[j];
                        if( !a )
                            pos = j;
                    }
                }
           printf("%d\n", pos);
        }
    }
}

int main()
{
    Read();
    Solve_it();
    return 0;
}
