#include <cstdio>
#include <algorithm>

using namespace std;

FILE *fin=freopen("jocul.in","r",stdin);
FILE *fout=freopen("jocul.out","w",stdout);

int F[1000000], V[1003];
int n, Max, Sum, Half, Diffmin = 1000000000, s1, s2;


void Read()
{
    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++i )
    {
        scanf("%d", &V[i]);
        Sum += V[i];
    }

    Half = Sum / 2;
    F[0] = 1;
}

void Solve_Dynamic()
{
    int i, j;
    for(i = 1 ; i <= n ; ++i )
    {
        for(j = Max; j >= 0 ; --j )
            if( F[j] )
            {
                F[j + V[i]] = 1;
                if( abs(2 * (j + V[i]) - Sum) < Diffmin )
                {
                    Diffmin = abs(2 * (j + V[i]) - Sum);
                    s1 = j + V[i];
                    s2 = Sum - j - V[i];
                }
            }
        Max += V[i];
        if( Max > Half )
            Max = Half;
    }

    int aux;
    if( s2 < s1 )
    {
        aux = s1;
        s1 = s2;
        s2 = aux;
    }

    printf("%d %d", s1, s2);
}

int main()
{
    Read();
    Solve_Dynamic();

    return 0;
}
