/**
  *  Worg
  */
#include <map>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("overlap.in", "r", stdin); FILE *fout = freopen("overlap.out", "w", stdout);

/*-------- Data --------*/
int N;
std::map<std::pair<int, int >, int > map[4];
std::vector<std::vector<std::pair<int, int > > > points;
/*-------- --------*/

void ReadInput() {
  scanf("%d", &N);
  points = std::vector<std::vector<std::pair<int, int > > >(N, std::vector<std::pair<int,int > >(4));

  for(int i = 0; i < N; i++) {
    int x, y; scanf("%d%d", &x, &y);

    for(int rot = 0; rot < 4; rot++) {
      points[i][rot] = {x, y}; map[rot][points[i][rot]] = i;
      //printf("%d %d\n", x, y);
      std::swap(x, y); x = -x;
    }
  }
}

int main() {
  ReadInput();

  for(int rot = 0; rot < 4; rot++) {
    for(int fixed = 1; fixed < N; fixed++) {
      std::vector<int > nxt(N, -1), prev(N, -1), ans(N, 0);

      std::pair<int, int > offset = {points[fixed][rot].first - points[0][0].first, points[fixed][rot].second - points[0][0].second};
      nxt[0] = fixed; prev[fixed] = 0;

      bool ok = true;
      for(int i = 1; i < N; i++) {
        std::pair<int, int > p = {points[i][0].first + offset.first, points[i][0].second + offset.second};

        if(map[rot].count(p)) {
          if(map[rot][p] == i) ok = false;
          nxt[i] = map[rot][p];
          prev[map[rot][p]] = i;
        }
      }

      if(!ok) continue;

      for(int i = 0; i < N; i++) {
        if(ans[i] != 0) continue;

        int node = i;
        while(prev[node] != -1 && prev[node] != i) {
          node = prev[node];
        }

        ans[node] = 1;
        while(nxt[node] != -1 && ans[nxt[node]] == 0) {
          ans[nxt[node]] = 3 - ans[node]; node = nxt[node];
        }
        if(ans[node] == 1) {ok = false; break;}
      }

      if(ok) {
        for(auto& itr : ans) {
          printf("%d ", itr);
        }
        return 0;
      }
    }
  }
	return 0;
}
