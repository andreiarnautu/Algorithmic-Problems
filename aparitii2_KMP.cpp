/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
FILE *fin = freopen("aparitii2.in", "r", stdin);
FILE *fout = freopen("aparitii2.out", "w", stdout);

const int MAX_LEN = 1 + 1000000 + 1;

/*-------- Input data --------*/
char A[MAX_LEN], B[MAX_LEN];
int N, M;
/*-------- KMP data --------*/
int L[2][MAX_LEN], D[2][MAX_LEN];
int dp[2][MAX_LEN];
/*-------- Solution --------*/
int Solution[MAX_LEN];
/*-------- --------*/


void readInput() {
    scanf("%s%s", A + 1, B + 1);
    N = strlen(A + 1);
    M = strlen(B + 1);
}

void runKMP(int index) {
    int k = 0;
    for(int i = 2; i <= M; i++) {
        while(k > 0 && B[i] != B[k + 1]) {
            k = L[index][k];
        }
        if(B[i] == B[k + 1]) {
            k ++;
        }
        L[index][i] = k;
    }

    k = 0;
    for(int i = 1; i <= N; i++) {
        while(k > 0 && A[i] != B[k + 1]) {
            k = L[index][k];
        }
        if(A[i] == B[k + 1]) {
            k ++;
        }
        D[index][i] = k;

        if(k > 0) {
            dp[index][i - k + 1] = max(dp[index][i - k + 1], k);
            int K = k;
            while(L[index][K] > 0) {
                K = L[index][K];
                dp[index][i - K + 1] = max(dp[index][i - K + 1], K);
            }
        }
    }
}

void getSolution() {
   /* for(int i = 1; i <= N; i++) {
        printf("%d", D[0][i]);
    }
    printf("\n");
    for(int i = 1; i <= N; i++) {
        printf("%d", D[1][i]);
    }
    printf("\n");*/


    for(int i = 1; i + M - 1 <= N; i++) {
        int first = dp[0][i];
        int second = dp[1][N - (i + M - 1) + 1];

        int wanted = min(first, second);
        if(wanted > 0) {
         //   printf("Intervalul (%d %d), maxX = %d\n", i, i + M - 1, wanted);
            Solution[1] ++;
            Solution[wanted + 1] --;
        }
    }

    for(int i = 1; i * 2 <= M; i++) {
        Solution[i] += Solution[i - 1];
    }
}

void writeOutput() {
    for(int i = 1; i * 2 <= M; i++) {
        printf("%d\n", Solution[i]);
    }
}

int main() {
    readInput();
    runKMP(0);
    reverse(A + 1, A + N + 1);
    reverse(B + 1, B + M + 1);
    runKMP(1);
    getSolution();
    writeOutput();
    return 0;
}
