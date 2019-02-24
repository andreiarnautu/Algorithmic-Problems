/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int maxN = 500 + 5;
const int inf = 1e9;

/*--------- Data --------*/
struct Edge {
  int u, v, c;

  Edge(const int _u, const int _v, const int _c) {u = _u; v = _v; c = _c;}

  bool operator <(const Edge &other) const {
    return this->c < other.c;
  }
};

int n, m;
std::vector<Edge > edg;
std::vector<int > used;

int father[maxN];

int blocked;
int sol = inf;
/*--------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    int u, v, c; scanf("%d%d%d", &u, &v, &c);
    edg.emplace_back(u, v, c);
  }

  std::sort(edg.begin(), edg.end());
}

int Group(int node) {
  if(node != father[node]) {
    father[node] = Group(father[node]);
  }
  return father[node];
}

void Unite(int u, int v) {
  father[Group(u)] = Group(v);
}

void FirstMST() {
  for(int i = 1; i <= n; i++) {
    father[i] = i;
  }

  int cost = 0;
  for(int i = 0; i < m; i++) {
    auto e = edg[i];

    if(Group(e.u) != Group(e.v)) {
      cost += e.c;

      Unite(e.u, e.v);

      used.push_back(i);
    }
  }

  if((int)used.size() != n - 1) {
    printf("Cost: %d\n", -1);
  } else {
    printf("Cost: %d\n", cost);
  }
}

void SecondMST() {
  for(int i = 1; i <= n; i++) {
    father[i] = i;
  }

  int cost = 0, cnt = 0;
  for(int i = 0; i < m && cnt < n - 1; i++) {
    if(blocked == i) continue;

    auto e = edg[i];

    if(Group(e.u) != Group(e.v)) {
      Unite(e.u, e.v);

      cost += e.c;

      cnt++;
    }
  }

  if(cnt == n - 1) {
    sol = std::min(sol, cost);
  }
}

int main() {
  ReadInput();

  FirstMST();

  for(auto& itr : used) {
    blocked = itr;

    SecondMST();
  }

  printf("Cost: %d\n", (sol == inf) ? -1 : sol);

  return 0;
}
