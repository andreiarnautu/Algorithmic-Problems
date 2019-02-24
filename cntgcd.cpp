/**
  *  Worg
  */
#include <cstdio>
#include <unordered_map>

using namespace std;
FILE *fin = freopen("cntgcd.in", "r", stdin);
FILE *fout = freopen("cntgcd.out", "w", stdout);

const int DIM = 1 + 1000000;

int N, D;
long long phi[DIM], nr[DIM];
unordered_map <int, long long> Map;

void preCalc() {
    for(int i = 1; i < DIM; ++i) {
        phi[i] = i;
    }
    for(int i = 2; i < DIM; ++i) {
        if(phi[i] == i) {
            for(int j = i; j < DIM; j += i) {
                phi[j] /= i;
                phi[j] *= (i - 1);
            }
        }
    }
    nr[1] = 1;
    for(int i = 2; i < DIM; ++i) {
        nr[i] = nr[i - 1] + 2 * phi[i];
    }
}

long long Get(int n) {
    if(n < DIM) {
        return nr[n];
    } else {
        if(Map[n]) {
            return Map[n];
        }
    }

    long long answer = 1LL * n * n;
    for(int i = 2; i * i <= n; ++i) {
        answer -= Get(n / i);
    }
    for(int i = 1; i * (i + 1) <= n; ++i) {
        long long a = n / i;
        long long b = n / (i + 1);
        answer -= 1LL * (a - b) * Get(i);
    }

    Map[n] = answer;

    return answer;
}

int main() {
    scanf("%d%d", &N, &D);
    preCalc();

    long long SOL = (Get(N / D) - 1) / 2 + 1;
    printf("%lld\n", SOL);
    return 0;
}
