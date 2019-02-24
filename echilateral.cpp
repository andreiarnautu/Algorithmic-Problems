/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("echilateral.in", "r", stdin);
FILE *fout = freopen("echilateral.out", "w", stdout);

const int MOD = 666013;

long long N, A, B, A2, B2;
long long Solution;

void solveLength(const long long &L) {
    if(L == 1) {
        Solution = (1LL * N * (N + 1) / 2) % MOD; return;
    }

    long long howMany = (1LL * (N - L + 1) * (N - L + 2) / 2) % MOD;
    long long Left, Right;

    long long a = 3;
    long long b = -3 * L;
    long long c = L * L - A * A;
    long long Delta = b * b - 4 * a * c;

    if(Delta < 0) {
        Right = L / 2;
    } else {
        double eqSol = (3.0 * L - sqrt((double)Delta)) / 6.0;
        Right = (long long) eqSol;

        if(a * Right * Right + b * Right + c < 0) {
            Right --;
        }
        Right = min(L / 2, Right);
    }

    c = L * L - B * B;
    Delta = b * b - 4 * a * c;

    if(Delta < 0) {
        Left = N + 1; /* nu avem solutie */
    } else {
        double eqSol = (3 * L - sqrt((double)Delta)) / 6.0;
        Left = (long long) eqSol;

        if(a * Left * Left + b * Left + c > 0) {
            Left ++;
        }

        Left = max(0LL, Left);
    }

    long long matchCount = 0;

   // printf("%lld %lld %lld\n", L, Right, Left);
    if(Left <= Right) {
        matchCount = (Right - Left + 1) << 1;

        if(Right == L / 2 && L % 2 == 0) {
            matchCount --;
        }
        if(Left == 0) {
            matchCount --;
        }

        Solution = (Solution + matchCount * howMany) % MOD;
    }
}

int main() {
    scanf("%lld%lld%lld", &N, &A, &B);
    A2 = A * A;
    B2 = B * B;

    const long long lowerLimit = A;
    const long long upperLimit = min(B * 2, N);
    for(long long i = lowerLimit; i <= upperLimit; i++) {
        solveLength(i);
    }

    printf("%lld", Solution);
    return 0;
}
