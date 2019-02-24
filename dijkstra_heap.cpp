/**
  *  Worg
  *  Dijkstra using heaps
  */
#include <vector>
#include <fstream>

#define pb              push_back
#define mp              make_pair
#define fi              first
#define se              second
#define dim             50500
#define inf             100000000
#define father(i)       (i / 2)
#define left_son(i)     (i * 2)
#define right_son(i)    (i * 2 + 1)
#define inFile          "dijkstra.in"
#define outFile         "dijkstra.out"

using namespace std;

vector < pair<int,int> > G[dim];
vector < pair<int,int> >::iterator it;

int heap[dim], pos[dim], dmin[dim], inQueue[dim];
int n, m, nr;

void readData() {

    int x, y, z;
    ifstream cin(inFile);
    cin >> n >> m;

    for(int i = 1; i <= m; ++i) {

        cin >> x >> y >> z;
        G[x].pb(mp(y, z));
    }
}

void up(int node) {

    int key = dmin[heap[node]], k = node, ind = heap[node];

    while(k > 1 && key < dmin[heap[father(k)]]) {

        pos[heap[father(k)]] = k;
        heap[k] = heap[father(k)];
        k = father(k);
    }
    heap[k] = ind;
    pos[ind] = k;
}

void down(int node) {

    int son = 1, k = node, key = dmin[heap[node]], ind = heap[node];

    while(son) {

        son = 0;
        if(left_son(k) <= nr) {

            son = left_son(k);
            if(right_son(k) <= nr && dmin[heap[right_son(k)]] < dmin[heap[left_son(k)]])
                son = right_son(k);

            if(dmin[heap[son]] > key)
                son = 0;
        }

        if(son) {

            pos[heap[son]] = k;
            heap[k] = heap[son];
            k = son;
        }
    }

    heap[k] = ind;
    pos[ind] = k;
}

void add(int node) {

    ++nr;
    heap[nr] = node;
    pos[node] = nr;
    up(nr);
}

void popHeap() {

    pos[heap[nr]] = 1;
    heap[1] = heap[nr];
    --nr;

    if(nr)
        down(1);
}

void dijkstra() {

    for(int i = 1; i <= n; ++i)
        dmin[i] = (int)inf;

    add(1);
    dmin[1] = 0, inQueue[1] = 1, pos[1] = 1;

    int node;
    while(nr) {

        node = heap[1];
        inQueue[node] = 0;
        popHeap();

        for(it = G[node].begin(); it != G[node].end(); ++it) {

            if(!inQueue[it->fi] && dmin[node] + it->se < dmin[it->fi]) {

                inQueue[it->fi] = 1;
                dmin[it->fi] = it->se + dmin[node];
                add(it->fi);
            }
            else if (dmin[node] + it->se < dmin[it->fi]) {

                dmin[it->fi] = dmin[node] + it->se;
                up(pos[it->fi]);
            }

        }
        /*for(int i = 1; i <= nr; ++i)
            printf("%d %d, ", heap[i], dmin[heap[i]]);
        printf("\n");*/
    }
}

void writeData() {

    ofstream cout(outFile);
    for(int i = 2; i <= n; ++i)
        cout << (dmin[i] == inf ? 0 : dmin[i]) << " ";
}

int main() {

    readData();
    dijkstra();
    writeData();
    return 0;
}
