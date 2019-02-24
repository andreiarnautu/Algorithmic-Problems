#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin=freopen("noname2.in","r",stdin);
FILE *fout=freopen("noname2.out","w",stdout);
long long int N, K, V[100002], S[100002], Max, Sum, Nr;


void Read()
{
    long long int x;
    scanf("%lld%lld", &N, &K);
    for(int i = 1 ; i <= N ; ++i )
    {
        scanf("%lld", &x);
        V[i] = x;
       // S[i] = x + S[i - 1];
    }
}

long long int Abs(long long int a, long long int b)
{
    if( a >= b )
        return a - b;
    return b - a;
}

void Solve()
{
    sort( V + 1 , V + N + 1 );
    for(int i = 1 ; i <= N ; ++i )
    {
        S[i] = S[i - 1] + V[i];
    }
    for(int i = 1 ; i < N ; ++i )
    {
        for(int j = N ; j > i && j - i + 1 > Max ; --j )
        {
            Sum = S[j] - S[i - 1];
            Sum /= ( j - i + 1 );
            Nr = 0;
            for(int l = i ; l <= j ; ++l )
                Nr += Abs( Sum , V[l] );
            if( Nr <= K && Max <= j - i + 1)
                Max = j - i + 1;
        }
    }
    printf("%lld", Max);
}

int main()
{
    Read();
    Solve();
}
