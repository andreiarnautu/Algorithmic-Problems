/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("cowfood.in", "r", stdin); FILE *fout = freopen("cowfood.out", "w", stdout);

const int maxN = 20 + 5;
const int maxK = 30 + 5;
const int maxS = 1e4 + 5;
const int mod = 3210121;

/*-------- Data --------*/
int k, s, n;
int a[maxN][maxK];

int dp[maxK][maxS];

int maxA[maxK];
int prevA[maxN][maxK];

int validConfs;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d%d", &k, &s, &n);
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= k; j++) {
      scanf("%d", &a[i][j]);
    }
  }
}

void Precompute() {
  for(int i = 0; i <= s; i++) {
    dp[0][i] = 1;
  }

  for(int i = 1; i <= k; i++) {
    dp[i][0] = 1;

    for(int j = 1; j <= s; j++) {
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      if(dp[i][j] >= mod) dp[i][j] -= mod;
    }
  }
}

void Back(int lvl, int cnt) {
  if(lvl == n + 1) {
    int sum = 0;
    for(int i = 1; i <= k; i++) {
      sum += maxA[i];
    }

    if(sum > s) return;

    if(cnt & 1) {
      validConfs -= dp[k][s - sum];
      if(validConfs < 0) validConfs += mod;
    } else {
      validConfs += dp[k][s - sum];
      if(validConfs >= mod) validConfs -= mod;
    }
  } else {
    //  Continue without the current one
    Back(lvl + 1, cnt);

    //  Add the current experiment to the configuration
    for(int i = 1; i <= k; i++) {
      prevA[lvl][i] = maxA[i];
      maxA[i] = std::max(maxA[i], a[lvl][i]);
    }
    Back(lvl + 1, cnt + 1);

    //  Restore
    for(int i = 1; i <= k; i++) {
      maxA[i] = prevA[lvl][i];
    }
  }
}

int main() {
  ReadInput();

  Precompute();

  Back(1, 0);

  validConfs = (validConfs - 1 - s * k + mod) % mod;
  printf("%d\n", validConfs);

  return 0;
}
