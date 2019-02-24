/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#define fi              first
#define se              second
#define mp              make_pair
#define pb              push_back
#define father(i)       i / 2
#define leftSon(i)      i * 2
#define rightSon(i)     i * 2 + 1

using namespace std;
FILE *fin=freopen("dbz.in","r",stdin);
FILE *fout=freopen("dbz.out","w",stdout);

const int MAX_N = 1 + 1500, INF = 1000000000, bufferDim = 10000;

vector < pair<int,int> > G[MAX_N];
vector < pair<int,int> >::iterator it;

int dmin[MAX_N], father[MAX_N], color[MAX_N];
int n, m, x;

/********************inputReader********************/
class inputReader {

private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {

            return('0' <= c && c <= '9');
        }
public:

        void getBuffer() {

            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        int getInt() {

            int ret = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                ret = ret * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
            return ret;
        }
};

/********************heap********************/
class heap {

private:
        int pos[MAX_N], val[MAX_N];
        int dim;


public:

        heap() {

            dim = 0;
            for(int i = 1; i < MAX_N; ++i)
                pos[i] = val[i] = 0;
        }

        void down(int node) {

            int son = 1, k = node, key = dmin[val[node]], ind = val[node];
            while(son) {

                son = 0;
                if(leftSon(k) <= dim) {

                    son = leftSon(k);
                    if(rightSon(k) <= dim && dmin[val[rightSon(k)]] < dmin[val[leftSon(k)]])
                        son = rightSon(k);
                    if(dmin[val[son]] > key)
                        son = 0;
                }
                if(son) {

                    pos[val[son]] = k;
                    val[k] = val[son];
                    k = son;
                }
            }
            val[k] = ind;
            pos[ind] = k;
        }

        void up(int node) {

            int key = dmin[val[node]], k = node, ind = val[node];
            while(k > 1 && key < dmin[val[father(k)]]) {

                pos[val[father(k)]] = k;
                val[k] = val[father(k)];
                k = father(k);
            }
            val[k] = ind;
            pos[ind] = k;
        }

        int pop() {

            int ret = val[1];
            pos[val[1]] = 0;
            pos[val[dim]] = 1;
            val[1] = val[dim--];

            if(dim)
                down(1);
            return ret;
        }

        void push(int node) {

            val[++dim] = node;
            pos[node] = dim;
            up(dim);
        }

        bool inHeap(int node) {

            return pos[node];
        }

        bool empty() {

            return (dim == 0);
        }
};
/********************endClassDeclarations********************/

void readData() {

    inputReader cin; cin.getBuffer();
    n = cin.getInt(); m = cin.getInt();

    for(int i = 1; i <= m; ++i) {

        int x = cin.getInt(), y = cin.getInt(), z = cin.getInt();
        G[x].pb(mp(y, z));
        G[y].pb(mp(x, z));
    }
}

void dijkstra(int start) {

    for(int i = 1; i <= n; ++i)
        dmin[i] = father[i] = INF;
    heap h = heap();
    dmin[start] = 0; h.push(start);

    while(!h.empty()) {

        int node = h.pop();
        for(it = G[node].begin(); it != G[node].end(); it++)
            if(dmin[it->fi] > dmin[node] + it->se) {

                dmin[it->fi] = dmin[node] + it->se;
                father[it->fi] = node;
                int p = h.inHeap(it->fi);
                if(!p)
                    h.push(it->fi);
                else
                    h.up(p);
            }
    }
}

void dfs(int node, int val) {

    color[node] = val;
    for(vector < pair<int,int> >::iterator i = G[node].begin(); i != G[node].end(); ++i)
        if(father[i->fi] == node)
            dfs(i->fi, val);
}

void minCostCycle(int root) {

    int sol = INF;
    for(int i = 1; i <= n; ++i)
        for(it = G[i].begin(); it != G[i].end(); ++it)
            if(color[i] != color[it->fi] && i != father[it->fi] && it->fi != father[i])
                sol = min(sol, dmin[i] + it->se + dmin[it->fi]);
    printf("%d ", (sol == INF ? -1 : sol));
}

int main() {

    readData();
    for(int i = 1; i <= n; ++i) {

        dijkstra(i);
        for(int j = 1; j <= n; ++j)
            color[j] = 0;
        for(int j = 1; j <= n; ++j)
            if(father[j] == i)
                dfs(j, j);
        minCostCycle(i);
    }
    return 0;
}
