/**
  *  Worg
  */
#include <cstdio>
FILE *fin = freopen("namlei.in", "r", stdin);
FILE *fout = freopen("namlei.out", "w", stdout);

const int kMaxN = 30000;
const int kMaxK = 8;
const int kModulo = 997;

/*-------- Input data --------*/
int N, K, X, Y;
int edgeCount, x1, x2, add;
int initial[kMaxN][kMaxK][kMaxK];
/*-------- Segment tree --------*/
int segtree[kMaxN * 4][kMaxK][kMaxK];
int solution[kMaxK], aux[kMaxK];
/*-------- --------*/

void Build(int node, int left, int right) {
    if(left == right) {
        for(int i = 0; i < K; i++) {
            for(int j = 0; j < K; j++) {
                segtree[node][i][j] = initial[left][i][j];
            }
        }
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        Build(leftSon, left, mid); Build(rightSon, mid + 1, right);
        for(int k = 0; k < K; k++) {
            for(int i = 0; i < K; i++) {
                for(int j = 0; j < K; j++) {
                    segtree[node][i][j] = segtree[node][i][j] + segtree[leftSon][i][k] * segtree[rightSon][k][j];
                }
            }
        }
        for(int i = 0; i < K; i++) {
            for(int j = 0; j < K; j++) {
                segtree[node][i][j] %= kModulo;
            }
        }
    }
}

inline void Update(int node, int left, int right, int position) {
    if(left == right) {
        for(int i = 0; i < K; i++) {
            for(int j = 0; j < K; j++) {
                segtree[node][i][j] = 1;  //  Reinitializing the matrix
            }
        }
        for(int count = 1; count <= edgeCount; count++) {
            segtree[node][x1][x2] ++;
            int newX1 = (x1 * X + x2 * count * Y + add) % K;
            int newX2 = (x1 * count * X + x2 * Y + add) % K;
            x1 = newX1; x2 = newX2;
        }
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        if(position <= mid) {
            Update(leftSon, left, mid, position);
        } else {
            Update(rightSon, mid + 1, right, position);
        }
        //  Update the current matrix based on the sons
        for(int i = 0; i < K; i++) {
            for(int j = 0; j < K; j++) {
                segtree[node][i][j] = 0;
            }
        }
        for(int k = 0; k < K; k++) {
            for(int i = 0; i < K; i++) {
                for(int j = 0; j < K; j++) {
                    segtree[node][i][j] = segtree[node][i][j] + segtree[leftSon][i][k] * segtree[rightSon][k][j];
                }
            }
        }
        for(int i = 0; i < K; i++) {
            for(int j = 0; j < K; j++) {
                segtree[node][i][j] %= kModulo;
            }
        }
    }
}

void ProcessInitialData() {
    scanf("%d%d%d%d", &N, &K, &X, &Y);
    for(int i = 0; i < N; i++) {
        scanf("%d%d%d", &edgeCount, &x1, &x2);
        for(int j = 0; j < K; j++) {
            for(int k = 0; k < K; k++) {
                initial[i][j][k] = 1;
            }
        }
        for(int count = 1; count <= edgeCount; count++) {
            initial[i][x1][x2] ++;
            int newX1 = (x1 * X + x2 * count * Y + add) % K;
            int newX2 = (x1 * count * X + x2 * Y + add) % K;
            x1 = newX1; x2 = newX2;
        }
    }
    Build(1, 0, N - 1);
}

inline void Query(int node, int left, int right, int first, int last) {
    if(first <= left && right <= last){
        for(int i = 0; i < K; i++) {
            aux[i] = 0;
        }
        for(int i = 0; i < K; i++) {
            for(int j = 0; j < K; j++) {
                aux[j] = aux[j] + solution[i] * segtree[node][i][j];
            }
        }
        for(int i = 0; i < K; i++) {
            solution[i] = aux[i] % kModulo;
        }
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        if(first <= mid) {
            Query(leftSon, left, mid, first, last);
        }
        if(mid < last) {
            Query(rightSon, mid + 1, right, first, last);
        }
    }
}

void ProcessOperations() {
    char type;
    while(scanf(" %c", &type) == 1) {
        if(type == 'U') {
            int position; scanf("%d%d%d%d", &position, &edgeCount, &x1, &x2);
            add = 1; Update(1, 0, N - 1, position);
        } else {
            int i, x, j, y; scanf("%d%d%d%d", &i, &x, &j, &y);
            for(int i = 0; i < K; i++) {
                solution[i] = 0;
            }
            solution[x] = 1; Query(1, 0, N - 1, i, j - 1);
            printf("%d\n", solution[y]);
        }
    }
}

int main() {
    ProcessInitialData();
    ProcessOperations();
    return 0;
}
