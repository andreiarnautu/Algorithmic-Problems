/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using std::vector;

FILE *fin = freopen("arbpal.in", "r", stdin);
FILE *fout = freopen("arbpal.out", "w", stdout);

const int MAX_N = 1 + 5000;

/*-------- Input data --------*/
int N;
char value[MAX_N];
vector<int > graph[MAX_N];
/*-------- Algorithm --------*/
int solution;
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N);
    for(int i = 1; i < N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v); graph[v].push_back(u);
    }
    for(int i = 1; i <= N; i++) {
        scanf(" %c", &value[i]);
    }
}

void DFS(int u, int v, int prev_u, int prev_v) {
    solution ++;

    for(int next_u : graph[u]) {
        for(int next_v : graph[v]) {
            if(next_u != prev_u && next_v != prev_v && next_u != next_v && value[next_u] == value[next_v]) {
                DFS(next_u, next_v, u, v);
            }
        }
    }
}

void GetSolutions() {
    //  Intai tratam sirurile de lungime impara
    for(int i = 1; i <= N; i++) {
        DFS(i, i, i, i);
    }

    //  Apoi sirurile cu lungime para
    for(int i = 1; i <= N; i++) {
        for(int j : graph[i]) {
            if(value[i] == value[j]) {
                DFS(i, j, j, i);
            }
        }
    }
}

int main() {
    ReadInput();
    GetSolutions();
    printf("%d\n", solution);
    return 0;
}
