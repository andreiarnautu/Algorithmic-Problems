/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int mod = 1e9 + 7;

/*-------- Data --------*/
int n, q;
std::vector<int > left, dp, sum;
/*-------- --------*/

int main() {
  scanf("%d%d", &n, &q);

  //  Read data
  left = std::vector<int >(n + 10, 0);
  for(int i = 0; i < q; i++) {
    int l, r; scanf("%d%d", &l, &r);
    left[r + 1] = std::max(left[r + 1], l);
  }
  for(int i = 1; i <= n + 1; i++) {
    left[i] = std::max(left[i], left[i - 1]);
  }

  //  Compute dp
  dp = sum = std::vector<int >(n + 10, 0);
  sum[1] = 1;

  for(int i = 1; i <= n + 1; i++) {
    dp[i] = (sum[i] - sum[left[i]] + mod) % mod;
    sum[i + 1] = (dp[i] + sum[i]) % mod;
  }

  printf("%d\n", dp[n + 1]);
	return 0;
}
