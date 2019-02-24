#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *fin=freopen("calatorie.in","r",stdin);
FILE *fout=freopen("calatorie.out","w",stdout);

long long int N, A[51][501], Sum;
bool Used[51][501];


void Run()
{
    int a, b;
    scanf("%d", &N);
    if( N == 1 )
    {
        printf("Consumul minim = 0.\n");
        return;
    }

    memset(Used , 0 , sizeof(Used));
    memset(A, 0 , sizeof(A));

    Sum = 0;
    Used[0][0] = 1;
    for(int i = 1 ; i < N ; ++i )
    {
        scanf("%d%d", &a, &b);
        for(int j = 0 ; j <= Sum ; ++j )
            if( Used[i - 1][j] )
            {
                if( A[i][j + b] == 0 || A[i - 1][j] < A[i][j + b] )
                {
                    A[i][j + b] = A[i - 1][j];
                    Used[i][j + b] = 1;
                }
                if( A[i][j] == 0 || A[i - 1][j] + a < A[i][j] )
                {
                    A[i][j] = A[i - 1][j] + a;
                    Used[i][j] = 1;
                }
            }
        Sum += b;
    }

    long long int Min = 100000000000000;
    for(long long int i = 0 ; i <= Sum ; ++i )
        if( Used[N - 1][i] && A[N - 1][i] + i * i * i *i <= Min )
            Min = A[N - 1][i] + i * i * i * i;

    printf("Consumul minim = %lld.\n", Min);
}

int main()
{
    int T;
    scanf("%d", &T);
    for(int i = 1 ; i <= T ; ++i )
        Run();
    return 0;
}
