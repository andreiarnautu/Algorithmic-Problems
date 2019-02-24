#include <cstdio>
using namespace std;
FILE *fin=freopen("fib.in","r",stdin);
FILE *fout=freopen("fib.out","w",stdout);
int N, K = 2, KK;
int A1[30003], A2[30003], A3[30003];

void Modify()
{
    int i, t = 0;
    for( i = 1 ; i <= A1[0] || i <= A2[0] || t ; t /= 10 , ++i )
        A3[i] = ( t += A1[i] + A2[i] ) % 10;
    A3[0] = i - 1;
    for( i = 0 ; i <= A2[0] ; ++i )
        A1[i] = A2[i];
    for( i = 0 ; i <= A3[0] ; ++i )
        A2[i] = A3[i];
}

int main()
{
    A1[0] = A2[0] = A1[1] = A2[1] = 1;
    scanf("%d", &N);
    if( N == 1 || N == 2 )
        printf("1");
    else
    {
        while( K < N )
        {
            KK = K;
            K += A3[0];
            Modify();
        }
        printf("%d", A1[A1[0] - N + KK + 1]);
    }
    return 0;
}

