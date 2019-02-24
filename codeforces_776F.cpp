/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using std::vector;

FILE *fin = freopen("main.in", "r", stdin);
FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 1 + 100000;

/*-------- Input data --------*/
int N, M;
vector<int > adj[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 1; i < N; i++) {
        adj[i].push_back(i + 1);
        adj[i + 1].push_back(i);
    }
    adj[1].push_back(N); adj[N].push_back(1);
}

void GetZones() {
    for(int i = 3; i <= N; i++) {
        for(int j = 1; j < (int))
    }
}

int main() {
    ReadInput();
    GetZones();
    return 0;
}
