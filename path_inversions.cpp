/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int kModulo = 1e9 + 7;

/*-------- Data --------*/
int N, K;
std::vector<std::vector<int > > graph;

std::vector<int > deleted, size;

long long sol;
/*-------- --------*/

void DFS(int node, int dad) {
  size[node] = 1;
  for(auto& nxt : graph[node]) {
    if(nxt == dad || deleted[nxt]) continue;

    DFS(nxt, node);
    size[node] += size[nxt];
  }
}

int FindCentroid(int node, int dad, int sz) {
  for(auto& nxt : graph[node]) {
    if(nxt == dad || deleted[nxt]) continue;

    if(size[nxt] > sz / 2) {
      return FindCentroid(nxt, node, sz);
    }
  }
  return node;
}

void AddDFS(int node, int dad, int depth, std::map<int, int >& map, std::map<int, int > &mapHere) {
  if(map.find(K - depth) != map.end()) {
    sol += map[K - depth];
  }

  if(sol >= kModulo) sol -= kModulo;

  mapHere[depth] += 1;

  for(auto& nxt : graph[node]) {
    if(nxt == dad || deleted[nxt]) continue;

    AddDFS(nxt, node, depth + 1, map, mapHere);
  }
}

void Decompose(int node) {
  DFS(node, node);

  int G = FindCentroid(node, node, size[node]);

  std::map<int, int > map; map[0] = 1;

  for(auto& nxt : graph[G]) {
    if(deleted[nxt]) continue;

    std::map<int, int > mapHere;
    AddDFS(nxt, G, 1, map, mapHere);

    for(auto& itr : mapHere) {
      map[itr.first] += itr.second;
    }
  }

  deleted[G] = true;

  for(auto& nxt : graph[G]) {
    if(deleted[nxt]) continue;

    Decompose(nxt);
  }
}

int main() {
  scanf("%d%d", &N, &K); graph.resize(N);
  for(int i = 1; i < N; i++) {
    int u, v; scanf("%d%d", &u, &v); u--; v--;
    graph[u].push_back(v); graph[v].push_back(u);
  }

  deleted = size = std::vector<int >(N, 0);

  Decompose(0);

  long long coef = 1LL * K * (K + 1) / 2; coef %= kModulo;

  sol = sol * coef % kModulo;
  printf("%lld\n", sol);

	return 0;
}
