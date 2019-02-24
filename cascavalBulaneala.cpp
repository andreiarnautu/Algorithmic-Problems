/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>
FILE *fin = freopen("cascaval.in", "r", stdin);
FILE *fout = freopen("cascaval.out", "w", stdout);

const int kMaxN = 100000 + 2;

/*-------- Input data --------*/
int N;
int F[kMaxN], C[kMaxN], S[kMaxN], D[kMaxN];
/*-------- Dp data --------*/
long long dp[kMaxN];
long long sumD[kMaxN], sumS[kMaxN];
long long partialCost[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d%d%d%d", &F[i], &C[i], &S[i], &D[i]);
    }
}

void ComputeAuxiliaryData() {
    for(int i = 1; i <= N; i++) {
        sumS[i] = sumS[i - 1] + S[i]; sumD[i] = sumD[i - 1] + D[i];
    }
    partialCost[N] = 0;
    for(int i = N - 1; i > 0; i--) {
        partialCost[i] = partialCost[i + 1] + S[i] * (sumD[N] - sumD[i]);
    }
}

long long TransportationCost(int x, int y) {
    return partialCost[x] - partialCost[y] - (sumD[N] - sumD[y]) * (sumS[y - 1] - sumS[x - 1]);
}

long long GetRangeCost(int x, int y) {  //  All the cheese for the range [x, y] is produced in month x
    return F[x] + C[x] * (sumD[y] - sumD[x - 1]) + TransportationCost(x, y);
}

long long RunDP() {
    const int kMagic = 100000000 / N;

    dp[N] = F[N] + C[N] * D[N];
    for(int i = N - 1; i > 0; i--) {
        dp[i] = dp[i + 1] + GetRangeCost(i, i);

        for(int j = i + 2; j <= N + 1; j++) {
            dp[i] = std::min(dp[i], dp[j] + GetRangeCost(i, j - 1));
        }
    }

    return dp[1];
}

int main() {
    ReadInput();
    ComputeAuxiliaryData();
    printf("%lld\n", RunDP());
    return 0;
}
