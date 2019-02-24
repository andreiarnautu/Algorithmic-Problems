/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

/*-------- Data --------*/
struct S {
  int l, r, idx;
  S(int _l, int _r, int _idx) {l = _l; r = _r; idx = _idx;}
};

int n, m, q;
std::vector<std::vector<int > > graph;

std::vector<int > seen, father, has, maxR;

std::vector<std::pair<int, int > > v;
std::vector<S > qs;

std::vector<long long > sum, sol;
/*-------- --------*/

void AddCycle(int from, int to) {
  int m = to, M = to;
  has[to] = 1;

  while(from != to) {
    has[from] = true;
    m = std::min(m, from); M = std::max(M, from);
    from = father[from];
  }

  v.emplace_back(m, M);
}

void DFS(int node, int dad) {
  seen[node] = 1; father[node] = dad;

  for(auto& nxt : graph[node]) {
    if(nxt == dad || has[nxt]) continue;

    if(seen[nxt]) {
      AddCycle(node, nxt);
    } else {
      DFS(nxt, node);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m); graph.resize(n + 1);
  for(int i = 0; i < m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    graph[u].push_back(v); graph[v].push_back(u);
  }

  seen = father = has = maxR = std::vector<int >(n + 1, 0);
  for(int i = 1; i <= n; i++) {
    if(!seen[i]) {
      DFS(i, -1);
    }
  }

  std::sort(v.begin(), v.end());

  scanf("%d", &q);
  for(int i = 0; i < q; i++) {
    int u, v; scanf("%d%d", &u, &v);
    qs.emplace_back(u, v, i);
  }

  std::sort(qs.begin(), qs.end(), [&](S a, S b) {
    return std::make_pair(a.l, a.r) < std::make_pair(b.l, b.r);
  });

  sol = std::vector<long long >(q, 0);
  sum = std::vector<long long >(n + 2, 0);

  int mx = n + 1;
  for(int i = n, a = (int)v.size() - 1, b = q - 1; i > 0; i--) {
    while(a >= 0 && i == v[a].first) {
      mx = std::min(mx, v[a].second); a--;
    }
    maxR[i] = mx;
    sum[i] = sum[i + 1] + mx - i;

    while(b >= 0 && i == qs[b].l) {
      int left = i, right = qs[b].r, ans = right + 1;

      while(left <= right) {
        int mid = (left + right) >> 1;
        if(maxR[mid] > qs[b].r) {
          ans = mid; right = mid - 1;
        } else {
          left = mid + 1;
        }
      }

      int cnt = qs[b].r - ans + 1;
      sol[qs[b].idx] = 1LL * cnt * (cnt + 1) / 2;
      sol[qs[b].idx] += sum[i] - sum[ans];

      b--;
    }
  }

  for(int i = 0; i < q; i++) {
    printf("%lld\n", sol[i]);
  }
	return 0;
}
