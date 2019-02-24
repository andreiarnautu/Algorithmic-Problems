/**
  *  Worg
  */
#include <queue>
#include <cstdio>

using namespace std;
FILE *fin = freopen("cezar.in", "r", stdin);
FILE *fout = freopen("cezar.out", "w", stdout);

const int MAX_N = 1 + 10000;

vector <short int> G[MAX_N];
int n, k;

short int degree[MAX_N], subTree[MAX_N];
int answer;


struct Node {
    short int index;
    Node(const short int &index) {
        this->index = index;
    }
    bool operator <(const Node &other) const {
        return subTree[this->index] > subTree[other.index];
    }
};

priority_queue <Node> pq;

void readData() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i < n; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v); G[v].push_back(u);
        degree[u]++; degree[v]++;
    }
}

void initializePQ() {
    for(short int i = 1; i <= n; ++i) {
        subTree[i] = 1;
        if(degree[i] == 1) {
            pq.push(Node(i));
        }
    }
}

void solveProblem() {
    int chosen = 0, limit = n - 1 - k;
    while(chosen < limit) {
        Node node = pq.top(); pq.pop();
        answer += subTree[node.index];
        chosen++;
        for(vector <short int>::iterator it = G[node.index].begin(); it != G[node.index].end(); ++it) {
            degree[*it]--;
            subTree[*it] += subTree[node.index];
            if(degree[*it] == 1) {
                pq.push(Node(*it));
            }
        }
    }
    printf("%d", answer);
}

int main() {

    readData();
    initializePQ();
    solveProblem();
    return 0;
}
