/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const long long mod = 1e9 + 7;

long long dp[1005][1005];
long long k, pa, pb;

long long Power(long long base, long long exp) {
  long long ans = 1, aux = base;
  for(long long i = 1; i <= exp; i <<= 1) {
    if(i & exp) {
      ans = ans * aux % mod;
    }
    aux = aux * aux % mod;
  }
  return ans;
}

int main() {
  scanf("%lld%lld%lld", &k, &pa, &pb);
  for(int i = 0; i < k; i++) {
    dp[k][i] = (k + i + pa * Power(pb, mod - 2)) % mod;
  }

  for(int i = k - 1; i >= 1; i--) {
    for(int j = k - 1; j >= 0; j--) {
      long long val = i + j;
      if(i + j < k) {
        val = dp[i][i + j];
      }
      dp[i][j] = (pa * dp[i + 1][j] + pb * val) % mod;
      dp[i][j] = dp[i][j] * Power(pa + pb, mod - 2) % mod;
    }
  }

  printf("%lld\n", dp[1][0]);
	return 0;
}
