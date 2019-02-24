/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

const int maxN = 500 + 5;

/*-------- Data --------*/
int n, p;
int comb[maxN][maxN];

int cnt[maxN];
/*-------- --------*/

void Precompute() {
  for(int i = 0; i <= n; i++) {
    comb[i][0] = 1;

    for(int j = 1; j <= i; j++) {
      comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % p;
    }
  }
}

void Compute(const int k) {
  std::vector<int > dp(n + 1, 0), prevDp(n + 1, 0);

  dp[n] = 1;
  for(int i = (1 << 9); i > 0; i >>= 1) {
    prevDp = dp;
    dp = std::vector<int >(n + 1, 0);

    for(int q = n; q >= 0; q--) {
      for(int j = 0; j * i <= q && j <= k; j += 2) {
        dp[q - j * i] += 1LL * prevDp[q] * comb[k][j] % p;
        dp[q - j * i] %= p;
      }
    }
  }

  cnt[k] = dp[0];
}

int main() {
  scanf("%d%d", &n, &p);

  Precompute();

  for(int i = 1; i <= n; i++) {
    Compute(i);
  }

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j < i; j++) {
      cnt[i] -= 1LL * cnt[j] * comb[i][j] % p;
      if(cnt[i] < 0) cnt[i] += p;
    }

    printf("%d\n", cnt[i]);
  }
  return 0;
}
