#include <cstdio>
#include <cmath>
using namespace std;

FILE *fin=freopen("numar.in","r",stdin);
FILE *fout=freopen("numar.out","w",stdout);

int n, k, pos;
struct{int first, numbers;} V[100000];

void Find_Max()
{

    k = sqrt((double)2 * n);
    if(k * (k + 1) > 2 * n)
        --k;

}

void Check(int x)
{
    int sum, rest;
    sum = x * (x - 1) / 2;
    rest = n - sum;
    if( rest % x == 0 )
    {
        ++pos;
        V[pos].first = rest / x;
        V[pos].numbers = x;
    }
}

int main()
{
    scanf("%d", &n);
    Find_Max();
    for(int i = 2; i <= k ; ++i)
        Check(i);
    for(int i = 1; i <= pos ; ++i)
        printf("%d %d\n", V[i].first, V[i].numbers);
    for(int i = pos; i >= 1; --i)
        if( -V[i].first + 1 < 0 )
            printf("%d %d\n", -V[i].first + 1, V[i].numbers + 1 + 2 * (V[i].first - 1));

    printf("%d %d", - n + 1, 2 * n);
    return 0;
}
