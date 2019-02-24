/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("numerologie.in", "r", stdin);
FILE *fout = freopen("numerologie.out", "w", stdout);

const int MAX_N = 1 + 1250;

bool checked[MAX_N];
int val[MAX_N], prim[MAX_N], cost[MAX_N];
int N, M, k;

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &val[i]);
    }
    k = -1;
    for(int j = 1; j <= M; ++j) {
        int x;
        scanf("%d", &x);
        if(x != -1) {
            k++;
            prim[k] = j;
            cost[k] = x;
        }
    }
}

void getSol() {
    int answer = 2000000000;
    for(int mask = 0; mask < (1 << k); mask++) {
        int current = 0;
        for(int i = 1; i <= N; ++i) {
            checked[i] = false;
        }
        for(int i = 0; i <= k; ++i) {
            if(mask & (1 << i)) {
                current += cost[i];
                for(int j = 1; j <= N; ++j) {
                    if(val[j] % prim[i] == 0) {
                        checked[j] = true;
                    }
                }
            }
        }
        bool ok = true;
        for(int i = 1; i <= N; ++i) {
            if(!checked[i]) {
                ok = false; break;
            }
        }
        if(ok) {
            answer = min(answer, current);
        }
    }
    printf("%d", answer);
}

int main() {
    readData();
    getSol();
}
