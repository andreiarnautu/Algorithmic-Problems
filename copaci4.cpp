#include <cstdio>
#include <cstring>
#include <algorithm>
#define MaxN 200013
#define MaxH 203

using namespace std;

FILE *fin=freopen("copaci4.in","r",stdin);
FILE *fout=freopen("copaci4.out","w",stdout);

int N, V[MaxN], Left[MaxN], Right[MaxN];
int aux[MaxH], cnt;


void Read()
{
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
}

void Build_Left()
{
    memset(aux, 0, sizeof(aux));
    int val;

    for(int i = 1 ; i <= N ; ++i )
    {
        val = 0;

        for(int j = V[i] ; j < MaxH ; ++j )
                val = max( val , aux[j] );

        Left[i] = val;
        aux[V[i]] = i;
    }
}

void Build_Right()
{
    memset(aux, 0, sizeof(aux));
    int val;

    for(int i = N ; i > 0 ; --i )
    {
        val = N + 1;

        for(int j = V[i]; j <= MaxH ; ++j )
            if( aux[j] )
                val = min( val, aux[j] );

        Right[i] = val;
        aux[V[i]] = i;
    }
}

void Solve_the_Problem()
{
    int q1, q2;

    for(int i = 2 ; i < N ; ++i )
    {
        q1 = Left[i];
        q2 = Right[i];

        if( q1 == 0 || q2 == N + 1 )
            continue;

        if( Right[q1] >= q2 && Left[q2] <= q1 )
            ++cnt;
    }

    printf("%d", cnt);
}

int main()
{
    Read();
    Build_Left();
    Build_Right();
    Solve_the_Problem();
    return 0;
}
