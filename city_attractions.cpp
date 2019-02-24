/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int kMaxN = 3e5 + 1;
const int root = 1;

/*-------- Structures --------*/
struct Next {
    int node, distance;
    Next() {
        node = 0; distance = -kMaxN;
    }
    Next(const int node, const int distance) {
        this->node = node; this->distance = distance;
    }
    bool operator <(const Next &other) const {
        if(this->distance != other.distance) {
            return this->distance < other.distance;
        } else {
            return this->node > other.node;
        }
    }
};
/*-------- Input data --------*/
int N;
long long K;
int beauty[kMaxN];
std::vector<int > graph[kMaxN];
/*-------- DFS data --------*/
Next underMinus[kMaxN], underPlus[kMaxN];
Next above[kMaxN];
/*-------- Finish --------*/
int nextNode[kMaxN];

int cycle[kMaxN], position[kMaxN];
int cursor;
bool checked[kMaxN];
/*-------- --------*/

void ReadInput() {
    scanf("%d", &N); scanf("%lld", &K);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &beauty[i]);
    }
    for(int i = 1; i < N; i++) {
        int x, y; scanf("%d%d", &x, &y);
        graph[x].push_back(y); graph[y].push_back(x);
    }
}

inline void UnderDFS(int node, int father) {
    for(auto adjNode : graph[node]) {
        if(adjNode != father) {
            UnderDFS(adjNode, node);
            Next next = underPlus[adjNode]; next.distance --;
            underMinus[node] = std::max(underMinus[node], next);
        }
    }
    underPlus[node] = std::max(underMinus[node], {node, beauty[node]});
}

inline void AboveDFS(int node, int father) {
    std::vector<Next > list;
    list.push_back(above[node]); list.push_back({node, beauty[node]});
    for(auto adjNode : graph[node]) {
        if(adjNode != father) {
            auto x = underPlus[adjNode]; x.distance--;
            list.push_back(x);
        }
    }
    std::sort(list.begin(), list.end()); std::reverse(list.begin(), list.end());
    for(auto adjNode : graph[node]) {
        if(adjNode != father) {
            if(list[0].node == underPlus[adjNode].node) {
                above[adjNode] = list[1];
            } else {
                above[adjNode] = list[0];
            }
            above[adjNode].distance --;
            AboveDFS(adjNode, node);
        }
    }
}

void PrintAnswer() {
    for(int i = 1; i <= N; i++) {
        auto next = std::max(underMinus[i], above[i]);
        nextNode[i] = next.node;
    }

    int node = nextNode[root], length = 0;
    while(!checked[node]) {
        cursor ++; length ++;
        cycle[cursor] = node; position[node] = cursor; checked[node] = true;
        node = nextNode[node];
    }

    if(K < position[node]) {
        printf("%d\n", cycle[K]);
    } else {
        length -= (position[node] - 1);
        K -= position[node];
        printf("%d\n", cycle[position[node] + K % length]);
    }
}

int main() {
    ReadInput();
    UnderDFS(root, 0);
    AboveDFS(root, 0);
    PrintAnswer();
    return 0;
}
