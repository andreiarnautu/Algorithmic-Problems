/**
  *  Worg
  */
#include <queue>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>

#define fi      first
#define se      second
#define pb      push_back
#define mp      make_pair
#define Nmax    52
#define Tmax    102
#define dim     5003
#define inFile  "algola.in"
#define outFile "algola.out"

using namespace std;

queue  < pair<short int,short int> > Q;
vector < pair<short int,short int> > G[Nmax][Tmax];
vector < pair<short int,short int> >::iterator it;
pair   < short int, short int > sink, source, node, null, father[Nmax][Tmax], aux;

short int c[Nmax][Tmax][Nmax][Tmax], f[Nmax][Tmax][Nmax][Tmax];
short int A[dim], X[dim], Y[dim], L[dim];
short int n, m, flow, total;


void makeEdge(int node_1, int time_1, int node_2, int time_2, int cap) {

    c[node_1][time_1][node_2][time_2] = cap;
    G[node_1][time_1].pb(mp(node_2, time_2));
    G[node_2][time_2].pb(mp(node_1, time_1));
}

void read() {

    ifstream cin(inFile);
    cin >> n >> m;
    for(int i = 1; i <= n; ++i)
        cin >> A[i], total += A[i];

    for(int i = 1; i <= m; ++i)
        cin >> X[i] >> Y[i] >> L[i];

    for(int i = 1; i <= n; ++i)
        if( A[i] )
            makeEdge(0, 0, i, 0, A[i]);
}

bool BFS(int time) {

    while( !Q.empty() )
        Q.pop();
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= time; ++j)
            father[i][j] = null;

    father[0][0] = mp(0, 0);
    Q.push(source);

    while( !Q.empty() ) {

        node = Q.front(); Q.pop();
        if(node == sink)
            return 1;

        for(it = G[node.fi][node.se].begin(); it != G[node.fi][node.se].end(); ++it)
            if(father[it->fi][it->se] == null && c[node.fi][node.se][it->fi][it->se] > f[node.fi][node.se][it->fi][it->se]) {

                father[it->fi][it->se] = mp(node.fi, node.se);
                Q.push(mp(it->fi, it->se));
            }
    }
    return 0;
}

void increaseFlow() {

    //printf("^");
    int flowMin;

    //printf("%d %d", sink.fi, sink.se);

    for(it = G[sink.fi][sink.se].begin(); it != G[sink.fi][sink.se].end(); ++it) {

        node = *it;
       // printf("%d %d---", node.fi, node.se);
        if(father[node.fi][node.se] == null)
            continue;

        father[sink.fi][sink.se] = node;
        flowMin = 100;

        for(node = sink; node != source; node = father[node.fi][node.se]) {

            aux = father[node.fi][node.se];
            flowMin = min(flowMin, c[aux.fi][aux.se][node.fi][node.se] - f[aux.fi][aux.se][node.fi][node.se]);
        }

        if( !flowMin )
            continue;

        flow += flowMin;
        for(node = sink; node != source; node = father[node.fi][node.se]) {

            aux = father[node.fi][node.se];
            f[aux.fi][aux.se][node.fi][node.se] += flowMin;
            f[node.fi][node.se][aux.fi][aux.se] -= flowMin;
        }
    }
}

void write(int time) {

    ofstream cout(outFile);
    cout << time;
}

int main() {

    read();

    source = mp(0, 0); null = mp(-1, -1);
    for(int time = 0; time < Tmax; ++time) {

        //printf("*");
        sink = mp(1, time);
        while( BFS(time) )
            increaseFlow();
        if(flow == total) {
            write(time);
            return 0;
        }

        for(int i = 1; i <= n; ++i)
            makeEdge(i, time, i, time + 1, 100);
        for(int i = 1; i <= m; ++i) {

            makeEdge(X[i], time, Y[i], time + 1, L[i]);
            makeEdge(Y[i], time, X[i], time + 1, L[i]);
        }
    }

    return 0;
}
