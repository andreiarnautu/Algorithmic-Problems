/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("biperm.in", "r", stdin);
FILE *fout = freopen("biperm.out", "w", stdout);

const int MAX_N = 1 + 10000;

int A[MAX_N], B[MAX_N];
int N;

/* (1) = sirul 1, (2) = sirul 2 */

struct Edge {
    int vertex, type, index;
    /* type == 1 daca muchia este (1) -> (2), type == 2 altfel */
    Edge(const int &vertex, const int &type, const int &index) {
        this->vertex = vertex; this->type = type; this->index = index;
    }
};

vector <Edge> G[MAX_N];
vector <int> vec, w;
bool checked[MAX_N];
bool swapped[MAX_N];

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &A[i]);
    }
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &B[i]);
    }
}

void makeGraph() {
    for(int i = 1; i <= N; ++i) {
        G[A[i]].push_back(Edge(B[i], 1, i));
        G[B[i]].push_back(Edge(A[i], 2, i));
    }
}

int getCycle(int node) {
    int previous = 0;
    vec.clear(); w.clear();

    checked[node] = true;
    vec.push_back(1);
    previous = node;
    /* vrem ca prima muchie sa fie mereu orientata (1) -> (2) */
    if(G[node][0].type == 1) {
        node = G[node][0].vertex;
        w.push_back(G[node][0].index);
    }
    else {
        previous = G[node][1].vertex;
        w.push_back(G[node][1].index);
    }

    while(1) {
        checked[node] = true;
        if(previous == G[node][0].vertex) {
            vec.push_back(G[node][1].type);
            w.push_back(G[node][1].index);
            previous = node;
            node = G[node][1].vertex;
        }
        else {
            vec.push_back(G[node][0].type);
            w.push_back(G[node][0].index);
            previous = node;
            node = G[node][0].vertex;
        }

        if(checked[node]) {
            break;
        }
    }

    int edgeCount = (int)vec.size(), good = 0;
    for(int i = 0; i < edgeCount; i++) {
        if(vec[i] == 1) {
            good++;
        }
    }

    int answer = min(good, edgeCount - good);
    if(good < edgeCount - good) {
        for(int i = 0; i < edgeCount; ++i) {
            if(vec[i] == 1) {
                swapped[w[i]] = true;
            }
        }
    }
    else {
        for(int i = 0; i < edgeCount; ++i) {
            if(vec[i] == 2) {
                swapped[w[i]] = true;
            }
        }
    }
    return answer;
}

int main() {
    readData();
    makeGraph();

    int cycleCount = 0, minSwaps = 0;
    for(int i = 1; i <= N; ++i) {
        if(!checked[A[i]]) {
            if(A[i] == B[i]) {
                /* evident, nu are niciun sens sa schimbam perechea, iar numarul de solutii nu creste */
                continue;
            }
            minSwaps += getCycle(A[i]);
            cycleCount++;
        }
    }

    printf("%lld %d\n", 1LL << cycleCount, minSwaps);
    for(int i = 1; i <= N; ++i) {
        if(swapped[i]) {
            printf("%d ", B[i]);
        }
        else {
            printf("%d ", A[i]);
        }
    }
    printf("\n");
    for(int i = 1; i <= N; ++i) {
        if(swapped[i]) {
            printf("%d ", A[i]);
        }
        else {
            printf("%d ", B[i]);
        }
    }
    return 0;
}
