/**
  *  Worg
  *  Mar 19, 2018
  *  8:26:55 PM
  */
#include <set>
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("aquapark.in", "r", stdin); FILE *fout = freopen("aquapark.out", "w", stdout);

const int maxN = 1e5 + 5;
const int mod = 666013;

/*-------- Data --------*/
int c, n, m;

std::pair<int, int > edg[maxN];

std::vector<std::pair<int, int > > from[maxN];
std::vector<std::pair<int, int > > to[maxN];
/*-------- Data --------*/
std::vector<int > graph[maxN];
std::vector<int > now;

std::multiset<std::pair<int, int > > mset;

int countWays;
int where[maxN];
/*-------- --------*/

void ReadInput() {
  scanf("%d%d%d", &c, &n, &m);

  for(int i = 0; i < m; i++) {
     int u, v; scanf("%d%d", &u, &v);

     if(u > v) std::swap(u, v);

     edg[i] = {u, v};
     from[u].emplace_back(v, i); to[v].emplace_back(u, i);
  }
}

void ConstructGraph() {
  for(int i = 1; i <= n; i++) {
    //  Erase current elements from the multiset
    for(auto& itr : to[i]) {
      if(mset.find(itr) == mset.end()) continue;
      mset.erase(mset.find(itr));
    }

    //  Check intersections for the edges which end here
    std::sort(to[i].begin(), to[i].end());

    for(int j = (int)to[i].size() - 1; j >= 0 && !mset.empty(); j--) {
      auto it = mset.end(); it--;
      auto itr = mset.end();

      while(it->first > to[i][j].first) {
        int u = it->second, v = to[i][j].second;
        itr = it;

        graph[u].push_back(v); graph[v].push_back(u);

        if(it == mset.begin()) break;
        it--;
      }

      it = itr;
      while(it != mset.end() && itr != mset.end() && it->first == itr->first) {
        it++;
      }

      if(it != mset.end() && itr != mset.end()) {
        mset.erase(it, mset.end());
      }

    }

    //  Add elements to the multiset
    for(auto& itr : from[i]) {
      mset.insert({i, itr.second});
    }
  }
}

void DFS(int node, int color) {
  where[node] = color;

  for(auto& nxt : graph[node]) {
    if(where[nxt]) continue;

    DFS(nxt, 3 - color);
  }
}

void GetSolution() {
  countWays = 1;

  for(int i = 0; i < m; i++) {
    if(!where[i]) {
      DFS(i, 1);

      countWays = countWays * 2;
      if(countWays >= mod) countWays -= mod;

    }
  }

  if(c == 1) {
    for(int i = 0; i < m; i++) {
      printf("%d %d %d\n", edg[i].first, edg[i].second, where[i]);
    }
  } else {
    printf("%d\n", countWays);
  }
}

int main() {
  ReadInput();

  ConstructGraph();

  GetSolution();
  return 0;
}
