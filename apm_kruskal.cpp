/**
  *  Worg
  */
#include <tuple>
#include <cstdio>
#include <algorithm>

using std::pair;
using std::tuple;
using std::vector;

FILE *fin = freopen("apm.in", "r", stdin);
FILE *fout = freopen("apm.out", "w", stdout);

const int kMaxN = 1 + 200000;
const int kMaxM = 1 + 400000;

/*-------- Input data --------*/
int N, M;
tuple<int, int, int > edges[kMaxM];
/*-------- Algorithm data --------*/
int father[kMaxN];
vector<pair<int, int > > apm;
int apm_cost;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; i++) {
        int u, v, cost; scanf("%d%d%d", &u, &v, &cost);
        edges[i] = std::make_tuple(cost, u, v);  //  Punem costul primul fiindca dupa el vrem sa sortam
    }
}

int Group(int node) {
    if(node != father[node]) {
        father[node] = Group(father[node]);
    }
    return father[node];
}

void Unite(int u, int v) {
    father[Group(u)] = Group(v);
}

void GetAPM() {
    sort(edges, edges + M);
    for(int i = 1; i <= N; i++) {
        father[i] = i;
    }


    for(int i = 0; i < M; i++) {
        int cost = std::get<0>(edges[i]);
        int u = std::get<1>(edges[i]);
        int v = std::get<2>(edges[i]);
        if(Group(u) != Group(v)) {
            apm_cost += cost;
            apm.push_back(std::make_pair(u, v));
            Unite(u, v);
        }
    }
}

void WriteAPM() {
    printf("%d\n", apm_cost);
    printf("%d\n", N - 1);
    for(pair<int, int >  edge : apm) {
        printf("%d %d\n", edge.first, edge.second);
    }
}

int main() {
    ReadInput();
    GetAPM();
    WriteAPM();
    return 0;
}
