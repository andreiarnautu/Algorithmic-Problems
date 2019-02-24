/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

FILE *fin = freopen("croco.in", "r", stdin); FILE *fout = freopen("croco.out", "w", stdout);

const int maxN = 110 + 5;
const int inf = 1e9;

/*-------- Data --------*/
int n;
int a[maxN][maxN];
std::vector<int > graph[maxN];

int cap[maxN][maxN];
int prev[maxN], seen[maxN];

int total;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &n);
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      scanf("%d", &a[i][j]);
      total += a[i][j];

      if(a[i][j]) {
        graph[i].push_back(j);
      }
    }
  }

  total /= 2;
}

bool BFS(int beg, int fin) {
  for(int i = 1; i <= n; i++) {
    prev[i] = 0;
  }

  std::queue<int > q;
  prev[beg] = beg; q.push(beg);

  while(!q.empty()) {
    int node = q.front(); q.pop();

    if(node == fin) return true;

    for(auto& nxt : graph[node]) {
      if(!prev[nxt] && cap[node][nxt]) {
        prev[nxt] = node; q.push(nxt);
      }
    }
  }

  return false;
}

int Flow(int beg, int fin, int best) {
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      cap[i][j] = a[i][j];
    }
  }

  int flow = 0;
  while(BFS(beg, fin) && flow < best) {
    for(auto& x : graph[fin]) {
      if(prev[x] != 0 && cap[x][fin]) {
        prev[fin] = x;

        int flowHere = inf;
        for(int i = fin; i != beg && flowHere != 0; i = prev[i]) {
          flowHere = std::min(flowHere, cap[prev[i]][i]);
        }
        for(int i = fin; i != beg && flowHere != 0; i = prev[i]) {
          cap[prev[i]][i] -= flowHere; cap[i][prev[i]] += flowHere;
        }

        flow += flowHere;
      }
    }
  }

  return flow;
}

void DFS(int node) {
  seen[node] = true;
  for(auto& nxt : graph[node]) {
    if(cap[node][nxt] && !seen[nxt]) {
      DFS(nxt);
    }
  }
}

int MinCut() {
  int ans = inf;

  for(int i = 2; i <= n; i++) {
    int here = Flow(1, i, ans);

    if(here < ans) {
      ans = here;
      for(int j = 1; j <= n; j++) {
        seen[j] = false;
      }
      DFS(1);
    }
  }

  return ans;
}

int main() {
  ReadInput();

  printf("%d ", total - MinCut());

  int cnt = 0;
  for(int i = 1; i <= n; i++) {
    cnt += seen[i];
  }
  printf("%d\n", cnt);

  for(int i = 1; i <= n; i++) {
    if(seen[i]) {
      printf("%d ", i);
    }
  }

  return 0;
}
