/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("egal.in", "r", stdin); FILE *fout = freopen("egal.out", "w", stdout);

const int kMaxN = 1e5 + 10;

/*-------- Data --------*/
int n;
std::vector<std::vector<int > > graph;
std::vector<int > key, idx;

std::map<int, int > map[kMaxN];
std::vector<std::pair<int, int > > sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n); graph.resize(n); key.resize(n); sol.resize(n); idx.resize(n);
  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v); u--; v--;
    graph[u].push_back(v); graph[v].push_back(u);
  }
  for(int i = 0; i < n; i++) {
    scanf("%d", &key[i]);
    idx[i] = i;
  }
}

void Update(std::pair<int, int > &to, std::pair<int, int > from) {
  if(from.second == to.second) {
    to.first = std::min(to.first, from.first);
  } else if(from.second > to.second) {
    to = from;
  }
}

void DFS(int node, int dad) {
  map[idx[node]][key[node]] = 1;
  sol[node] = {key[node], 1};

  for(auto& nxt : graph[node]) {
    if(nxt == dad) continue;

    DFS(nxt, node);

    Update(sol[node], sol[nxt]);

    if(map[idx[node]].size() < map[idx[nxt]].size()) {
      std::swap(idx[node], idx[nxt]);
    }

    for(auto& p : map[idx[nxt]]) {
      map[idx[node]][p.first] += p.second;
      Update(sol[node], {p.first, map[idx[node]][p.first]});
    }
  }
}

int main() {
  ReadInput();

  DFS(0, 0);

  for(int i = 0; i < n; i++) {
    printf("%d %d\n", sol[i].first, sol[i].second);
  }
	return 0;
}
