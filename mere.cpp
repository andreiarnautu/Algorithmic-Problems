#include <cstdio>
using namespace std;
FILE *fin=freopen("mere.in","r",stdin);
FILE *fout=freopen("mere.out","w",stdout);
long long int N, K, T, P;


int main()
{
    scanf("%lld", &T);
    for(int i = 1 ; i <= T ; ++i )
    {
        scanf("%lld%lld", &N, &K);
        P = K * 2;
        if( N < K )
            printf("Remiza\n");
        else if( (N / K) % 2 == 0 && N % K == 0 )
            printf("Remiza\n");
        else
            printf("Santa Klaus\n");
    }
    return 0;
}
