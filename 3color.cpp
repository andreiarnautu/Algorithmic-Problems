#include <cstdio>
#include <cstring>
#define VMax 1003
using namespace std;

FILE *fin=freopen("3color.in","r",stdin);
FILE *fout=freopen("3color.out","w",stdout);

bool A[VMax][VMax];
int V, E, F[101], C[VMax];


int main()
{
    scanf("%d%d", &V, &E);

    int x, y;
    for(int i = 1 ; i <= E ; ++i )
    {
        scanf("%d%d", &x, &y);
        A[x][y] = A[y][x] = 1;
    }

    printf("0 ");

    for(int i = 1 ; i < V ; ++i )
    {
        for(int j = 0 ; j < 100 ; ++j )
            F[j] = 0;

        for(int j = 0 ; j < i ; ++j )
        {
            if( A[i][j] == 1 )
            {
                F[C[j]] = 1;
            }
        }
        for(int j = 0 ; j < 100 ; ++j )
            if( F[j] == 0 )
            {
                C[i] = j;
                printf("%d ", C[i]);
                break;
            }
    }

    return 0;
}
