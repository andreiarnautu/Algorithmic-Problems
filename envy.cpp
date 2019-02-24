/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int kMaxCost = 5e5 + 5;
/*-------- Data --------*/
struct Edge {
  int u, v, c;

  Edge() {}

  Edge(int _u, int _v, int _c) {u = _u; v = _v; c = _c;}

  bool operator <(const Edge &other) const {
    return this->c < other.c;
  }
};

int n, m;
std::vector<Edge > edg;
std::vector<std::pair<int, int > > costEdg[kMaxCost];

int q;
std::vector<Edge > qedg[kMaxCost];

std::vector<std::vector<std::pair<int, int > > > edgHere;

std::vector<int > father, prev, sol, changes;
/*-------- --------*/

int Group(int node, int type) {
  if(node != father[node]) {
    father[node] = Group(father[node], type);
    if(type == 1) {
      changes.push_back(node);
    } else {
      prev[node] = father[node];
    }
  }
  return father[node];
}

void Unite(int u, int v, int type) {
  u = Group(u, type); v = Group(v, type);
  father[u] = v;
  if(type == 1) {
    changes.push_back(u);
  } else {
    prev[u] = father[u];
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    int u, v, c; scanf("%d%d%d", &u, &v, &c); u--; v--;
    edg.emplace_back(u, v, c);
    costEdg[c].emplace_back(u, v);
  }

  scanf("%d", &q);
  for(int i = 0; i < q; i++) {
    int k; scanf("%d", &k);
    for(int j = 0; j < k; j++) {
      int idx; scanf("%d", &idx); idx--;
      qedg[edg[idx].c].emplace_back(edg[idx].u, edg[idx].v, i);
    }
  }

  father.resize(n); prev.resize(n);
  for(int i = 0; i < n; i++) {
    father[i] = prev[i] = i;
  }

  sol = std::vector<int >(q, true); edgHere.resize(q);

  //return 0;

  for(int cst = 1; cst < kMaxCost; cst++) {
    std::set<int > set;
    for(auto& e : qedg[cst]) {
      set.insert(e.c);
      edgHere[e.c].emplace_back(e.u, e.v);
    }

    for(auto& id : set) {
      if(sol[id] == false) continue;

      //  Do operations
      for(auto& e : edgHere[id]) {
        if(Group(e.first, true) == Group(e.second, true)) {
          sol[id] = false; break;
        } else {
          Unite(e.first, e.second, true);
        }
      }

      edgHere[id].clear();

      //  Reverse them
      for(auto& itr : changes) {
        father[itr] = prev[itr];
      }
      changes.clear();
    }

    //  Continue building the mst with edges of current cost
    for(auto& e : costEdg[cst]) {
      if(Group(e.first, false) != Group(e.second, false)) {
        Unite(e.first, e.second, false);
      }
    }
  }

  for(int i = 0; i < q; i++) {
    printf("%s\n", sol[i] == 0 ? "NO" : "YES");
  }
}
