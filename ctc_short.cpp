/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::stack;
using std::vector;

FILE *fin = freopen("ctc.in", "r", stdin);
FILE *fout = freopen("ctc.out", "w", stdout);

const int kMaxN = 1 + 100000;

/*-------- Input data --------*/
int N, M;
vector<int > graph[kMaxN];
/*-------- Tarjan --------*/
int lowlink[kMaxN], index[kMaxN];
int crt_index;

stack<int > my_stack;
bool in_stack[kMaxN];

vector<int > scc;
vector<vector<int > > scc_list;
/*-------- --------*/

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u].push_back(v);
    }
}

void StrongConnect(int node) {
    crt_index ++;
    index[node] = crt_index; lowlink[node] = crt_index;
    my_stack.push(node); in_stack[node] = true;

    for(int next : graph[node]) {
        if(!index[next]) {
            StrongConnect(next);
            lowlink[node] = std::min(lowlink[node], lowlink[next]);
        } else if(in_stack[next]) {
            lowlink[node] = std::min(lowlink[node], index[next]);
        }
    }

    if(index[node] == lowlink[node]) {
        scc.clear();
        int now;
        do {
            now = my_stack.top(); my_stack.pop();
            in_stack[now] = false;
            scc.push_back(now);
        }while(now != node);
        scc_list.push_back(scc);
    }
}

void RunTarjan() {
    for(int i = 1; i <= N; i++) {
        if(!index[i]) {
            StrongConnect(i);
        }
    }
}

void WriteOutput() {
    printf("%d\n", (int)scc_list.size());
    for(vector<int > crt_scc : scc_list) {
        for(int node : crt_scc) {
            printf("%d ", node);
        }
        printf("\n");
    }
}

int main() {
    ReadInput();
    RunTarjan();
    WriteOutput();
    return 0;
}
