#include <cstdio>
#define MaxN 2003
#define Inf 2000000000

using namespace std;

FILE *fin=freopen("minim.in","r",stdin);
FILE *fout=freopen("minim.out","w",stdout);

int V[MaxN];
int n;


int main()
{
    bool ok;
    int i, Min, first, last, p, Sum, nr = 0;

    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++i )
        scanf("%d", &V[i]);

    //for(int i = 1 ; i <= n ; ++i )
       // printf("%d ", V[i]);

    do
    {
        ok = 0;
        Min = Inf;
        p = 1;
        first = last = 1;
        Sum = 0;

        for( i = 1 ; i <= n ; ++i )
            if( V[i] != Inf )
            {
                p = i;
                break;
            }

        for( i = 1 ; i <= n ; ++i )
        {
            if( Sum > 0 && V[i] != Inf )
            {
                Sum = 0;
                p = i;
            }

            if( V[i] == Inf )
                continue;

            Sum += V[i];
            if( Sum < Min )
            {
                Min = Sum;
                first = p;
                last = i;
                ok = 1;
            }

            else if( Sum == Min && first - last > i - p )
            {
                first = p;
                last = i;
            }
        }

        printf("%d %d %d\n", Min, first, last);

        for( i = first ; i <= last ; ++i )
            V[i] = Inf;

        nr += last - first + 1;

    }while(nr < n);
}
