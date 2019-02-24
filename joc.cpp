#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
FILE *fin=freopen("joc.in","r",stdin);
FILE *fout=freopen("joc.out","w",stdout);
int A[2003][1003], N, V[1003];

void Read()
{
    scanf("%d", &N);
    for(int i = 0 ; i < N ; ++i )
        scanf("%d", &V[i]);
}

void Solve()
{
    int No1, No2;
    for(int i = 1 ; i <= N  ; ++i )
        A[1][i - 1] = abs( V[i] - V[i - 1] );
    for(int i = 2 ; i <= N / 2 ; ++i )
        for(int j = 0 ; j <= N - 2 * i + 1 ; ++j )
        {
            if( V[j + 1] < V[j + 2 * i - 1] )
                No1 = V[j] - V[j + 2 * i - 1] + A[i - 1][j + 1];
            else
                No1 = V[j] - V[j + 1] + A[i - 1][j + 2];
            if( V[j + 2 * i - 2] > V[j] )
                No2 = V[j + 2 * i - 1] - V[j + 2 * i - 2] + A[i - 1][j];
            else
                No2 = V[j + 2 * i - 1] - V[j] + A[i - 1][j + 1];
            A[i][j] = max( No1 , No2 );
        }
    printf("%d", A[N / 2][0]);
}

int main()
{
    Read();
    Solve();
    return 0;
}
