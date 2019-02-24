/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("oneouts.in", "r", stdin);
FILE *fout = freopen("oneouts.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int N_40 = 1 + 2000;
const int MAX_VAL = 1 + 1000000000;
const long long MAX_INF = 1LL * (MAX_N + 1) * MAX_VAL;

long long SOL = MAX_INF;

/*----------------------------*/
int N, K;
int throwTime[2 * MAX_N], edgeTime[2 * MAX_N];
/*----------------------------*/
bool used[MAX_N];
/*----------------------------*/
long long dp[2 * N_40][N_40];
/*----------------------------*/

void readData() {
    scanf("%d%d", &N, &K);
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &edgeTime[i]);
    }
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &throwTime[i]);
    }
}

void expandData() {
    for(int i = N + 1; i <= 2 * N; i++) {
        edgeTime[i] = edgeTime[i - N];
        throwTime[i] = throwTime[i - N];
    }
}

void bruteContinue() {
    int start = 0;
    for(int i = 1; i <= N; ++i) {
        if(used[i]) {
            start = i; break;
        }
    }

    long long current = 0;
    long long currentSOL = 0;
    for(int i = start; i <= start + N; i++) {
        if(used[i]) {
            currentSOL = max(currentSOL, current);
            current = 1LL * throwTime[i] + 1LL * edgeTime[i];
        } else {
            current += 1LL * edgeTime[i];
        }
    }

    SOL = min(SOL, currentSOL);
}

void bruteForce() {
    int limit = (1 << N);

    for(int i = 1; i < limit; i++) {
        int usedCount = 0;
        for(int j = 1; j <= N; j++) {
            if(i & (1 << (j - 1))) {
                used[j] = used[j + N] = true;
                usedCount++;
            } else {
                used[j] = used[j + N] = false;
            }
        }

        if(usedCount <= K) {
            bruteContinue();
        }
    }
}

void Init() {
    for(int i = 1; i <= 2 * N; i++) {
        for(int j = 1; j <= K; j++) {
            dp[i][j] = MAX_INF;
        }
    }
}


void writeData() {
    printf("%lld", SOL);
}

int main() {
    readData();
    expandData();
    if(N <= 20) {
        bruteForce();
        writeData();
    } else {
        for(int i = 1; i <= N; i++) {
            SOL = min(SOL, 1LL * throwTime[i]);
        }
        for(int i = 1; i <= N; ++i) {
            SOL += 1LL * edgeTime[i];
        }
        writeData();
    }

    return 0;
}
