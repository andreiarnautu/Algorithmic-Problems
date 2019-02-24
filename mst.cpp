/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("mst.in", "r", stdin); FILE *fout = freopen("mst.out", "w", stdout);

const double eps = 1e-8;

/*-------- Data --------*/
struct Edge {
  int u, v;
  double a, b, c;

  Edge() {}
  Edge(int _u, int _v, double _a, double _b, double _c) {u = _u; v = _v; a = _a; b = _b; c = _c;}
};

int n, m;
std::vector<Edge > edges, mst;
std::vector<double > mins;
std::vector<int > father;
/*-------- --------*/

int Group(int node) {
  if(node != father[node]) {
    father[node] = Group(father[node]);
  }
  return father[node];
}

void Unite(int u, int v) {
  father[Group(u)] = Group(v);
}

void GetMST(double beg, double end) {
  double t = (beg + end) * 0.5;

  father.resize(n);
  for(int i = 0; i < n; i++) {
    father[i] = i;
  }

  std::sort(edges.begin(), edges.end(), [&](Edge x, Edge y) {
    return (x.a * t * t + x.b * t + x.c) < (y.a * t * t + y.b * t + y.c);
  });

  mst.clear();
  for(auto& e : edges) {
    if(Group(e.u) != Group(e.v)) {
      mst.push_back(e);
      Unite(e.u, e.v);
    }
  }
}

int main() {
  double max = -1e9, min = +1e9;

  scanf("%d%d", &n, &m);
  for(int i = 0; i < m; i++) {
    int u, v; scanf("%d%d", &u, &v);
    double a, b, c; scanf("%lf%lf%lf", &a, &b, &c);
    edges.emplace_back(u, v, a, b, c);

    min = std::min(min, -b / (2*a)); max = std::max(max, -b / (2*a));
  }
  //  Get the points where the MST might change

  mins.emplace_back(min); mins.emplace_back(max);

  for(int i = 0; i < m; i++) {
    for(int j = i + 1; j < m; j++) {
      double a = edges[i].a - edges[j].a, b = edges[i].b - edges[j].b, c = edges[i].c - edges[j].c;

      if(a != 0.0) {
        double delta = b * b - 4 * a * c;

        if(delta < 0) continue;

        delta = std::sqrt(delta);

        double x1 = (- b - delta) / (2 * a), x2 = (- b + delta) / (2 * a);
        mins.emplace_back(x1); mins.emplace_back(x2);

        continue;
      }

      if(b != 0.0) {
        mins.emplace_back(c / b);
      }
    }
  }

  std::sort(mins.begin(), mins.end());

  //  Construct MST for each interval then update the solution

  double time = 0.0, cost = 1e14;

  for(int i = 0; i < (int)mins.size() - 1; i++) {
    double beg = mins[i], end = mins[i + 1];

    GetMST(beg, end);

    double a = 0.0, b = 0.0, c = 0.0;
    for(auto& e : mst) {
      a += e.a; b += e.b; c += e.c;
    }

    double x = -b / (2 * a), y = -(b * b - 4 * a * c) / (4 * a);

    if(cost > y) {
      time = x; cost = y;
    }
  }

  printf("%.10f %.10f\n", time, cost);
	return 0;
}
