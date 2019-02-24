/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int maxN = 100 + 5;
const int inf = 1e9;

/*-------- Data --------*/
int n, m;
std::vector<int > graph[maxN];

int best = inf;
int dp[maxN][maxN];

std::vector<std::pair<int, int > > sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);

  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      dp[i][j] = inf;
    }
  }

  for(int i = 0; i < m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    graph[u].push_back(v); graph[v].push_back(u);

    dp[u][u] = dp[v][v] = 0;
    dp[u][v] = dp[v][u] = 1;
  }
}

void RunDP() {
  for(int k = 1; k <= n; k++) {
    for(int i = 1; i <= n; i++) {
      for(int j = 1; j <= n; j++) {
        dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k][j]);
      }
    }
  }
}

void GetTree(int root1, int root2) {
  std::queue<int > q;
  std::vector<int > seen(n + 1, false);

  if(root1 != inf) {seen[root1] = true; q.push(root1);}
  if(root2 != inf) {seen[root2] = true; q.push(root2);}

  if(root1 != inf && root2 != inf) {sol.emplace_back(root1, root2);}

  while(!q.empty()) {
    int node = q.front(); q.pop();

    for(auto& nxt : graph[node]) {
      if(seen[nxt]) continue;

      sol.emplace_back(node, nxt);
      seen[nxt] = true; q.push(nxt);
    }
  }
}

void FindBest() {
  int ans = inf, u = inf, v = inf;

  //  The center is a node
  for(int i = 1; i <= n; i++) {
    int diam = 0;
    for(int j = 1; j <= n; j++) {
      diam = std::max(diam, dp[i][j]);
    }

    if(2 * diam < ans) {
      ans = 2 * diam; u = i;
    }
  }

  //  The center is an edge
  for(int i = 1; i <= n; i++) {
    for(int j = i + 1; j <= n; j++) {
      if(dp[i][j] == 1) {
        int diam = 0;
        for(int k = 1; k <= n; k++) {
          diam = std::max(diam, std::min(dp[i][k], dp[k][j]));
        }

        if(2 * diam + 1 < ans) {
          ans = 2 * diam + 1;
          u = i; v = j;
        }
      }
    }
  }

  GetTree(u, v);
}

int main() {
  ReadInput();

  RunDP();

  FindBest();

  for(auto& edg : sol) {
    printf("%d %d\n", edg.first, edg.second);
  }

  return 0;
}
