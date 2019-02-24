/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("mvc.in", "r", stdin); FILE *fout = freopen("mvc.out", "w", stdout);

const int kMaxInf = 1e9;

/*-------- Data --------*/
int N;
std::vector<int > cost;
std::vector<std::vector<int > > graph;

int x, y;
std::vector<int > seen;

bool state;
std::vector<std::vector<int > > dp;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &N); cost.resize(N); graph.resize(N);
  for(auto& itr : cost) {
    scanf("%d", &itr);
  }
  for(int i = 0; i < N; i++) {
    int u, v; scanf("%d%d", &u, &v); u--; v--;
    graph[u].push_back(v); graph[v].push_back(u);
  }
}

void FindNodes(int node, int dad) {
  seen[node] = true;
  for(auto& nxt : graph[node]) {
    if(nxt == dad) continue;

    if(seen[nxt]) {
      x = node; y = nxt; continue;
    }
    FindNodes(nxt, node);
  }
}

void DFS(int node, int dad) {
  dp[node][0] = 0; dp[node][1] = cost[node];
  if(node == y) {
    if(state == 0) {
      dp[node][1] = kMaxInf;
    } else {
      dp[node][0] = kMaxInf;
    }
  }

  for(auto& nxt : graph[node]) {
    if(nxt == dad || (node == x && nxt == y) || (node == y && nxt == x)) continue;

    DFS(nxt, node);

    dp[node][0] += dp[nxt][1];
    dp[node][1] += std::min(dp[nxt][0], dp[nxt][1]);
  }
}

int main() {
  ReadInput();

  seen = std::vector<int >(N, false);
  FindNodes(0, 0);

  dp = std::vector<std::vector<int > >(N, std::vector<int >(2, kMaxInf));

  state = 0; DFS(x, x);
  int sol = dp[x][1];

  state = 1; DFS(x, x);
  sol = std::min(sol, std::min(dp[x][0], dp[x][1]));

  printf("%d\n", sol);
  return 0;
}
