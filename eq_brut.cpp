/**
  *  Worg
  *  Brute-force
  */

#include <cstdio>
#include <algorithm>

#define DIM 100100

using namespace std;
FILE *fin=freopen("eq.in","r",stdin);
FILE *fout=freopen("eq.out","w",stdout);

int v[DIM];

int main() {

    int n, m, x, y;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &v[i]);

    for(int i = 1; i <= m; ++i) {

        int Y = -1, Z = 1 << 30;
        scanf("%d %d ", &x, &y);
        for(int i1 = x; i1 <= y; ++i1)
            for(int i2 = i1; i2 <= y; ++i2)
                for(int i3 = i1; i3 <= y; ++i3) {

                    Y = max(Y, v[i1] + v[i2] - v[i3]);
                    Z = min(Z, v[i1] + v[i2] - v[i3]);
                }
        printf("%d %d %d\n", Y, Z, Y + Z);
    }
}
