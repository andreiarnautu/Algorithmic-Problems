/**
  *  Worg
  */
#include <bitset>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("armate.in", "r", stdin); FILE *fout = freopen("armate.out", "w", stdout);

const int kMaxN = 400;
const int limit = 3000;

/*-------- Data --------*/
int n, q;
std::vector<int > s;
std::vector<std::vector<std::pair<int, int > > > queries;

std::vector<int > ans;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &q); s.resize(n + 1);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &s[i]);
  }

  ans.resize(q); queries.resize(n + 1);
  for(int i = 0; i < q; i++) {
    int left, right; scanf("%d%d", &left, &right);
    queries[left].push_back({right, i});
  }
}

void SolveQueries(int left) {
  if(queries[left].empty()) return;
  std::sort(queries[left].begin(), queries[left].end());

  std::bitset<2 * limit > dp[kMaxN + 1];

  dp[left - 1][limit] = 1;
  for(int i = left, cursor = 0; i <= n && cursor < (int)queries[left].size(); i++) {
    dp[i] = 0;
    dp[i] |= (dp[i - 1] >> s[i]);
    dp[i] |= (dp[i - 1] << s[i]);

    while(cursor < (int)queries[left].size() && queries[left][cursor].first == i) {
      for(int j = 0; j <= limit; j++) {
        if(dp[i][limit - j] == 1 || dp[i][limit + j] == 1) {
          ans[queries[left][cursor].second] = j; break;
        }
      }
      cursor++;
    }
  }
}

int main() {
  ReadInput();

  for(int i = 1; i <= n; i++) {
    SolveQueries(i);
  }

  for(auto& itr : ans) {
    printf("%d\n", itr);
  }
	return 0;
}
