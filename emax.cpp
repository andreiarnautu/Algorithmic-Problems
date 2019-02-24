/**
  *  Worg
  */
#include <cmath>
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("emax.in", "r", stdin);
FILE *fout = freopen("emax.out", "w", stdout);

const int kMaxN = 1 + 100000;
const int mod = 666013;
const int kStep = 5;

/*-------- Input data --------*/
int N;
int v[kMaxN];
/*-------- Algorithm data --------*/
int partial_sum[kMaxN];
double dp[kMaxN];
int before[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    int n = 0;
    for(int i = 1; i <= N; i++) {
        int x; scanf("%d", &x);
        x = std::abs(x);
        if(x != 0) {
            v[++n] = x;
        }
    }
    N = n;
}

void DoPartialSums() {
    for(int i = 1; i <= N; i++) {
        partial_sum[i] = partial_sum[i - 1] + v[i];
    }
}

void GetDp() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; i - j >= 0 && j <= kStep; j++) {
            if(dp[i] < dp[i - j] + log10(partial_sum[i] - partial_sum[i - j])) {
                dp[i] = dp[i - j] + log10(partial_sum[i] - partial_sum[i - j]);
                before[i] = i - j;
            }
        }
    }
}

void WriteOutput() {
    long long answer = 1;
    int i = N;

    while(i > 0) {
        int j = before[i];
        answer = answer * (partial_sum[i] - partial_sum[j]) % mod;
        i = j;
    }

    printf("%lld\n", answer);
}

int main() {
    ReadInput();
    DoPartialSums();
    GetDp();
    WriteOutput();
    return 0;
}
