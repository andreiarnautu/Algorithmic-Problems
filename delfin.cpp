/**
  *  Worg
  *  Mar 11, 2018
  *  11:09:22 AM
  */
#include <deque>
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("delfin.in", "r", stdin); FILE *fout = freopen("delfin.out", "w", stdout);

const int maxN = 1000 + 5;
const int dx[] = {-1, 0,  0, 1};
const int dy[] = { 0, 1, -1, 0};
const int inf = 1e9;

/*-------- Struct -------*/
struct Str {
  int x, y, type, dist, restricted;

  Str() {x = 0; y = 0; type = 0; dist = 0; restricted = 0;}

  Str(const int _x, const int _y, const int _type, const int _dist, int _restricted = 0) {x = _x; y = _y; type = _type; dist = _dist; restricted = _restricted;}
};
/*-------- Data -------*/
int n, m;
int xTeo, yTeo, xPer, yPer, xFin, yFin;
char s[maxN];


int a[maxN][maxN];
int dst[maxN][maxN][3];

std::deque<Str > q;
/*-------- -------*/

bool Inside(int x, int y) {
  return 1 <= x && x <= n && 1 <= y && y <= m;
}

void ReadInput() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; i++) {
    scanf("%s", s + 1);

    for(int j = 1; j <= m; j++) {
      if(s[j] == '1') {
        a[i][j] = 1;
      } else if(s[j] == '0') {
        a[i][j] = 0;
      } else if(s[j] == 'S') {
        a[i][j] = 1;
        xTeo = i; yTeo = j;
      } else if(s[j] == 'F') {
        a[i][j] = 1;
        xFin = i; yFin = j;
      } else {
        a[i][j] = 0;
        xPer = i; yPer = j;
      }
    }
  }
}

int Solve() {
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      for(int type = 0; type <= 2; type++) {
        dst[i][j][type] = inf;
      }
    }
  }

  //printf("%d %d\n%d %d\n%d %d\n", xTeo, yTeo, xPer, yPer, xFin, yFin);

  q.emplace_back(xTeo, yTeo, 0, 0, 0);
  q.emplace_back(xPer, yPer, 1, 0, 0);

  while(!q.empty()) {
    auto sth = q.front(); q.pop_front();
    int x = sth.x, y = sth.y, type = sth.type, distHere = sth.dist, restricted = sth.restricted;

    //  We are on land with Percy, don't expand and don't update
    if(type == 1 && a[x][y] == 1) continue;
    if(type == 0 && a[x][y] == 0 && restricted) continue;

    //  We have already been here
    if(dst[x][y][type] != inf) continue;

    dst[x][y][type] = distHere;

    //  We are on water(edge of land) with Teo, so we don't want to expand, just update dst[x][y][2]
    if(type == 0 && a[x][y] == 0) {
      if(dst[x][y][1] != inf) {
        q.emplace_front(x, y, 2, distHere, restricted);
      }
      continue;
    }

    //  We are on water, state 1, and we want to see if we can reach state 2
    if(type == 1 && dst[x][y][0] != inf) {
      q.emplace_front(x, y, 2, distHere, restricted);
    }

    //  We are on land with Teo&Percy, we don't want to expand, just update dst[x][y][0]
    if(type == 2 && a[x][y] == 1) {
      if(dst[x][y][0] == inf) {
        q.emplace_front(x, y, 0, distHere, 1);
      }
      continue;
    }

    //  Expand
    for(int d = 0; d < 4; d++) {
      int newX = x + dx[d], newY = y + dy[d];

      if(!Inside(newX, newY)) continue;

      if(dst[newX][newY][type] == inf) q.emplace_back(newX, newY, type, distHere + 1, restricted);
    }
  }

  return dst[xFin][yFin][0];
}

int main() {
  ReadInput();

  printf("%d\n", Solve());

  return 0;
}
