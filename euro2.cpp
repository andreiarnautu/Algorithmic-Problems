#include <cstdio>
#define MaxN 10003
#define INF 10.000000
using namespace std;
FILE *fin=freopen("euro2.in","r",stdin);
FILE *fout=freopen("euro2.out","w",stdout);

float V[MaxN];
int P[2][MaxN], Len[2];
float Q[2][MaxN];
int n;

void Read()
{
    scanf("%d ", &n);
    for(int i = 1; i <= n ; ++i)
        scanf("%f ", &V[i]);
}

int Insert(int k, float val, int left, int right)
{
    int mid = (left + right) / 2;

    if(left == right)
    {
        if( right > Len[k] )
            Q[k][++Len[k] + 1] = INF;
        Q[k][right] = val;
        return right;
    }

    if(val <= Q[k][mid])
        return Insert(k, val, left, mid);
    return Insert(k, val, mid + 1, right);
}

void BuildPQ(int k)
{
    int i;
    Len[k] = 0;
    Q[k][1] = INF;

    if(!k)
    {
        for(i = 1; i <= n ; ++i)
            P[k][i] = Insert(k, V[i], 1, Len[k] + 1);
    }
    else
    {
        for(i = n; i > 0 ; --i)
            P[k][i] = Insert(k, V[i], 1, Len[k] + 1);
    }
}

int main()
{
    int best = 0;
    Read();
    BuildPQ(0);
    BuildPQ(1);
    for(int i = 1; i <= n ; ++i)
    {
        if( P[0][i] >= 2 && P[1][i] >= 2 && P[0][i] + P[1][i] - 1 > best )
            best = P[0][i] + P[1][i] - 1;
    }
    printf("%d", best);
    return 0;
}
