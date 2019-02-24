/**
  *  Worg
  */
#include <cstdio>

#define Dim 505

using namespace std;
FILE *fin=freopen("expozitie.in","r",stdin);
FILE *fout=freopen("expozitie.out","w",stdout);

int n, k, d;
long long int dp[Dim][Dim];

void build() {

    for(int i = 1; i <= d; ++i)
        dp[1][i] = i;

    for(int i = 2; i <= n; ++i)
        for(int j = 1; j <= d; ++j)
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
}

int main() {

    scanf("%d %d %d", &n, &d, &k);
    n -= k * d;

    if( n < 0 ) {
        printf("0"); return 0;
    }

    if( n == 0 ) {
        printf("1"); return 0;
    }

    build();
    printf("%lld", dp[n][d]);
    return 0;
}
