/**
  *  Worg
  */
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

#define pb              push_back
#define father(i)       i / 2
#define leftSon(i)      i * 2
#define rightSon(i)     i * 2 + 1

using namespace std;
FILE *fin = freopen("desen.in", "r", stdin);
FILE *fout = freopen("desen.out", "w", stdout);

const int MAX_N = 1 + 1000;

struct punct {

    int x, y;

    punct(const int &x, const int &y) {

        this->x = x, this->y = y;
    }
};

struct neighbour {

    int vertex;
    double cost;

    neighbour(const int &vertex, const double &cost) {

        this->vertex = vertex, this->cost = cost;
    }
};

struct edge {

    int a, b;
    double cost;

    edge(int a, int b, double cost) {

        this->a = a, this->b = b, this->cost = cost;
    }
    bool operator <(const edge &other) const {

        return this->cost > other.cost;
    }
};

class priorityQueue {

private:
        vector < edge > heap;
        int dim;

public:
        priorityQueue() {

            dim = 0;
            heap.pb(edge(0, 0, 0));
        }

        void up(int node) {

            edge key = heap[node];
            while(node > 1 && key.cost < heap[father(node)].cost) {

                heap[node] = heap[father(node)];
                node = father(node);
            }
            heap[node] = key;
        }

        void down(int node) {

            int son = 1;
            edge key = heap[node];

            while(son) {

                son = 0;
                if(leftSon(node) <= dim) {

                    son = leftSon(node);
                    if(rightSon(node) <= dim && heap[rightSon(node)].cost < heap[leftSon(node)].cost)
                        son = rightSon(node);
                    if(key.cost < heap[son].cost)
                        son = 0;
                }
                if(son) {

                    heap[node] = heap[son];
                    node = son;
                }
            }
            heap[node] = key;
        }

        void push(const edge &newEdge) {

            heap.pb(newEdge);
            up(++dim);
        }

        edge top() {

            return heap[1];
        }

        void pop() {

            heap[1] = heap[dim--];
            heap.pop_back();
            if(dim)
                down(1);
        }

        bool empty() {

            return dim == 0;
        }
} candidates = priorityQueue();

vector < punct > p;
vector < edge > chosen;
vector < neighbour > G[MAX_N];

double minEdge[MAX_N];
bool solved[MAX_N];

double dist(const punct &p1, const punct &p2) {

    return (double)sqrt((double)(p1.x - p2.x) * (double)(p1.x - p2.x) + (double) (p1.y - p2.y) * (double)(p1.y - p2.y));
}

void addEdges(int pos) {

    for(int i = 0; i < pos - 1; ++i) {

        G[pos].pb(neighbour(i + 1, dist(p[pos - 1], p[i])));
        G[i + 1].pb(neighbour(pos, dist(p[pos - 1], p[i])));
    }
}

void init(int pos) {

    for(int i = 1; i <= pos; ++i)
        solved[i] = false, minEdge[i] = 1000000;
    solved[1] = true;
    for(vector < neighbour >::iterator it = G[1].begin(); it != G[1].end(); ++it)
        candidates.push(edge(1, it->vertex, it->cost));
}

void getAPM(int pos) {

    double sol = 0;
    int needed = pos - 1;
    while(!candidates.empty() && needed) {

        edge Edge = candidates.top(); candidates.pop();
        if(!(solved[Edge.a] && solved[Edge.b])) {

            --needed;
            sol += Edge.cost;
            chosen.pb(Edge);
            int newNode = (solved[Edge.a] == true) ? Edge.b : Edge.a;
            solved[newNode] = true;
            for(vector < neighbour >::iterator it = G[newNode].begin(); it != G[newNode].end(); ++it)
                if(!solved[it->vertex] && minEdge[it->vertex] > it->cost) {

                    candidates.push(edge(newNode, it->vertex, it->cost));
                    minEdge[it->vertex] = it->cost;
                }
        }
    }
    while(!candidates.empty())
        candidates.pop();

    for(int i = 1; i <= pos; ++i)
        G[i].clear();
    for(vector < edge >::iterator it = chosen.begin(); it != chosen.end(); ++it) {

        G[it->a].pb(neighbour(it->b, it->cost));
        G[it->b].pb(neighbour(it->a, it->cost));
    }
    chosen.clear();
    printf("%.6f\n", sol);
}

int main() {

    int n, a, b;
    scanf("%d ", &n);

    for(int i = 1; i <= n; ++i) {

        scanf("%d %d ", &a, &b);
        p.pb(punct(a, b));
        addEdges(i);
        init(i);
        getAPM(i);
    }
    return 0;
}
