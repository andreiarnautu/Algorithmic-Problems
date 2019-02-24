/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("lss.in", "r", stdin);
FILE *fout = freopen("lss.out", "w", stdout);

const int kMaxP = 1 + 100000;

int K, P;
int pos[kMaxP];

int main() {
    scanf("%d%d", &K, &P);
    for(int i = 1; i <= P; i++) {
        scanf("%d", &pos[i]);
    }
    std::sort(pos + 1, pos + P + 1);

    long long solution = 0;
    if(K < P) {
        solution = P - K;
        P = K;
    }
    for(int i = 1; i <= P; i++) {
        pos[i] = (pos[i] % K == 0) ? K : pos[i] % K;
        solution += std::max(pos[i] - i + 1, 1);
    }
    printf("%lld\n", solution);
    return 0;
}
