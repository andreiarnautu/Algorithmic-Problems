/**
  *  Worg
  */
#include <cstdio>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1 + 300000;
const int kMaxDim = 1 + 4000000;
const int sigma = 26;

int N;
int cnt[kMaxN];
int tree[kMaxDim][sigma];
int cursor;

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i < N; i++) {
        int u, v;
        char c;
        scanf("%d%d %c", &u, &v, &c);
        tree[u][c - 'a'] = v;
    }

    cursor = N;
}

int Merge(int u, int v, int depth) {
    if(!u || !v) {return u + v;}  /// @SPECIAL

    cnt[depth] ++;
    cursor ++;
    int result = cursor;

    for(int i = 0; i < sigma; i++) {
        tree[result][i] = Merge(tree[u][i], tree[v][i], depth);
    }
    return result;
}

void DFS(int node = 1, int depth = 1) {
    int result = 0;
    for(int i = 0; i < sigma; i++) {
        if(tree[node][i] != 0) {
            DFS(tree[node][i], depth + 1);
            result = Merge(result, tree[node][i], depth);
        }
    }
    if(result > 0) {
        cnt[depth] ++;
    }
}

void WriteOutput() {
    int max_cnt = 0, index = 0;
    for(int i = 1; i <= N; i++) {
        if(cnt[i] > max_cnt) {
            max_cnt = cnt[i]; index = i;
        }
    }
    printf("%d\n%d\n", N - max_cnt, index);
}

int main() {
    ReadInput();
    DFS();
    WriteOutput();
    return 0;
}
