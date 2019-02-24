#include <cstdio>
using namespace std;
FILE *fin=freopen("ornament.in","r",stdin);
FILE *fout=freopen("ornament.out","w",stdout);

struct patrat{int N, E, S, V;};
int n, op, ansCount, stop, rad;
patrat A[20], Sol[20];
int Ord[20];
int viz[20];

void Read()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d %d %d %d ", &A[i].N, &A[i].E, &A[i].S, &A[i].V);
    if( n == 9 )
        rad = 3;
    if( n == 4 )
        rad = 2;
    if( n == 16 )
        rad = 4;
    scanf("%d", &op);
}

void Verif()
{
    if( op == 1 )
    {
        for(int i = 1, p = 0; i * i <= n; ++i, p += rad)
            {
            for(int j = 1; j * j <= n ; ++j)
                printf("%d ", Ord[p + j]);
            printf("\n");
            }
        stop = 1;
    }
}

inline int f(int k)
{
    while( k > rad )
        k -= rad;
    return k;
}

void Gen(int nr)
{
    if( stop )
        return;
    if( nr > n )
    {
        ++ansCount;
        if( op == 1 )
            Verif();
    }
    else
    {
        bool ok;
        for(int i = 1; i <= n; ++i)
            if( !viz[i] )
            {
                ok = 1;
                if( f(nr) != 1 )
                    if( A[i].V != Sol[nr - 1].E )
                        ok = 0;
                if( nr > rad )
                    if( A[i].N != Sol[nr - rad].S )
                        ok = 0;
                if( ok )
                {
                    viz[i] = 1;
                    Ord[nr] = i;
                    Sol[nr].E = A[i].E, Sol[nr].V = A[i].V, Sol[nr].S = A[i].S, Sol[nr].N = A[i].N;
                    //Sol[nr] = A[i];
                    Gen( nr + 1 );
                    viz[i] = 0;
                }
            }

    }
}

int main()
{
    Read();
    Gen(1);
    if( op == 2 )
        printf("%d", ansCount);
    return 0;
}
