/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int MAX_N = 1 + 100;
const int LIMIT = 60;

/*--------------------*/
long long K;
long long dp[MAX_N];
/*--------------------*/
int SOL[MAX_N];
/*--------------------*/

void Generate() {
    dp[1] = 1;
    for(int i = 2; i <= LIMIT; i++) {
        dp[i] = dp[i - 1] * 2 + 1LL;
    }
}

void Refresh(int dim) {
    for(int i = 1; i <= dim; i++) {
        SOL[i] = i;
    }
}

bool Try(int dim) {
    if(dp[dim] < K) { /* if we can't possibly reach K subsequences with only dim numbers */
        return false;
    } else {
        int swapPos = 1;
        long long subCount = dp[dim];

    //    printf("-------------------\n");
    //    printf("Starting with dim = %d:\n", dim);

        for(int i = dim; i > swapPos; i--) {
            int j = i;
            for(; j >= swapPos; j--) {
                if(subCount - dp[i - j] < K) {
                    break;
                }
            }
            j++;

            int ret = SOL[i];
            for(int k = i; k > j; k--) {
                SOL[k] = SOL[k - 1];
            }
            SOL[j] = ret;

            subCount -= dp[i - j];
     //       printf("%d %d %d\n", i, j, subCount);
            swapPos = j + 1;

            if(j != i) {
                i++;
            }

            if(subCount == K) {
                return true;
            }
        }

        return false;
    }
}

void writeData(int dim) {
    for(int i = 1; i <= dim; i++) {
        printf("%d ", SOL[i]);
    }
    printf("\n");
}

int main() {
    Generate();
    scanf("%lld", &K);

    if(K == 1) {
        printf("1\n"); return 0;
    }

    for(int i = 1; i <= LIMIT; i++) {
        Refresh(i);
        if(Try(i)) {
            writeData(i); return 0;
        }
    }
    return 0;
}
