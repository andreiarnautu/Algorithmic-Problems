/**
  *  Worg
  */
#include <cstdio>
FILE *fin = freopen("ghiozdan.in", "r", stdin);
FILE *fout = freopen("ghiozdan.out", "w", stdout);

const int kMaxG = 75000 + 1;
const int kMaxOb = 200 + 1;

/*--------- Data --------*/
int N, G;
int count[kMaxOb];

int dp[kMaxG], substract[kMaxG];
/*--------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &G);
    for(int i = 1; i <= N; i++) {
        int x; scanf("%d", &x);
        count[x] ++;
    }
}

void RunDP() {
    dp[0] = 1;
    for(int i = kMaxOb - 1; i > 0; i--) {
        if(count[i] > 0) {
            for(int j = G - i; j >= 0; j--) {
                if(dp[j] != 0) {
                    for(int x = 1; x <= count[i] && j + x * i <= G && dp[j + x * i] == 0; x++) {
                        dp[j + x * i] = dp[j] + x;
                        substract[j + x * i] = i;
                    }
                }
            }
        }
    }
}

void WriteData() {
    for(int i = G; i >= 0; i--) {
        if(dp[i] != 0) {
            printf("%d %d\n", i, dp[i] - 1);
            int x = i;
            while(x > 0) {
                printf("%d\n", substract[x]);
                x -= substract[x];
            }
            return;
        }
    }
}

int main() {
    ReadInput();
    RunDP();
    WriteData();
    return 0;
}
