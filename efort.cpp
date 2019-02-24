#include <cstdio>
using namespace std;
FILE *fin=freopen("efort.in","r",stdin);
FILE *fout=freopen("efort.out","w",stdout);
int N, K, V[1003], Fib[46];

void Read()
{
    scanf("%d%d", &N, &K);
    for(int i = 1 ; i <= N ; ++i )
        scanf("%d", &V[i]);
}

void Init()
{
    Fib[0] = 1;
    Fib[1] = 2;
    for(int i = 2 ; i <= 45 ; ++i )
        Fib[i] = Fib[i - 1] + Fib[i - 2];
}

void Solve()
{
    long long int Sol = 0;
    for(int i = 1 ; i <= N ; ++i )
    {
        int j = i, nr = 0, Rest;
        while( j <= N && nr < K )
        {
            nr += V[j];
            ++j;
        }
        i = j - 1;
        if( i == N && nr < K )
        {
            Sol += nr;
            break;
        }
        Rest = nr - K;
        for(int l = 1 ; l <= Rest ; ++l )
            Sol += Fib[l];
        Sol += K;
    }
    printf("%lld\n", Sol);
}

int main()
{
    Read();
    Init();
    Solve();
    return 0;
}
