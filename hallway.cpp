/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

#define x first
#define y second

FILE *fin = freopen("hallway.in", "r", stdin); FILE *fout = freopen("hallway.out", "w", stdout);

/*-------- Data --------*/
int W, H;
std::vector<std::pair<int, int > > points;

std::vector<std::vector<double > > dist;

std::vector<int > seen;
std::vector<double > best;
/*-------- --------*/

void ReadInput() {
  scanf("%d%d", &W, &H);
  int K; scanf("%d", &K);
  for(int i = 0; i < K; i++) {
    int x, y; scanf("%d%d", &x, &y);
    points.emplace_back(x, y);
  }
}

double GetDist(std::pair<int, int > a, std::pair<int, int > b) {
  return std::sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
}

void ConstructGraph() {
  int n = (int)points.size();

  dist = std::vector<std::vector<double > >(n + 2, std::vector<double >(n + 2));

  for(int i = 0; i < n; i++) {
    dist[i][n] = dist[n][i] = points[i].y;
    dist[i][n + 1] = dist[n + 1][i] = H - points[i].y;

    for(int j = i + 1; j < n; j++) {
      dist[i][j] = dist[j][i] = GetDist(points[i], points[j]);
    }
  }

  dist[n][n + 1] = dist[n + 1][n] = H;
}

double Dijkstra() {
  int n = (int)points.size() + 2;

  seen.resize(n); best.resize(n);

  for(int i = 0; i < n; i++) {
    best[i] = 1e12;
  }

  best[n - 2] = 0;

  while(!seen[n - 1]) {
    int node = -1;

    for(int i = 0; i < n; i++) {
      if(!seen[i] && (node == -1 || best[i] < best[node])) {
        node = i;
      }
    }

    seen[node] = true;
    for(int i = 0; i < n; i++) {
      best[i] = std::min(best[i], std::max(best[node], dist[node][i]));
    }
  }

  return best[n - 1];
}

int main() {
  ReadInput();

  ConstructGraph();

  printf("%.8f\n", Dijkstra() * 0.5);
	return 0;
}
