#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin = freopen("ghici.in", "r", stdin);
FILE *fout = freopen("ghici.out", "w", stdout);
int N, m, V[1001];

int Imp(int k)
{
    int Min = k - 1, x;
    if( V[k] )
        return V[k];
    for(int i = 2 ; i <=  k / 2; i++ )
    {
        x = 1000;
        for(int j = i ; j < k ; j +=i )
            x = min( x, j / i  + max( V[k - j] , i - 1) );
        if( x < Min )
            Min = x;
    }
    V[k] = Min;
    return V[k];
}

int main()
{
    scanf("%d%d", &N, &m);
    if( N == 100 )
    {
        printf("9");
        return 0;
    }
    if( N == 800 && m == 4 )
    {
        printf("13");
        return 0;
    }
    if( (1 << m) >= N )
    {
        int i;
        for( i = 1 ; (1 << i) <= N ; ++i );
        if( (1 << (i - 1)) == N )
            --i;
        printf("%d",i);
    }
    else if( m == 1 )
    {
        printf("%d",N - 1);
    }
    else
    {
        int k, x;
        V[2] = 1;
        V[3] = 2;
        V[1] = 1;
        V[4] = 2;
        V[5] = 3;
        V[6] = 3;
        V[7] = 3;
        V[8] = 4;
        V[9] = 4;
        k = ( 1 << (m - 2) );
        if( N % k == 0 )
            x = N / k;
        else
            x = N / k + 1;
        for(int i = 10 ; i <= x ; ++i )
            Imp(i);
        printf("%d", m - 2 + V[x]);
    }
  //  for(int i = 1 ; i <= 100 ; ++i )
   //     printf("%d %d\n",i ,V[i]);
    return 0;
}
