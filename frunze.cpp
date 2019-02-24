/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("frunze.in", "r", stdin);
FILE *fout = freopen("frunze.out", "w", stdout);

const int kMaxN = 1 + 50;
const int mod = 29989;

int a[kMaxN][kMaxN];

int s(int n, int m) {
    if(m == 1 || n == m) {
        return 1;
    } else {
        if(!a[n][m]) {
            a[n][m] = (s(n - 1, m - 1) + m * s(n - 1, m) % mod) % mod;
        }
        return a[n][m];
    }
}

int main() {
    int n, p; scanf("%d%d", &n, &p);
    int answer = s(n - 2, n - p);
    for(int i = p + 1; i <= n; i++) {
        answer = answer * i % mod;
    }
    printf("%d\n", answer);
    return 0;
}
