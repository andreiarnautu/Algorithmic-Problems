#include <cstdio>
#define Dim 1003

using namespace std;

FILE *fin=freopen("gradina3.in","r",stdin);
FILE *fout=freopen("gradina3.out","w",stdout);

int N, P, K, A[Dim][Dim], Sum[Dim][Dim];

void Read()
{
    scanf("%d%d%d", &N, &P, &K);

    int x, y;
    for(int i = 1 ; i <= P ; ++i )
    {
        scanf("%d%d", &x, &y);
        A[x][y] = 1;
    }

}

void Build_Sums()
{
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= N ; ++j )
        {
            Sum[i][j] = Sum[i - 1][j] + Sum[i][j - 1] - Sum[i - 1][j - 1] + A[i][j];
        }
}

void Gardening()
{
    int Max = 0, cnt, nr;

    for(int i = K ; i <= N ; ++i )
        for(int j = K ; j <= N ; ++j )
        {
            nr = Sum[i][j] - Sum[i - K][j] - Sum[i][j - K] + Sum[i - K][j - K];
            if( nr > Max )
                Max = nr , cnt = 1;
            else if( nr == Max )
                ++cnt;
        }

    printf("%d\n%d", Max , cnt);
}

int main()
{
    Read();
    Build_Sums();
    Gardening();
}
