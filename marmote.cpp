/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("marmote.in", "r", stdin); FILE *fout = freopen("marmote.out", "w", stdout);

const int kMaxN = 1000 + 5;
const std::vector<std::pair<int, int > > dir = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
/*-------- Data --------*/
int N, M, K, L;
int a[kMaxN][kMaxN];

std::queue<std::pair<int, int > > q;
/*-------- --------*/

int Dist(std::pair<int, int > x, std::pair<int, int > y) {
  return std::abs(x.first - y.first) + std::abs(x.second - y.second);
}

bool Valid(std::pair<int, int > p) {
  return 0 < p.first && p.first <= N && 0 < p.second && p.second <= M && a[p.first][p.second] == 0;
}

int main() {
  scanf("%d%d%d%d", &N, &M, &K, &L);

  for(int i = 1; i <= K; i++) {
    int x, y; scanf("%d%d", &x, &y);

    if(a[std::max(1, x - L)][y] || a[std::min(N, x + L)][y] || a[x][std::max(1, y - L)] || a[x][std::min(M, y + L)]) continue;

    printf("%d\n", i);

    q.emplace(x, y); a[x][y] = 1;

    while(!q.empty()) {
      auto p = q.front(); q.pop();
      int dist0 = Dist({x, y}, p);

      for(auto& d : dir) {
        std::pair<int, int > nxt = {p.first + d.first, p.second + d.second};
        int dist1 = Dist({x, y}, nxt);

        if(Valid(nxt) && dist1 == dist0 + 1 && dist1 <= L) {
          q.push(nxt); a[nxt.first][nxt.second] = 1;
        }
      }
    }
  }
  return 0;
}
