/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("oxificarelight.in", "r", stdin); FILE *fout = freopen("oxificarelight.out", "w", stdout);

const int kMaxLen = 10000;

std::vector<std::vector<int > > dp;

void RunTest() {
  int n; scanf("%d", &n);

  std::vector<int > v(n);
  for(auto& x : v) {
    scanf("%d", &x);
  }

  dp = std::vector<std::vector<int > >(n + 1, std::vector<int >(kMaxLen, kMaxLen));

  for(int i = 0; i < kMaxLen; i++) {
    dp[0][i] = i;
  }

  for(int i = 1; i <= n; i++) {
    int len = v[i - 1];

    for(int j = 0; j < kMaxLen; j++) {
      if(j - len >= 0) {
        dp[i][j] = std::min(dp[i][j], std::max(j, dp[i - 1][j - len]));
      }
      if(j + len < kMaxLen) {
        dp[i][j] = std::min(dp[i][j], dp[i - 1][j + len]);
      }
    }
  }

  int ans = kMaxLen;
  for(int i = 0; i < kMaxLen; i++) {
    ans = std::min(ans, dp[n][i]);
  }
  printf("%d\n", ans);
}

int main() {
  int t; scanf("%d", &t);
  for(int i = 0; i < t; i++) {
    RunTest();
  }
	return 0;
}
