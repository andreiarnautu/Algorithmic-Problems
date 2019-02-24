/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("grafc.in", "r", stdin);
FILE *fout = freopen("grafc.out", "w", stdout);

const int MAX_K = 1 + 100;

/*-------- --------*/
int K, N, M;

int father[MAX_K];
int connectedComponents;
bool chosen[MAX_K][MAX_K];
/*-------- --------*/

void readInput() {
    scanf("%d%d%d", &K, &N, &M);
}

int Group(int node) {
    if(node != father[node]) {
        father[node] = Group(father[node]);
    }
    return father[node];
}

void Unite(int u, int v) {
    u = Group(u);
    v = Group(v);
    father[u] = v;
    connectedComponents --;
}

void getGraph(int x) {
    connectedComponents = K;

    if(x == K) {
        return;
    }

    for(int i = 1; i <= K; i++) {
        for(int j = i + 1; j <= K; j++) {
            if(Group(i) != Group(j)) {
                if(x == 1 && i == 1 && j == K) {
                    continue;
                }
                chosen[i][j] = true;
                Unite(i, j);

                if(connectedComponents == x) {
                    return;
                }
            }
        }
    }
}

void writeOutput() {
    if(N != 1 && M != 1) {
        printf("-1"); return;
    }

    if(N == 1 && M == 1 && (K == 2 || K == 3)) {
        printf("-1"); return;
    }

    if(N != 1) {
        printf("%d\n", K - N);
        for(int i = 1; i <= K; i++) {
            for(int j = i + 1; j <= K; j++) {
                if(chosen[i][j]) {
                    printf("%d %d\n", i, j);
                }
            }
        }
    } else {
        printf("%d\n", K * (K - 1) / 2 - (K - M));
        for(int i = 1; i <= K; i++) {
            for(int j = i + 1; j <= K; j++) {
                if(!chosen[i][j]) {
                    printf("%d %d\n", i, j);
                }
            }
        }
    }
}

int main() {
    readInput();
    for(int i = 1; i <= K; i++) {
        father[i] = i;
    }
    getGraph(max(N, M));
    writeOutput();
    return 0;
}
