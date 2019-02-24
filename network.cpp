/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int maxN = 1000 + 5;

/*-------- Data --------*/
struct Edge {
  int u, v, c;

  Edge(const int _u, const int _v, const int _c) {
    u = _u; v = _v; c = _c;
  }

  bool operator <(const Edge &other) const {
    return this->c < other.c;
  }
};

int n, m;
std::vector<Edge > edg, sol;

int father[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; i++) {
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

void MST() {
  for(int i = 1; i <= n; i++) {
    father[i] = i;
  }

  int cnt = 0;
  for(auto& e : edg) {
    if(Group(e.u) != Group(e.v)) {
      Unite(e.u, e.v);

      sol.push_back(e);

      cnt++;
      if(cnt == n - 1) {
        printf("%d\n", e.c); break;
      }
    }
  }

  printf("%d\n", n - 1);
  for(int i = 0; i < n - 1; i++) {
    printf("%d %d\n", sol[i].u, sol[i].v);
  }
}

int main() {
  ReadInput();

  MST();
  return 0;
}
