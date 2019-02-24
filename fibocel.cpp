/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("fibocel.in", "r", stdin);
FILE *fout = freopen("fibocel.out", "w", stdout);

const int MAX_POW = 55;

int fib[9];
long long comb[MAX_POW][MAX_POW];

void initializeFib() {
    fib[1] = 1;
    fib[2] = 2;
    fib[3] = 3;
    fib[4] = 5;
    fib[5] = 8;
    fib[6] = 13;
    fib[7] = 21;
    fib[8] = 34;
}

void initializeComb() {
    comb[0][0] = 1LL;
    for(int i = 1; i < MAX_POW; ++i) {
        comb[i][0] = 1LL;
        for(int j = 1; j <= i; ++j) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }
}

long long Get(long long x, int used) {
    if(x <= 0) {
        long long answer = 0;
        for(int i = 1; i <= 8; ++i) {
            if(used == fib[i]) {
                answer += 1LL;
            }
        }
        return answer;
    } else if(x == 1) {
        long long answer = 0;
        for(int i = 1; i <= 8; ++i) {
            if(used == fib[i]) {
                answer++;
            }
        }
        for(int i = 1; i <= 8; ++i) {
            if(used + 1 == fib[i]) {
                answer++;
            }
        }
        return answer;
    }

    long long pow = 1;
    int exp = 0;
    while(pow * 2 <= x) {
        pow *= 2LL; exp++;
    }


    long long answer = 0;
    for(int i = 0; i <= exp; ++i) {
        bool ok = false;
        for(int j = 1; j <= 8; ++j) {
            if(fib[j] == i + used) {
                ok = true; break;
            }
        }
        if(ok) {
            answer += 1LL * comb[exp][i];
        }
    }

    answer += 1LL * Get(x - pow, used + 1);

    return answer;
}

int main() {
    initializeFib();
    initializeComb();


    int Q; scanf("%d", &Q);
    for(; Q; --Q) {
        long long A; scanf("%lld", &A);
        long long B; scanf("%lld", &B);
        printf("%lld\n", Get(B, 0) - Get(A - 1, 0));
    }
    return 0;
}
