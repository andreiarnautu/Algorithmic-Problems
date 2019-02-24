/**
  *  Worg
  */
#include <cmath>
#include <cstdio>

using namespace std;
FILE *fin = freopen("test.in", "r", stdin);
FILE *fout = freopen("test.out", "w", stdout);

long long gcd(long long a, long long b) {
    long long r;
    while(b) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {

    long long a, b;
    scanf("%lld%lld", &a, &b);

    if(a == b) {
        printf("-1");
    }
    else if(a == 1) {
        printf("%lld", b);
    }
    else {
        long long answer = 0;
        for(long long i = a; i < b - answer; ++i) {
            for(long long j = b; j - i + 1 > answer; --j) {
                if(gcd(i, j) == 1) {
                    answer = j - i + 1;
                    break;
                }
            }
        }
        printf("%lld", answer);
    }
}
