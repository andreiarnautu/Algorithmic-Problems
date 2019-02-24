/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("metrou5.in", "r", stdin);
FILE *fout = freopen("metrou5.out", "w", stdout);

const int mod = 1e9 + 7;
const int kMaxN = 1 + 100000 + 10;

/*-------- Input data --------*/
int N, K;
int v[kMaxN];
/*-------- Algorithm data --------*/
int fact[2 * kMaxN];
int cursor = 0;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &v[i]);
    }
    v[0] = 1;
    N++;
    v[N] = K;
}

int FindNext() {
    while(v[cursor] == -1) {
        cursor ++;
    }
    return cursor;
}

void Precalc() {
    fact[0] = 1;
    for(int i = 1; i < 2 * kMaxN; i++) {
        fact[i] = 1LL * fact[i - 1] * i % mod;
    }
}

long long Power(long long base, long long exp) {
    long long answer = 1, aux = base;
    for(long long i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = (answer * aux) % mod;
        }
        aux = (aux * aux) % mod;
    }
    return answer;
}

long long Comb(int n, int k) {
    return 1LL * fact[n] * Power(fact[n - k], mod - 2) % mod * Power(fact[k], mod - 2) % mod;
}

int main() {
    ReadInput();
    Precalc();

    long long sol = 1;
    int pos_1, pos_2;

    pos_1 = 0; cursor = 1;
    while(cursor < N + 1) {
        int pos_2 = FindNext(); cursor ++;

        int i = v[pos_2] - v[pos_1];
        if(i < 0) {
            printf("0\n"); return 0;
        }
        int j = pos_2 - pos_1 - 1;

        sol = sol * Comb(j + i, i) % mod;

        pos_1 = pos_2;
    }

    printf("%lld\n", sol % mod);
    return 0;
}
