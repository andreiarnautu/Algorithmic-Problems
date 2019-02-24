/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("nperechi.in", "r", stdin);
FILE *fout = freopen("nperechi.out", "w", stdout);

long long getGcd(long long x, long long y) {
    long long r;
    while(y) {
        r = x % y; x = y; y = r;
    }
    return x;
}

int main() {
    long long A, B, C, D;
    scanf("%lld%lld%lld%lld", &A, &B, &C, &D);

    long long Answer;
    if(A * D - B * C != 0) {
        Answer = abs(A * D - B * C) - getGcd(A, C) - getGcd(B, D) + 1;
    } else {
        Answer = getGcd(A + B, C + D) - 1;
    }

    printf("%lld\n", Answer);
    return 0;
}
