#include <cstdio>
#include <algorithm>

using namespace std;

FILE *fin=freopen("arbint.in","r",stdin);
FILE *fout=freopen("arbint.out","w",stdout);

int Aint[500003], N, M, Val, Pos, op, Max, first, last;



void Update(int nod, int left, int right)
{
    int m;
    if( left == right )
    {
        Aint[nod] = Val;
        return;
    }

    m = (left + right) >> 1;

    if( Pos <= m )
        Update(2 * nod, left , m);
    else
        Update(2 * nod + 1 , m + 1 , right);

    Aint[nod] = max( Aint[2 * nod] , Aint[2 * nod + 1] );

}

void Answer(int nod, int left, int right)
{
    int m;

    if( first <= left && right <= last )
    {
        Max = max( Max, Aint[nod] );
        return;
    }

    m = (left + right) / 2;
    if( first <= m )
        Answer(2 * nod, left, m);
    if( m < last )
        Answer(2 * nod + 1, m + 1, right);
}

int main()
{
    scanf("%d%d", &N, &M);
    int a, b;

    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%d", &Val);
        Pos = i;
        Update(1, 1, N);
    }

    for(int i = 1 ; i <= M ; ++i )
    {
        scanf("%d%d%d", &op, &a, &b);

        if( op )
        {
            Pos = a;
            Val = b;
            Update(1, 1, N);
        }

        else
        {
            Max = -1;
            first = a, last = b;
            Answer(1, 1, N);
            printf("%d\n", Max);
        }
    }

    return 0;
}
