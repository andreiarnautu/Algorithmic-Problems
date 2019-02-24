#include <cstdio>
#include <cmath>
using namespace std;

FILE *fin=freopen("maxunice.in","r",stdin);
FILE *fout=freopen("maxunice.out","w",stdout);

long long int n, k;

void Find_Max()
{
    scanf("%lld", &n);
    n *= 2;

    k = sqrt((double)n);
    if(k * (k + 1) > n)
        --k;

}

void Write()
{
    long long int i, Diff;
    Diff = n - k * (k + 1);
    Diff /= 2;

    printf("%lld\n", k);

    for(i = 1; i <= k; ++i)
    {
        if( k - Diff + 1 <= i )
            printf("%lld\n",i + 1);
        else
            printf("%lld\n",i);
    }
}

int main()
{
    Find_Max();
    Write();
    return 0;
}
