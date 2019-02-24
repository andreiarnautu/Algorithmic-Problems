/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("numerologie.in", "r", stdin);
FILE *fout = freopen("numerologie.out", "w", stdout);

const int MAX_N = 1 + 1250;
const int MAX_M = 1 + 1250;
const int MAX_INF = 0x3fffffff;
const int Primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
const int primeCount = 11;

/*------------------------------*/
int val[MAX_N], cost[MAX_M];
int N, M;
/*------------------------------*/
bool marked[MAX_M];
int SOL = MAX_INF;
/*------------------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &val[i]);
    }
    for(int i = 1; i <= M; i++) {
        scanf("%d", &cost[i]);
    }
}

void Reset() {
    for(int i = 37; i <= M; i += 2) {
        marked[i] = false;
    }
}

void solveProblem() {
    const int LIMIT = (1 << primeCount);

    for(int mask = 0; mask < LIMIT; mask++, Reset()) {
        bool possible = true;

        for(int i = 1; i <= N && possible == true; i++) {
            bool ok = false;
            int X = val[i];

            for(int j = 0; j < primeCount; j++) {
                if((mask & (1 << j)) && X % Primes[j] == 0) {
                    ok = true;
                }
                while(X % Primes[j] == 0) {
                    X /= Primes[j];
                }
            }

            if(!ok && X == 1) {
                possible = false;
            } else if(!ok && X > 35) {
                marked[X] = true;
            }
        }

        if(possible) {
            int currentCost = 0;
            for(int j = 0; j < primeCount; j++) {
                if(mask & (1 << j)) {
                    currentCost += cost[Primes[j]];
                }
            }
            for(int j = 35; j <= M; j++) {
                if(marked[j]) {
                    currentCost += cost[j];
                }
            }

            SOL = min(SOL, currentCost);
        }
    }
}

void writeData() {
    printf("%d", SOL);
}

int main() {
    readData();
    solveProblem();
    writeData();
    return 0;
}
