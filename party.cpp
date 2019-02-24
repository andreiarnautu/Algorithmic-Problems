/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("party.in", "r", stdin);
FILE *fout = freopen("party.out", "w", stdout);

const int MAX_N = 1 + 100;
const int MAX_NODES = MAX_N << 1;

/*-------- Input data --------*/
int N, M;
/*-------- Graph data --------*/
int total_nodes;
vector< int > graph[MAX_NODES];
/*-------- Tarjan's Algorithm --------*/
int crt_index;
int node_index[MAX_NODES], node_lowlink[MAX_NODES];

bool in_stack[MAX_NODES];
stack< int > my_stack;

vector< int > crt_scc;
int node_value[MAX_NODES];
/*-------- Solution --------*/
vector< int > participants;
/*-------- --------*/

int OppositeNode(const int node){
    if(node <= N) {
        return node + N;
    } else {
        return node - N;
    }
}

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int x, y, z; scanf("%d%d%d", &x, &y, &z);
        if(z == 0) { // (x or y)
            graph[OppositeNode(x)].push_back(y); graph[OppositeNode(y)].push_back(x);
        } else if(z == 1) {  // (x or !y)
            graph[OppositeNode(x)].push_back(OppositeNode(y)); graph[y].push_back(x);
        } else if(z == 2) {  // (!x or y)
            graph[x].push_back(y); graph[OppositeNode(y)].push_back(OppositeNode(x));
        } else {  // (!x or !y)
            graph[x].push_back(OppositeNode(y)); graph[y].push_back(OppositeNode(x));
        }
    }
}

void ProcessScc() {
    bool value = true;
    for(int node : crt_scc) {
        if(node_value[node] == 0) {
            value = false; break;
        }
    }

    for(int node : crt_scc) {
        node_value[node] = value;
        node_value[OppositeNode(node)] = value ^ true;
    }
}

void StrongConnect(const int node) {
    crt_index ++;
    node_index[node] = node_lowlink[node] = crt_index;
    my_stack.push(node); in_stack[node] = true;

    for(int nxt_node : graph[node]) {
        if(!node_index[nxt_node]) {
            StrongConnect(nxt_node);
            node_lowlink[node] = min(node_lowlink[node], node_lowlink[nxt_node]);
        } else if(in_stack[nxt_node]) {
            node_lowlink[node] = min(node_lowlink[node], node_index[nxt_node]);
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
        if(node_value[i] == 1) {
            participants.push_back(i);
        }
    }

    printf("%d\n", (int)participants.size());
    for(int i : participants) {
        printf("%d\n", i);
    }
}

int main() {
    ReadInput();
    RunTarjan();
    WriteOutput();
    return 0;
}
