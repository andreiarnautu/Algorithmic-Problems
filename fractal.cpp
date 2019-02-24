/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin=freopen("fractal.in","r",stdin);
FILE *fout=freopen("fractal.out","w",stdout);

int hilbert(int k, int x, int y) {

    if(!k)
        return 0;

    int L = 1 << (k - 1);

    if(x <= L && y <= L)
        return hilbert(k - 1, y, x);
    if(x > L && y <= L)
        return hilbert(k - 1, x - L, y) + L * L;
    if(x <= L && y > L)
        return hilbert(k - 1, 2 * L - y + 1, L - x + 1) + 3 * L * L;
    else
        return hilbert(k - 1, x - L, y - L) + 2 * L * L;
}

int main() {

    int k, x, y;
    scanf("%d %d %d ", &k, &x, &y);
    printf("%d ", hilbert(k, y, x));
    return 0;
}
