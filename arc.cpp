// It's not the load that breaks you down, it's the way you carry it.

#include <cstdio>
#define DIM 10010
using namespace std;
FILE *fin=freopen("arc.in","r",stdin);
FILE *fout=freopen("arc.out","w",stdout);

int n, V[DIM];

void Solve1()
{
    int secvCount = 0;
    for(int i = 2; i <= n + 1; ++i)
        if( V[i] != V[i - 1] )
            ++secvCount;
    printf("%d\n", secvCount);
}

void Solve2()
{
    int i, i1, lenmax, first, last, n1, n2;

    while( 1 )
    {
        lenmax = 0;
        i1 = 1;

        for(i = 2; i <= n + 1; ++i)
            if( V[i] != V[i - 1] )
            {
                if( lenmax < i - i1 )
                {
                    lenmax = i - i1;
                    first = i1, last = i - 1;
                }
                i1 = i;
            }

        if( lenmax < 3 )
            break;

        while( 1 )
        {
            int elem1 = 0, elem2 = 0;


            for( n1 = first - 1; n1 > 0 && V[n1] == V[first - 1]; --n1, ++elem1);

            for( n2 = last + 1; n2 <= n && V[n2] == V[last + 1]; ++n2, ++elem2);

            ++n1, --n2;

            if( first > 1 && last < n && V[first - 1] == V[last + 1] &&  elem1 + elem2 > 2 )
                first = n1, last = n2;

            else
                break;
        }

        for(i = first; i + last - first + 1 <= n; ++i)
            V[i] = V[i + last - first + 1];

        n -= (last - first + 1);
        V[n + 1] = -1;
    }

    printf("%d\n", n);
    for(i = 1; i <= n; ++i)
        printf("%d\n", V[i]);
}

void Read()
{
    int op;
    scanf("%d %d", &op, &n);

    for(int i = 1; i <= n; ++i)
        scanf("%d", &V[i]);

    if( op == 1 )
        Solve1();
    else
        Solve2();
}

int main()
{
    Read();
}
