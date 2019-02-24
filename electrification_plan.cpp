/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int maxN = 105;

/*-------- Data --------*/
int n, k;
int v[maxN];
int c[maxN][maxN];

std::vector<std::pair<int, int > > edg;

int father[maxN];
int sol;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &n, &k);
  for(int i = 1; i <= k; i++) {
    scanf("%d", &v[i]);
  }
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= n; j++) {
      scanf("%d", &c[i][j]);
      edg.emplace_back(i, j);
    }

    father[i] = i;
  }
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
  std::sort(edg.begin(), edg.end(), [&](std::pair<int, int > a, std::pair<int, int > b) {
    return c[a.first][a.second] < c[b.first][b.second];
  });

  for(int i = 2; i <= k; i++) {
    Unite(v[i], v[i - 1]);
  }

  for(int i = 0; i < (int)edg.size(); i++) {
    if(Group(edg[i].first) != Group(edg[i].second)) {
      sol += c[edg[i].first][edg[i].second];

      Unite(edg[i].first, edg[i].second);
    }
  }

  printf("%d\n", sol);
}

int main() {
  ReadInput();

  MST();

  return 0;
}
