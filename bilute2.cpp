/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("bilute2.in", "r", stdin);
FILE *fout = freopen("bilute2.out", "w", stdout);

const int MAX_N = 1 + 750;
const int MAX_VAL = 1 + 9;
const int MOD = 666013;


/*---------------------*/
int cnt[MAX_VAL];
int N, valMed, sumcif;
/*---------------------*/
int comb[MAX_N][MAX_N];
int dp[MAX_N * MAX_VAL][MAX_N];
/*---------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        int c; scanf("%d", &c);
        cnt[c]++; valMed += c; sumcif += c;
    }
    valMed /= N;
}

void getComb() {
    for(int i = 0; i < MAX_N; ++i) {
        comb[i][0] = 1;
        for(int j = 1; j <= i; ++j) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
            comb[i][j] -= MOD * (comb[i][j] >= MOD);
        }
    }
}

void solveProblem() {
    dp[0][0] = 1;

    int limit = 0, cifMax = 0;
    for(int i = 1; i < MAX_VAL; ++i) {
        limit += cnt[i] * i;
        cifMax += cnt[i];
        if(!cnt[i]) {
            continue;
        }


        for(int j = min(limit, sumcif / 2); j >= i; --j) {

            for(int nrcif = min(N / 2, cifMax); nrcif > 0; --nrcif) {
                int k = min(nrcif, min(cnt[i], j / i));
                while(j - k * i < nrcif - k && k >= 0) {
                    k--;
                }
                for(; k > 0; --k)  {
                    if(dp[j - k * i][nrcif - k]) {
                        dp[j][nrcif] = (1LL * dp[j][nrcif] + 1LL * dp[j - k * i][nrcif - k] * comb[cnt[i]][k]) % MOD;
                    }
                }
            }
        }
    }

    int SOL = 0;
    for(int i = 1; i <= N / 2; ++i) {
        for(int j = i * valMed; j < i * (valMed + 1); ++j) {
            double sum1 = j;
            double sum2 = sumcif - j;
            int coef = 2;
            if(i == N / 2 && N % 2 == 0) {
                coef = 1;
            }
            if((double)sum1 / i == (double)sum2 / (N - i)) {
                SOL = (SOL + coef * dp[j][i]) % MOD;
            }
        }
    }
    printf("%d", SOL);
}

int main() {
    readData();
    getComb();
    solveProblem();
    return 0;
}
