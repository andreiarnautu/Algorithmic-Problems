/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using std::queue;
using std::vector;

FILE *fin = freopen("casute.in", "r", stdin);
FILE *fout = freopen("casute.out", "w", stdout);

const int MAX_N = 1 + 3000;
const int MAX_INF = 0x3fffffff;
const int mod = 666013;

/*-------- Input data --------*/
int N, M;
int height[MAX_N];
vector<short int > graph[MAX_N];
/*-------- Algorithm data --------*/
bool checked[MAX_N];
short int lca[MAX_N][MAX_N];

short int degree[MAX_N];
queue<short int > my_queue;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &height[i]);
    }
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[v].push_back((short int)u);
        degree[u] ++;
    }
}

void DFS(int start, int node) {
    checked[node] = true;
    lca[start][node] = lca[node][start] = start;

    for(short int next : graph[node]) {
        if(!checked[next]) {
            DFS(start, next);
        }
    }
}

void GetLCA() {
    height[0] = MAX_INF;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            checked[j] = false;
        }
        DFS(i, i);
    }

    for(int i = 1; i <= N; i++) {
        if(degree[i] == 0) {
            my_queue.push((short int)i);
        }
    }

    while(!my_queue.empty()) {
        short int node = my_queue.front(); my_queue.pop();

        for(short int next : graph[node]) {
            for(int i = 1; i <= N; i++) {
                if(height[lca[node][i]] < height[lca[next][i]]) {
                    lca[next][i] = lca[i][next] = lca[node][i];
                }
            }
            --degree[next];
            if(!degree[next]) {
                my_queue.push(next);
            }
        }
    }
}

void WriteOutput() {
    int solution = 0;
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            //printf("%d ", lca[i][j]);
            solution = (solution * (N + 1) + lca[i][j]) % mod;
        }
        //printf("\n");
    }

    printf("%d\n", solution);
}

int main() {
    ReadInput();
    GetLCA();
    WriteOutput();
    return 0;
}
