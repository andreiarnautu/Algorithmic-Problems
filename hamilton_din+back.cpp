#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 18;
const int MAX_INF = 0x3fffffff;
                 // 0000 1111 1111 1111 1111 1111 1111 1111 == (2^30)-1
const int MIN_INF = 0x80000000;
                 // 1000 0000 0000 0000 0000 0000 0000 0000 == -(2^31)

                 // 1111 1111 1111 1111 1111 1111 1111 1111 == -1
                 // 0000 0000 0000 0000 0000 0000 0000 0001 ==  1

int n, m;
int cost[1 + MAX_N][1 + MAX_N];

int Back[1 << MAX_N][MAX_N];
int vecini[MAX_N];
char bit[1 << MAX_N];

int back(int u, int folosit) {
  if (Back[folosit][u] == 0) {
    if (folosit == 0 && u == 1)
    {
      Back[folosit][u] = 0;
    }
    else
    {
      Back[folosit][u] = MAX_INF;
      int tmpFolosit = folosit &  vecini[u];
      while (tmpFolosit > 0) {
        int newFolosit = (tmpFolosit & (tmpFolosit - 1));
        int v = bit[newFolosit ^ tmpFolosit]; // ultimul bit
        tmpFolosit = newFolosit;
        Back[folosit][u] = min(Back[folosit][u],
              cost[u][v] + back(v, folosit ^ (1 << v)));
      }
    }
  }
  return Back[folosit][u];
}

int main() {
  int i;
  freopen("hamilton.in", "r", stdin);
  freopen("hamilton.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for (i = 0; i < m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    cost[u][v] = c;
        vecini[u] ^= (1 << v);
  }
  for(int i = 0; i < n; ++i)
    bit[1 << i] = i;

  int minim = back(1, (1<<n) - 1);

  if (minim == MAX_INF)
    printf("Nu exista solutie");
  else
    printf("%d\n", minim);
  return 0;
}
