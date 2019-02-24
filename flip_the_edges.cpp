/**
  *  Worg
  */
#include <cstdio>
#include <vector>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1e5 + 1;

int N;
std::vector<std::vector<int > > graph[kMaxN];
std::pair<int, int > dp[kMaxN][2];

void ReadInput() {
  scanf("%d", &N);
  for(int i = 1; i < N; i++) {
    int u, v, b, e; scanf("%d%d%d%d", &u, &v, &b, &e);
    graph[u].push_back({v, b, e});
    graph[v].push_back({u, b, e});
  }
}

std::pair<int, int > operator +(const std::pair<int, int > &a, const std::pair<int, int > &b) {
  return {a.first + b.first, a.second + b.second};
}

void Update(int to, int from, int b, int e) {
  std::pair<int, int > tmp[2] = {{kMaxN, 0}, {kMaxN, 0}};

  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
      if(e == 2) {
        //!  Flip
        tmp[i ^ 1] = std::min(tmp[i ^ 1], std::make_pair(2 * (1 - i - j), 1) + dp[to][i] + dp[from][j]);
        //!  No flip
        tmp[i] = std::min(tmp[i], dp[to][i] + dp[from][j]);
      } else if(b != e) {
        //!  Flip
        tmp[i ^ 1] = std::min(tmp[i ^ 1], std::make_pair(2 * (1 - i - j), 1) + dp[to][i] + dp[from][j]);
      } else {
        //!  No flip
        tmp[i] = std::min(tmp[i], dp[to][i] + dp[from][j]);
      }
    }
  }

  dp[to][0] = tmp[0]; dp[to][1] = tmp[1];
}

void DFS(int node, int dad) {
  dp[node][0] = {0, 0}; dp[node][1] = {kMaxN, 0};

  for(auto& nxt : graph[node]) {
    if(nxt[0] == dad) continue;

    DFS(nxt[0], node);
    Update(node, nxt[0], nxt[1], nxt[2]);
  }
}

int main() {
  ReadInput();

  DFS(1, 0);

  std::pair<int, int > sol = std::min(dp[1][0], dp[1][1]);

  printf("%d %d\n", sol.first / 2, sol.second);

  return 0;
}
