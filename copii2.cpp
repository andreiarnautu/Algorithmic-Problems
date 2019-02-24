/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("copii2.in", "r", stdin);
FILE *fout = freopen("copii2.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MAX_LOG = 1 + 17;
/*----------------------------*/
int N, K;
int x;
/*----------------------------*/
int val[MAX_N];
vector <int> SOL[MAX_N];
/*----------------------------*/

void getX() {
    /* puterea maxima a lui K care este mai mica sau egala ca N, aceasta fiind egala cu numarul minim de runde */
    x = 0;
    long long current = 1;
    while(current < 1LL * N) {
        x++; current *= 1LL * K;
    }
    printf("%d\n", x);
}

void Generate() {
    for(int i = 0; i < N; ++i) {
        val[i] = i;
    }
    for(int i = 1; i <= x; ++i) {
        for(int j = 0; j < N; ++j) {
            SOL[val[j] % K].push_back(j + 1);
            val[j] /= K;
        }
        printf("%d\n", K);
        for(int j = 0; j < K; ++j) {
            printf("%d ", (int)SOL[j].size());
            for(vector<int>::iterator it = SOL[j].begin(); it != SOL[j].end(); ++it) {
                printf("%d ", *it);
            }
            printf("\n");
            SOL[j].clear();
        }
    }
}

int main() {
    scanf("%d%d", &N, &K);
    getX();
    Generate();
    return 0;
}
