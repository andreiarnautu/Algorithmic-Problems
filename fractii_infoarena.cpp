#include <cstdio>

using namespace std;

FILE *fin=freopen("fractii.in","r",stdin);
FILE *fout=freopen("fractii.out","w",stdout);

long long int cnt;
int V[1000013], N;

int main()
{
    scanf("%d", &N);

    for(int i = 2 ; i <= N ; ++i )
        V[i] = i - 1;

    for(int i = 2 ; i <= N ; ++i )
    {
        cnt += V[i];
        for(int j = i * 2 ; j <= N ; j += i )
            V[j] -= V[i];
    }

    printf("%lld", 2 * cnt + 1);

    return 0;
}
