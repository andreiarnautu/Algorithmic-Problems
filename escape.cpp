/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using std::pair;
using std::queue;
using std::vector;

FILE *fin = freopen("escape.in", "r", stdin);
FILE *fout = freopen("escape.out", "w", stdout);

const int kMaxN = 1 + 500;
const int kMaxK = 1 + 50;

/*-------- Input data --------*/
int N, M, K;
int color[kMaxN];
int edge[kMaxN][kMaxK];

vector<int > entering[kMaxN][kMaxK];
/*-------- Algorithm data --------*/
int wrong[kMaxN][kMaxN];

queue<pair<int, int > > my_queue;
/*-------- Solution --------*/
bool chosen[kMaxN];

/*-------- --------*/

void ReadInput() {
    scanf("%d%d%d", &N, &M, &K);
    for(int i = 1; i <= M; i++) {
        int node; scanf("%d", &node);
        color[node] = 1;
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= K; j++) {
            scanf("%d", &edge[i][j]);
            entering[edge[i][j]][j].push_back(i);
        }
    }

}

void GetWrong() {
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            bool ok = true;
            for(int k = 1; k <= K; k++) {
                if(color[edge[i][k]] != color[edge[j][k]]) {
                    ok = false; break;
                }
            }

            if(color[i] != color[j]) {
                ok =false;
            }

            if(!ok) {
                wrong[i][j] = wrong[j][i] = 1;
                my_queue.push(std::make_pair(i, j));
            }
        }
    }
}

void RunAlgo() {
    while(!my_queue.empty()) {
        pair<int, int > p = my_queue.front();
        my_queue.pop();

        for(int i = 1; i <= K; i++) {
            for(int u : entering[p.first][i]) {
                for(int v : entering[p.second][i]) {
                    int x = std::min(u, v);
                    int y = std::max(u, v);

                    if(!wrong[x][y]) {
                        wrong[x][y] = wrong[y][x] = 1;
                        my_queue.push(std::make_pair(x, y));
                    }
                }
            }
        }
    }
}

void WriteSolution() {
    for(int i = 1; i <= N; i++) {
        if(!chosen[i]) {
            printf("%d ", i);
            chosen[i] = true;
            for(int j = i + 1; j <= N; j++) {
                if(!chosen[j] && !wrong[i][j]) {
                    printf("%d ", j);
                    chosen[j] = true;
                }
            }
            printf("\n");
        }
    }
}

int main() {
    ReadInput();
    GetWrong();
    RunAlgo();
    WriteSolution();
    return 0;
}
