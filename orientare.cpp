#include <cstdio>
#include <algorithm>
#define Mod 666013
using namespace std;
FILE *fin=freopen("orientare.in","r",stdin);
FILE *fout=freopen("orientare.out","w",stdout);

long A[451][451], B[451][451], C[451][451], N, M;

void Read()
{
    int x;
    scanf("%d%d", &N, &M);
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= M ; ++j )
        {
            scanf("%d", &x);
            A[i][j] = A[i][j - 1] + x;
        }
    for(int i = 1 ; i <= M ; ++i )
        C[0][i] = 1;
    for(int i = 1 ; i <= N ; ++i )
        for(int j = 1 ; j <= M ; ++j )
        {
            if(i >= 1)
            {
                B[i][j] = B[i - 1][j] + A[i][j] - A[i][j - 1];
                C[i][j] = C[i - 1][j];
            }
            for(int l = 1 ; l < j ; ++l )
                {
                    if( B[i - 1][l] + A[i][j] - A[i][l - 1] > B[i][j] )
                    {
                        C[i][j] = C[i - 1][l];
                        B[i][j] = B[i - 1][l] + A[i][j] - A[i][l - 1];
                    }
                    else if( B[i - 1][l] + A[i][j] - A[i][l - 1] == B[i][j] )
                        C[i][j] = 1ll * (C[i][j] + C[i - 1][l]) % Mod;
                }
            for(int l = j + 1 ; l <= M ; ++l )
            {
                if( B[i - 1][l] + A[i][l] - A[i][j - 1] > B[i][j] )
                {
                    C[i][j] = C[i - 1][l];
                    B[i][j] = B[i - 1][l] + A[i][l] - A[i][j - 1];
                }
                else if( B[i - 1][l] + A[i][l] - A[i][j - 1] == B[i][j] )
                    C[i][j] = (C[i][j] + C[i - 1][l]) % Mod;
            }
        }
    int Max = -100000000;
    for(int i = 1 ; i <= M ; ++i )
        if( B[N][i] > Max )
            Max = B[N][i];
    printf("%d\n", Max);
    int Sol = 0;
    for(int i = 1 ; i <= M ; ++i )
        if( Max == B[N][i] )
            Sol = (Sol + C[N][i]) % Mod;
    printf("%d\n", Sol);
}

int main()
{
    Read();
    return 0;
}
