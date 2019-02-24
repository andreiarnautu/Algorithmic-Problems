#include <cstdio>
using namespace std;
FILE *fin=freopen("grid.in","r",stdin);
FILE *fout=freopen("grid.out","w",stdout);
int N, K, A[4][30002], Nr[4];

void Read()
{
    scanf("%d%d", &N, &K);
    for(int i = 0 ; i < N ; ++i )
        A[0][i] = i + 1;
    for(int i = 0 ; i < N ; ++i )
        A[1][i] = N + i + 1;
    for(int i = 0 ; i < N ; ++i )
        A[2][i] = 2 * N + i + 1;
    Nr[0] = Nr[1] = Nr[2] = N;
}

void Change(int a, int b, int c, int d)
{
    int x;
    x = A[a][b];
    Nr[a]--;
    for(int i = b ; i <= Nr[a] ; ++i )
        A[a][i] = A[a][i + 1];
    Nr[c]++;
    for(int i = Nr[c] ; i > d ; --i )
        A[c][i] = A[c][i - 1];
    A[c][d] = x;
}

int main()
{
    int x, y, x1, y1;
    Read();
    for(int i = 1 ; i <= K ; ++i )
    {
        scanf("%d%d%d%d", &x, &y, &x1, &y1);
        Change(x, y , x1 , y1);
    }
    for(int i = 0 ; i < 3 ; ++i )
    {
        for(int j = 0 ; j < Nr[i] ; ++j )
            printf("%d ",A[i][j]);
        printf("\n");
    }
    return 0;
}
