#include <cstdio>
using namespace std;
FILE *fin=freopen("latin.in","r",stdin);
FILE *fout=freopen("latin.out","w",stdout);
int N, A[501][501];
void Read()
{
    scanf("%d",&N);
    for(int i=1; i<=N ; ++i)
        for(int j=1; j<=N ; ++j)
            scanf("%d",&A[i][j]);
}
void Solve(int x, int y)
{
    int k;
    if(x>=y)
        k = N - x;
    else
        k = N - y;

}

int main()
{
    Read();
    for(int i=1; i<N ; i++)
        for(int j=1; j<N ; ++j)
            Solve(i,j);
    return 0;
}
