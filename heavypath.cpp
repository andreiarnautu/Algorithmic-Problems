/**
  *  Worg
  *  Mar 14, 2018
  *  9:37:06 AM
  */
#include <cstdio>
#include <vector>
#include <algorithm>

#define mid ((left + right) / 2)
#define leftSon (node * 2)
#define rightSon (node * 2 + 1)

FILE *fin = freopen("heavypath.in", "r", stdin); FILE *fout = freopen("heavypath.out", "w", stdout);

const int maxN = 1e5 + 5;

/*-------- Structures --------*/
struct Node;
struct Chain;

struct Node {
  int idx, value, depth, weight;

  std::vector<Node* > adj;

  Chain *chain;
};

struct Chain {
  Node* father;
  std::vector<Node* > nodes;
  std::vector<int > aint;

  int cnt;
  int maxDepth, delay;
  bool ok;

  Chain() {ok = false; cnt = 0;}
};
/*-------- Data --------*/
int n, m;

Node graph[maxN];
/*-------- --------*/

void ReadGraph() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &graph[i].value); graph[i].idx = i;
  }
  for(int i = 1; i < n; i++) {
    int u, v; scanf("%d%d", &u, &v);

    graph[u].adj.push_back(&graph[v]);
    graph[v].adj.push_back(&graph[u]);
  }
}

void DFS(Node *node, int dad, int depth) {
  node->depth = depth; node->weight = 1;

  Node *son;
  int son_weight = 0;

  for(auto& nxt : node->adj) {
    if(nxt->idx == dad) continue;

    DFS(nxt, node->idx, depth + 1);

    node->weight += nxt->weight;
    if(son_weight < nxt->weight) {
      son = nxt; son_weight = nxt->weight;
    }
  }

  if(son_weight == 0) {  //  Make new chain
    node->chain = new Chain();
  } else {  //  Add node to son's chain
    node->chain = son->chain;

    for(auto& nxt : node->adj) {
      if(nxt->idx == dad || nxt->idx == son->idx) continue;

      nxt->chain->father = node;
    }
  }

  node->chain->nodes.push_back(node);
  node->chain->cnt++;
}

void Update(std::vector<int > &aint, int node, int left, int right, int pos, int value) {
  if(left == right) {
    aint[node] = value; return;
  } else {
    if(pos <= mid) {
      Update(aint, leftSon, left, mid, pos, value);
    } else {
      Update(aint, rightSon, mid + 1, right, pos, value);
    }

    aint[node] = std::max(aint[leftSon], aint[rightSon]);
  }
}

void Decompose() {
  DFS(&graph[1], 0, 1);
  graph[0].depth = 0; graph[1].chain->father = &graph[0];

  //  Build aints
  for(int i = 1; i <= n; i++) {
    if(graph[i].chain->ok == true) continue;

    Chain *chain = graph[i].chain;

    int space = (int)chain->nodes.size() + 1;
    chain->aint = std::vector<int >(space * 4, 0);

    chain->maxDepth = chain->nodes[0]->depth;
    chain->delay = chain->nodes.back()->depth - 1;

    for(auto& node : chain->nodes) {
      Update(chain->aint, 1, 1, chain->cnt, node->depth - chain->delay, node->value);
    }

    chain->ok = true;
  }
}

void QueryAint(std::vector<int > &aint, int node, int left, int right, int first, int last, int &ans) {
  if(first <= left && right <= last) {
    ans = std::max(ans, aint[node]); return;
  }

  if(first <= mid) {
    QueryAint(aint, leftSon, left, mid, first, last, ans);
  }
  if(mid < last) {
    QueryAint(aint, rightSon, mid + 1, right, first, last, ans);
  }
}

int Query(Node *u, Node *v) {
  int ans = 0;

  if(u->chain == v->chain) {
    int hmin = std::min(u->depth, v->depth), hmax = std::max(u->depth, v->depth);
    Chain *chain = u->chain;

    QueryAint(chain->aint, 1, 1, chain->cnt, hmin - chain->delay, hmax - chain->delay, ans);
  } else {
    if(u->chain->father->depth > v->chain->father->depth) {
      Chain *chain = u->chain;

      QueryAint(chain->aint, 1, 1, chain->cnt, 1, u->depth - chain->delay, ans);

      ans = std::max(ans, Query(chain->father, v));
    } else {
      Chain *chain = v->chain;

      QueryAint(chain->aint, 1, 1, chain->cnt, 1, v->depth - chain->delay, ans);

      ans = std::max(ans, Query(u, chain->father));
    }
  }

  return ans;
}

void ProcessQueries() {
  for(int i = 0; i < m; i++) {
    int type, x, y; scanf("%d%d%d", &type, &x, &y);

    if(type == 0) {
      graph[x].value = y;

      Chain *chain = graph[x].chain;
      Update(chain->aint, 1, 1, chain->cnt, graph[x].depth - chain->delay, graph[x].value);

    } else {
      printf("%d\n", Query(&graph[x], &graph[y]));
    }
  }
}

int main() {
  ReadGraph();

  Decompose();

  ProcessQueries();

  return 0;
}
