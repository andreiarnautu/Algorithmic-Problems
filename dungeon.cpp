/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;

FILE *fin = freopen("dungeon.in", "r", stdin); FILE *fout = freopen("dungeon.out", "w", stdout);

/*-------- Test data --------*/
int n;
std::vector<std::vector<int > > whiteTree, blackTree;
std::vector<int > coresp, whitePair, blackPair;
/*-------- --------*/

void ReadTestData() {
  scanf("%d", &n);

  whiteTree = blackTree = std::vector<std::vector<int > >(2 * n + 5, std::vector<int >());

  coresp = whitePair = blackPair = std::vector<int > (2 * n + 5, 0);


  //  Read trees
  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v);
    whiteTree[u].push_back(v); whiteTree[v].push_back(u);
  }

  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v);
    blackTree[u].push_back(v); blackTree[v].push_back(u);
  }

  //  Read coresp
  for(int i = 0; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v);
    coresp[u] = v; coresp[v] = u;
  }
}

bool DFS(std::vector<std::vector<int > > &graph, int node, int dad, std::vector<int > &pair) {
  bool ret = true;

  for(auto& nxt : graph[node]) {
    if(nxt == dad) continue;

    ret &= DFS(graph, nxt, node, pair);
  }

  if(!pair[node] && dad != 0 && pair[dad] == 0) {
    pair[node] = dad; pair[dad] = node;
  }

  if(!pair[node]) ret = false;

  return ret;
}

void GetCycle() {
  //printf("Got here\n"); return;
  std::vector<int > cycle;
  std::vector<int > seen(2 * n + 5, false);

  int node = 1;

  while(!seen[node]) {
    cycle.push_back(node); seen[node] = true;

    node = coresp[node]; if(seen[node]) break; cycle.push_back(node); seen[node] = true;

    node = blackPair[node]; if(seen[node]) break; cycle.push_back(node); seen[node] = true;

    node = coresp[node]; if(seen[node]) break; cycle.push_back(node); seen[node] = true;

    node = whitePair[node];
  }

  if((int)cycle.size() != 2 * n) {
    printf("-1\n");
  } else {
    for(auto& itr : cycle) {
      printf("%d ", itr);
    }
    printf("\n");
  }

}

int main() {
  int testCount; scanf("%d", &testCount);

  for(int i = 0; i < testCount; i++) {
    ReadTestData();

    bool verdict = DFS(whiteTree, 1, 0, whitePair) | DFS(blackTree, n + 1, 0, blackPair);

    if(!verdict) {
      printf("-1\n");
    } else {
      GetCycle();
    }
  }

  return 0;
}
