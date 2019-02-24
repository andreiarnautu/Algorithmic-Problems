/**
  *  Worg
  *  Mar 14, 2018
  *  8:56:27 AM
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>

FILE *fin = freopen("2sat.in", "r", stdin); FILE *fout = freopen("2sat.out", "w", stdout);

const int maxN = (1e5 + 5) * 2;

/*-------- Data --------*/
int n, m;
std::vector<int > graph[maxN];

int cursor;
int idx[maxN], low[maxN], inStack[maxN], value[maxN], here[maxN];

std::stack<int > st;

std::vector<int > comp;
/*-------- --------*/

int Opp(int node) {
  if(node > n) return node - n;
  return node + n;
}

void ReadInput() {
  scanf("%d%d", &n, &m);

  for(int i = 0; i < m; i++) {
    int x, y; scanf("%d%d", &x, &y);

    x = (x < 0) ? (-x + n) : x;
    y = (y < 0) ? (-y + n) : y;

    graph[Opp(x)].push_back(y); graph[Opp(y)].push_back(x);
  }
}

void NoSol() {
  printf("-1\n"); exit(0);
}

void Process() {
  for(auto& node : comp) {
    here[node] = true;
    if(here[Opp(node)]) {
      NoSol();
    }
  }

  int val = -1;
  for(auto& node : comp) {
    if(value[node] != -1) {
      val = value[node]; break;
    }
  }

  for(auto& node : comp) {
    if(val == -1) value[node] = 1;
    else value[node] = 0;

    value[Opp(node)] = value[node] ^ 1;
    here[node] = false;
  }
}

void DFS(int node) {
  idx[node] = low[node] = ++cursor;

  st.push(node); inStack[node] = true;

  for(auto& nxt : graph[node]) {
    if(!idx[nxt]) {
      DFS(nxt);
      low[node] = std::min(low[node], low[nxt]);
    } else if(inStack[nxt]) {
      low[node] = std::min(low[node], idx[nxt]);
    }
  }

  if(idx[node] == low[node]) {
    int act;
    do {
      act = st.top(); st.pop();
      comp.push_back(act); inStack[act] = false;
    }while(act != node);

    Process();
    comp.clear();
  }
}

void Tarjan() {
  for(int i = 1; i <= 2 * n; i++) {
    value[i] = -1;
  }

  for(int i = 1; i <= 2 * n; i++) {
    if(!idx[i]) {
      DFS(i);
    }
  }
}

int main() {
  ReadInput();

  Tarjan();

  for(int i = 1; i <= n; i++) {
    printf("%d ", value[i]);
  }

  return 0;
}
