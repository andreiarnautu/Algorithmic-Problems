/**
  *  Worg
  *  Mar 21, 2018
  *  6:58:28 PM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("datorii2.in", "r", stdin); FILE *fout = freopen("datorii2.out", "w", stdout);

const int maxN = 20 + 1;

/*-------- Data --------*/
int n, m;
int v[maxN];

std::vector<int > good;
int dp[1 << maxN], sub[1 << maxN];

std::vector<int > left, right;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);

  for(int i = 1; i <= m; i++) {
    int a, b, c; scanf("%d%d%d", &a, &b, &c);

    v[a] += c; v[b] -= c;
  }
}

void Solve() {
  for(int i = 1; i <= n; i++) {
    if(v[i] != 0) {
      good.push_back(i);
    }
  }

  //  dp[i] = nr maxim de componente cu suma 0 pe care le avem pentru nodurile din configuratia "i"
  int sz = (int)good.size(), limit = 1 << sz;

  dp[0] = 0;

  for(int i = 1; i < limit; i++) {
    dp[i] = -1;

    int sum = 0;
    for(int j = 0; j < sz; j++) {
      if(i & (1 << j)) {
        sum += v[good[j]];

        if(dp[i] < dp[i - (1 << j)]) {
          dp[i] = dp[i - (1 << j)];
          sub[i] = j;
        }
      }
    }

    dp[i] += (sum == 0);
  }

  int act = limit - 1;
  while(act != 0) {
    int bit = sub[act];

    if(v[good[bit]] > 0) {
      left.push_back(good[bit]);
    } else {
      right.push_back(good[bit]);
    }

    act -= (1 << bit);
  }

  int sum = 0;
  for(auto& itr : left) {
    sum += v[itr];
  }

  printf("%d %d\n", sz - dp[limit - 1], sum);

  std::reverse(left.begin(), left.end()); std::reverse(right.begin(), right.end());

  int idx = 0;
  for(int i = 0; i < (int)left.size(); i++) {
    while(v[left[i]] && idx < (int)right.size()) {
      int x = std::min(v[left[i]], -v[right[idx]]);

      printf("%d %d %d\n", left[i], right[idx], x);

      v[left[i]] -= x; v[right[idx]] += x;

      if(v[right[idx]] == 0) {
        idx++;
      }
    }
  }

}

int main() {
  ReadInput();

  Solve();

  return 0;
}
