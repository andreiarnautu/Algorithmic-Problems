/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

FILE *fin = freopen("metro.in", "r", stdin); FILE *fout = freopen("metro.out", "w", stdout);

const int kMaxN = 2e5 + 10;

/*-------- Structures --------*/
struct Node; struct Chain;

struct Path {
    int u, v, index;

    Path(const int _u, const int _v, const int _index) {
        u = _u; v = _v; index = _index;
    }

    bool operator <(const Path &other) const {
        return this->index < other.index;
    }
};

struct SegmentTreeNode {
    bool lazy;
    int lazySwitch, normalSwitch;
    long long odd, even, lazyOdd, lazyEven;

    SegmentTreeNode() {
        lazy = false;
        lazySwitch = normalSwitch = odd = even = lazyOdd = lazyEven = 0;
    }
};

struct Node {
    int index, depth, weight;
    long long answer;
    std::vector<Node* > list;
    Node *father, *bestSon;
    Chain *chain;

    Node() {depth = weight = answer = 0;}
};

struct Chain {
    bool solved;

    int delay, maxDepth;
    std::vector<Node* > nodes;
    std::vector<SegmentTreeNode > segtree;
    Node *father;

    Chain() {solved = false;}
};
/*-------- Input data --------*/
int N, M;
Node *graph[kMaxN];
std::vector<Node* > nodeList;
std::vector<Path > paths;
/*-------- --------*/

void ReadGraph() {
    scanf("%d%d", &N, &M);

    for(int i = 0; i <= N; i++) {
        graph[i] = new Node; graph[i]->index = i;
    }

    for(int i = 0; i < N - 1; i++) {
        int u, v; scanf("%d%d", &u, &v);
        graph[u]->list.push_back(graph[v]);
        graph[v]->list.push_back(graph[u]);
    }
}

void DFS(Node *node) {
    nodeList.push_back(node);
    node->weight = 1;
    for(auto adjNode : node->list) {
        if(adjNode != node->father) {
            adjNode->father = node; adjNode->depth = node->depth + 1;
            DFS(adjNode);
            node->weight += adjNode->weight;
        }
    }
}

void Decompose() {
    graph[1]->depth = 1; graph[1]->father = graph[0]; DFS(graph[1]);


    for(int i = (int)nodeList.size() - 1; i >= 0; i--) {
        Node* node = nodeList[i]; node->bestSon = new Node();

        for(Node* son : node->list) {
            if(son != node->father) {
                if(son->weight > node->bestSon->weight) {
                    node->bestSon = son;
                }
            }
        }

        if(node->bestSon->weight == 0) {
            node->chain = new Chain();
        } else {
            node->chain = node->bestSon->chain;
            for(auto son : node->list) {
                if(son != node->father && son != node->bestSon) {
                    son->chain->father = node;
                }
            }
        }
        node->chain->nodes.push_back(node);
    }
    graph[1]->chain->father = graph[0];
}

void BuildSegmentTrees() {
    for(int i = 1; i <= N; i++) {
        Chain *chain = graph[i]->chain;

        if(chain->solved == false) {
            chain->segtree.resize((chain->nodes.size() + 1) << 2);

            chain->delay = chain->father->depth;
            chain->maxDepth = chain->nodes[0]->depth;

            chain->solved = true;
        }
    }
}

void Propagate(std::vector<SegmentTreeNode > &segtree, int from, int to) {
    if(segtree[from].lazy == 1 && to < (int)segtree.size()) {
        if(segtree[to].lazySwitch == 0) {
            segtree[to].lazyOdd += segtree[from].lazyOdd;
            segtree[to].lazyEven += segtree[from].lazyEven;
        } else {
            segtree[to].lazyOdd += segtree[from].lazyEven;
            segtree[to].lazyEven += segtree[from].lazyOdd;
        }
        segtree[to].lazySwitch = (segtree[to].lazySwitch + segtree[from].lazySwitch) % 2;
        segtree[to].lazy = true;
    }
}

void AutoUpdate(std::vector<SegmentTreeNode > &segtree, int node) {
    if(segtree[node].lazy == true) {
        if(segtree[node].normalSwitch == 0) {
            segtree[node].odd += segtree[node].lazyOdd;
            segtree[node].even += segtree[node].lazyEven;
        } else {
            segtree[node].odd += segtree[node].lazyEven;
            segtree[node].even += segtree[node].lazyOdd;
        }
        segtree[node].normalSwitch = (segtree[node].lazySwitch + segtree[node].normalSwitch) % 2;

        segtree[node].lazy = false;
        segtree[node].lazyOdd = segtree[node].lazyEven = segtree[node].lazySwitch = 0;
    }
}

void Update(std::vector<SegmentTreeNode > &segtree, int node, int left, int right, int first, int last, int value) {
    int leftSon = node << 1, rightSon = leftSon + 1, mid = (left + right) >> 1;

    Propagate(segtree, node, leftSon); Propagate(segtree, node, rightSon);
    AutoUpdate(segtree, node);

    if(first <= left && right <= last) {
        segtree[node].lazyOdd = value; segtree[node].lazySwitch = 1; segtree[node].lazy = true;
    } else {
        if(first <= mid) {
            Update(segtree, leftSon, left, mid, first, last, value);
        }
        if(mid < last) {
            Update(segtree, rightSon, mid + 1, right, first, last, value);
        }
    }
}

void UpdatePath(Node *u, Node *v, int value) {
    if(u->chain == v->chain) {
        int h1 = std::min(u->depth, v->depth);
        int h2 = std::max(u->depth, v->depth);
        Update(u->chain->segtree, 1, 1, u->chain->maxDepth - u->chain->delay, h1 - u->chain->delay, h2 - u->chain->delay, value);
    } else if(v == graph[0] || u->chain->father->depth >= v->chain->father->depth) {
        Update(u->chain->segtree, 1, 1, u->chain->maxDepth - u->chain->delay, 1, u->depth - u->chain->delay, value);
        UpdatePath(u->chain->father, v, value);
    } else {
        Update(v->chain->segtree, 1, 1, v->chain->maxDepth - v->chain->delay, 1, v->depth - v->chain->delay, value);
        UpdatePath(u, v->chain->father, value);
    }
}

void ProcessPaths() {
    for(int i = 1; i <= M; i++) {
        int u, v, index; scanf("%d%d%d", &u, &v, &index);
        paths.push_back({u, v, index});
    }

    std::sort(paths.begin(), paths.end());
    for(auto path : paths) {
        UpdatePath(graph[path.u], graph[path.v], path.index);
    }
}

long long GetValue(std::vector<SegmentTreeNode > &segtree, int node, int left, int right, int position) {
    int leftSon = node << 1, rightSon = leftSon + 1, mid = (left + right) >> 1;

    Propagate(segtree, node, leftSon); Propagate(segtree, node, rightSon);
    AutoUpdate(segtree, node);

    if(left == right) {
        return segtree[node].odd;
    } else {
        if(position <= mid) {
            return GetValue(segtree, leftSon, left, mid, position);
        } else {
            return GetValue(segtree, rightSon, mid + 1, right, position);
        }
    }
}

void WriteOutput() {
    for(int i = 1; i <= N; i++) {
        printf("%lld\n", GetValue(graph[i]->chain->segtree, 1, 1, graph[i]->chain->maxDepth - graph[i]->chain->delay, graph[i]->depth - graph[i]->chain->delay));
    }
}

int main() {
    ReadGraph();

    Decompose();

    BuildSegmentTrees();

    ProcessPaths();

    WriteOutput();

    return 0;
}
