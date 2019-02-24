#include <cstdio>
using namespace std;
FILE *fin = freopen("blockout.in", "r", stdin);
FILE *fout = freopen("blockout.out", "w", stdout);
int H[101][101], N, M;

int Check(int x1, int y1, int x2, int y2, int h)
{
    int Max = 0;
    for(int i = x1 ; i <= x2 ; ++i )
        for(int j = y1 ; j <= y2 ; ++j )
        {
            if( Max < H[i][j] )
                Max = H[i][j];
        }
    return Max;
}

void Plus(int x1, int y1, int x2, int y2, int Val)
{
    for(int i = x1 ; i <= x2 ; ++i )
        for(int j = y1 ; j <= y2 ; ++j )
            H[i][j] = Val;
}

void Solve()
{
    int x1, y1, x2, y2, h, k;
    for(int i = 1; i <= M ; ++i )
    {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &h);
        k = Check(x1, y1, x2, y2, h);
        printf("%d\n",k);
        Plus(x1, y1, x2, y2, k + h);
    }
}

int main()
{
    scanf("%d%d", &N, &M);
    Solve();
}
