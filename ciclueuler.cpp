/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <utility>

FILE *fin = freopen("ciclueuler.in", "r", stdin); FILE *fout = freopen("ciclueuler.out", "w", stdout);

/*-------- Data --------*/
int N, M;
std::vector<std::vector<std::pair<int, int > > > graph;

std::vector<int > deg, seen;
std::stack<int > s;

std::vector<int > sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &N, &M); graph.resize(N); deg.resize(N);
  for(int i = 0; i < M; i++) {
    int u, v; scanf("%d%d", &u, &v); u--; v--;
    deg[u]++; deg[v]++;
    graph[u].emplace_back(v, i); graph[v].emplace_back(u, i);
  }
}

void EulerCycle() {
  seen = std::vector<int >(M, false);

  s.push(0);
  while(!s.empty()) {
    int node = s.top();

    while(!graph[node].empty() && seen[graph[node].back().second] == true) {
      graph[node].pop_back();
    }

    if(!graph[node].empty()) {
      int nxt = graph[node].back().first;
      seen[graph[node].back().second] = true;

      s.push(nxt); graph[node].pop_back();
    } else {
      sol.push_back(node); s.pop();
    }
  }

  for(int i = 1; i < (int)sol.size(); i++) {
    printf("%d ", sol[i] + 1);
  }
  printf("\n");
}

int main() {
  ReadInput();

  for(int i = 0; i < N; i++) {
    if(deg[i] % 2 == 1) {
      printf("-1\n"); return 0;
    }
  }

  EulerCycle();
}
