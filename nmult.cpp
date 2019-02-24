/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("nmult.in", "r", stdin);
FILE *fout = freopen("nmult.out", "w", stdout);

const int MOD = 666013;

int n, k, w;

long long int prod(int p, int q) {

    long long int ret = 1;
    for(int i = p; i <= q; i++)
        ret = (1LL * ret * i) % MOD;
    return ret;
}

long long int pow(int p, int q) {

    long long int ret = 1, aux = p;
    for(int i = 1; i <= q; i <<= 1) {

        if(i & q) {
            ret = (1LL * ret * aux) % MOD;
        }
        aux = (1LL * aux * aux) % MOD;
    }
    return ret;
}

long long int comb(int p, int q) {

    long long int ret, a, b;

    if(q < p - q) {

        ret = prod(p - q + 1, p);
        a = prod(1, q);
    }

    else {

        ret = prod(q + 1, p);
        a = prod(1, p - q);
    }

    b = pow(a, MOD - 2);
    ret = (ret * b) % MOD;
    return ret;
}

int main() {

    scanf("%d%d%d", &n, &k, &w);
    n -= (k - 1) * (w - 1);

    if(n < k) {
        printf("0");
    }
    else {
        printf("%lld", comb(n, k));
    }

    return 0;
}
