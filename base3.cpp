/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>

#define mp           make_pair
#define pb           push_back
#define fi           first
#define se           second
#define dim          100000
#define inf          2000000000
#define inFile       "base3.in"
#define outFile      "base3.out"
#define father(i)    (i / 2)
#define left_son(i)  (i * 2)
#define right_son(i) (i * 2 + 1)
#define d(i)         (50000 + i)

using namespace std;

vector < pair<int,int> > G[dim];
vector < pair<int,int> >::iterator it;

int heap[dim], pos[dim], dmin[dim], inQueue[dim];
int n, nr, L[4];
char s[dim];

void up(int node) {

    int key = dmin[heap[node]], ind = heap[node], k = node;

    while(k > 1 && key < dmin[heap[father(k)]]) {

        pos[heap[father(k)]] = k;
        heap[k] = heap[father(k)];
        k = father(k);
    }
    heap[k] = ind;
    pos[ind] = k;
}

void down(int node) {

    int key = dmin[heap[node]], ind = heap[node], k = node, son = 1;

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

    heap[++nr] = node;
    pos[node] = nr;
    up(nr);
}

void popHeap() {

    pos[heap[nr]] = 1;
    heap[1] = heap[nr--];

    if(nr)
        down(1);
}

void readData() {

    freopen(inFile, "r", stdin);

    int len;
    gets(s); L[1] = len = strlen(s);
    for(int i = 0; i < len; ++i)
        if(s[i] == '1') {

            dmin[ d( i - (len - 1 - i) ) ] = len;
            if(!inQueue[ d(i - (len - 1 - i)) ]) {

                inQueue[ d(i - (len - 1 - i)) ] = 1;
                add( d(i - (len - 1 - i)) );
            }
        }

    gets(s); L[2] = len = strlen(s);
    for(int i = 0; i < len; ++i)
        if(s[i] == '1') {

            dmin[ d( i - (len - 1 - i) ) ] = len;
            if(!inQueue[ d(i - (len - 1 - i)) ]) {

                inQueue[ d(i - (len - 1 - i)) ] = 1;
                add( d(i - (len - 1 - i)) );
            }
        }

    gets(s); L[3] = len = strlen(s);
    for(int i = 0; i < len; ++i)
        if(s[i] == '1') {

            dmin[ d( i - (len - 1 - i) ) ] = len;
            if(!inQueue[ d(i - (len - 1 - i)) ]) {

                inQueue[ d(i - (len - 1 - i)) ] = 1;
                add( d(i - (len - 1 - i)) );
            }
        }
}

void dijkstra() {

    int low = d(-L[1] - L[2] - L[3]), high = d(L[1] + L[2] + L[3]);

    while(nr) {

        int node = heap[1]; popHeap();
        inQueue[node] = 0;


        for(int i = 1; i <= 3; ++i) {

            if(low <= node - L[i] && dmin[node] + L[i] < dmin[node - L[i]]) {

                dmin[node - L[i]] = dmin[node] + L[i];
                if(!inQueue[node - L[i]]) {

                    inQueue[node - L[i]] = 1;
                    add(node - L[i]);
                }
                else
                    up(pos[node - L[i]]);
            }

            if(high >= node + L[i] && dmin[node] + L[i] < dmin[node + L[i]]) {

                dmin[node + L[i]] = dmin[node] + L[i];
                if(!inQueue[node + L[i]]) {

                    inQueue[node + L[i]] = 1;
                    add(node + L[i]);
                }

                else
                    up(pos[node + L[i]]);
            }
        }
    }
}

void writeData() {

    freopen(outFile, "w", stdout);

    printf("%d", (dmin[d(0)] == inf ? 0 : dmin[d(0)]) );
}

int main() {

    for(int i = 0; i < dim; ++i)
        dmin[i] = inf;
    readData();
    dijkstra();
    writeData();
}
