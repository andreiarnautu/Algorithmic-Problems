/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("dw.in", "r", stdin); FILE *fout = freopen("dw.out", "w", stdout);

const int maxN = 1e5 + 5;

/*-------- Data --------*/
int n, m;
int imp[maxN];
std::vector<int > graph[maxN];
/*-------- Scc --------*/
int cursor;
int idx[maxN], lowlink[maxN], inStack[maxN];

std::stack<int > st;

std::vector<std::vector<int > > comps;
int where[maxN], dad[maxN];
/*-------- Tree --------*/
struct Event {
  int type, a, b;

  Event(const int _type, const int _a, const int _b) {type = _type; a = _a; b = _b;}
};
std::vector<int > tree[maxN];
std::vector<Event > events[maxN];

int dp[maxN];
int size;

int sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%d", &imp[i]);
  }
  for(int i = 1; i <= m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    graph[u].push_back(v);
  }
}

void StrongConnect(int node) {
  cursor++; idx[node] = lowlink[node] = cursor;

  st.push(node); inStack[node] = true;

  for(auto& nxt : graph[node]) {
    if(!idx[nxt]) {
      StrongConnect(nxt);
      lowlink[node] = std::min(lowlink[node], lowlink[nxt]);
    } else if(inStack[nxt]) {
      lowlink[node] = std::min(lowlink[node], idx[nxt]);
    }
  }

  if(idx[node] == lowlink[node]) {
    std::vector<int > here;

    int act;
    do {
      act = st.top(); st.pop();

      here.push_back(act); inStack[act] = false;
    }while(act != node);

    comps.push_back(here);
  }
}

void Tarjan() {
  for(int i = 1; i <= n; i++) {
    if(!idx[i]) {
      StrongConnect(i);
    }
  }

  std::reverse(comps.begin(), comps.end());
  for(int i = 0; i < (int)comps.size(); i++) {
    for(auto& node : comps[i]) {
      where[node] = i;
    }

    dad[i] = -1;
  }

  for(int i = 1; i <= n; i++) {
    for(auto& j : graph[i]) {
      if(where[i] == where[j]) continue;

      if(dad[where[j]] == -1 || where[i] > dad[where[j]]) {
        dad[where[j]] = where[i];
      }
    }
  }

  for(int i = 0; i < (int)comps.size(); i++) {
    if(dad[i] == -1) continue;

    tree[dad[i]].push_back(i);
  }
}

void DFS(int node) {
  std::sort(comps[node].begin(), comps[node].end(), [&](int a, int b) {
    return imp[a] < imp[b];
  });

  //  Add values to dp
  for(auto& x : comps[node]) {
    int value = imp[x];

    if(value > dp[size]) {
      dp[++size] = value;
      events[node].emplace_back(1, 0, 0);
    } else {
      int left = 1, right = size, ans = size;

      while(left <= right) {
        int mid = (left + right) / 2;

        if(value <= dp[mid]) {
          ans = mid; right = mid - 1;
        } else {
          left = mid + 1;
        }
      }

      events[node].emplace_back(2, ans, dp[ans]);
      dp[ans] = value;
    }
  }

  sol = std::max(sol, size);

  for(auto& nxt : tree[node]) {
    DFS(nxt);
  }

  //  Remove them
  while(!events[node].empty()) {
    auto ev = events[node].back(); events[node].pop_back();

    if(ev.type == 1) {
      size--;
    } else {
      dp[ev.a] = ev.b;
    }
  }
}

int main() {
  ReadInput();

  Tarjan();

  DFS(0);

  printf("%d\n", sol);

  return 0;
}
