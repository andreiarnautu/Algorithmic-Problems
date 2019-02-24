/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using std::min;
using std::stack;
using std::vector;
FILE *fin = freopen("andrei.in", "r", stdin);
FILE *fout = freopen("andrei.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MAX_NODES = MAX_N << 1;

/*-------- Input data --------*/
int N, M;
/*-------- Graph --------*/
int total_nodes;
vector< int > graph[MAX_NODES];
/*-------- Tarjan's algorithm --------*/
int node_index[MAX_NODES], node_lowlink[MAX_NODES], crt_index;

bool in_stack[MAX_NODES];
stack< int > my_stack;

vector< int > crt_scc;
int node_value[MAX_NODES];
/*-------- --------*/

int OppositeNode(int node) {
    if(node <= N) {
        return node + N;
    } else {
        return node - N;
    }
}

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v, color;
        scanf("%d%d%d", &u, &v, &color);

        if(color == 0) {  // (u or v)
            graph[OppositeNode(u)].push_back(v);
            graph[OppositeNode(v)].push_back(u);
        } else if(color == 1) {  // (!u or !v)
            graph[u].push_back(OppositeNode(v));
            graph[v].push_back(OppositeNode(u));
        } else {  // !(u xor v) == (!u or v) and (u or !v)
            graph[u].push_back(v);
            graph[OppositeNode(v)].push_back(OppositeNode(u));
            graph[OppositeNode(u)].push_back(OppositeNode(v));
            graph[v].push_back(u);
        }
    }
}

void ProcessScc() {
    bool ok = true;
    for(int node : crt_scc) {
        if(node_value[node] == 0) {
            ok = false; break;
        }
    }

    for(int node : crt_scc) {
        node_value[node] = ok;
        node_value[OppositeNode(node)] = ok ^ true;
    }
}

void StrongConnect(int node) {
    crt_index ++;
    node_index[node] = node_lowlink[node] = crt_index;
    my_stack.push(node); in_stack[node] = true;

    for(int nxt_node : graph[node]) {
        if(!node_index[nxt_node]) {
            StrongConnect(nxt_node);
            node_index[node] = min(node_index[node], node_lowlink[nxt_node]);
        } else if(in_stack[nxt_node]) {
            node_index[node] = min(node_index[node], node_index[nxt_node]);
        }
    }

    if(node_index[node] == node_lowlink[node]) {
        crt_scc.clear();
        int crt_node;
        do {
            crt_node = my_stack.top(); my_stack.pop();
            in_stack[crt_node] = false;
            crt_scc.push_back(crt_node);
        }while(crt_node != node);

        ProcessScc();
    }
}

void RunTarjan() {
    total_nodes = N << 1;
    for(int i = 1; i <= total_nodes; i++) {
        node_value[i] = -1;
    }
    for(int i = 1; i <= total_nodes; i++) {
        if(!node_index[i]) {
            StrongConnect(i);
        }
    }
}

void WriteOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%d ", node_value[i]);
    }
}

int main() {
    ReadInput();
    RunTarjan();
    WriteOutput();
    return 0;
}
}
