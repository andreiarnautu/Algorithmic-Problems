/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("oxificare.in", "r", stdin); FILE *fout = freopen("oxificare.out", "w", stdout);

/*-------- Data --------*/
int n;
std::vector<int > edgeCost;
std::vector<std::vector<int > > graph;

int limit;
std::vector<std::vector<int > > dp;
/*-------- --------*/

void ReadData() {
  scanf("%d", &n);
  graph = std::vector<std::vector<int > >(n); edgeCost = std::vector<int >(n);

  for(int i = 2; i <= n; i++) {
    int father; scanf("%d", &father);
    graph[father - 1].push_back(i - 1);
  }

  limit = 0;
  for(int i = 2; i <= n; i++) {
    scanf("%d", &edgeCost[i - 1]);
    limit = std::max(limit, 2 * edgeCost[i - 1]);
  }
  dp = std::vector<std::vector<int > >(n, std::vector<int >(limit, limit));
}

void DFS(int node) {
  if(graph[node].size() == 0) {
    for(int i = 0; i < limit; i++) {
      dp[node][i] = i;
    }
  } else {
    for(auto& son : graph[node]) {
      DFS(son);
    }

    for(int i = 0; i < limit; i++) {
      dp[node][i] = 0;

      for(auto& son : graph[node]) {
        int cost = edgeCost[son], crt = limit;

        if(i + cost < limit) {
          crt = std::min(crt, dp[son][i + cost]);
        }
        if(i - cost >= 0) {
          crt = std::min(crt, std::max(i, dp[son][i - cost]));
        }

        dp[node][i] = std::max(dp[node][i], crt);
      }
    }
  }
}

int main() {
  int t; scanf("%d", &t);

  for(; t != 0; t--) {
    ReadData();

    DFS(0);


    int ans = limit;
    for(int i = 0; i < limit; i++) {
      ans = std::min(ans, dp[0][i]);
    }
    printf("%d\n", ans);
  }
	return 0;
}
