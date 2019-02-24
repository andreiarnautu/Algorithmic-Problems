/**
  *  Worg
  */
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
FILE *fin = freopen("adapost.in", "r", stdin);
FILE *fout = freopen("adapost.out", "w", stdout);

const int MAX_N = 1 + 400 + 10;
const double MAX_DIST = 2000;
const double MIN_DIST = 1e-7;
const int MAX_INF = 0x3fffffff;

/*---------------------------------*/
pair< double,double > coord[MAX_N * 2];
double dist[MAX_N * 2][MAX_N * 2];
int N;
/*---------------------------------*/ /** Graph stuff */
int cap[MAX_N * 2][MAX_N * 2];
double cost[MAX_N * 2][MAX_N * 2];

vector< int > graph[2 * MAX_N];

/*---------------------------------*/ /** Cuplaj */
bool checked[2 * MAX_N];
int left[2 * MAX_N], right[2 * MAX_N];

int cuplaj;

/*---------------------------------*/ /** Min cost max flow */
bool inQueue[MAX_N * 2];
queue< int > Q;
int before[MAX_N * 2];
double dmin[MAX_N * 2];

int totalFlow;
double totalCost;
/*---------------------------------*/



double getDist(int u, int v) {
    return sqrt((coord[u].first - coord[v].first) * (coord[u].first - coord[v].first) +
                (coord[u].second - coord[v].second) * (coord[u].second - coord[v].second));
}

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= 2 * N; i++) {
        scanf("%lf%lf", &coord[i].first, &coord[i].second);
    }

    for(int i = 1; i <= N; i++) {
        for(int j = N + 1; j <= 2 * N; j++) {
            double d = getDist(i, j);
            dist[i][j] = d;
        }
    }
}

void buildGraph(double distLimit) {
    const int S = 2 * N + 1;
    const int D = 2 * N + 2;

    for(int i = 1; i <= N; i++) {
        graph[S].push_back(i); graph[i].push_back(S);
        cap[S][i] = 1; cap[i][S] = 0;
    }
    for(int i = 1; i <= N; i++) {
        for(int j = N + 1; j <= 2 * N; j++) {
            if(dist[i][j] <= distLimit) {
                graph[i].push_back(j); graph[j].push_back(i);
                cap[i][j] = 1; cap[j][i] = 0; cost[i][j] = dist[i][j]; cost[j][i] = -dist[i][j];
            }
        }
    }
    for(int i = N + 1; i <= 2 * N; i++) {
        graph[i].push_back(D); graph[D].push_back(i);
        cap[i][D] = 1; cap[D][i] = 0;
    }
}

bool bellmanFord() {
    const int S = 2 * N + 1;
    const int D = 2 * N + 2;

    for(int i = 1; i <= D; i++) {
        dmin[i] = MAX_INF;
    }
    dmin[S] = 0; Q.push(S);

    while(!Q.empty()) {
        int node = Q.front(); Q.pop(); inQueue[node] = false;
        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(cap[node][*it] && dmin[*it] > dmin[node] + cost[node][*it]) {
                dmin[*it] = dmin[node] + cost[node][*it];
                before[*it] = node;

                if(!inQueue[*it]) {
                    Q.push(*it); inQueue[*it] = true;
                }
            }
        }
    }

    if(dmin[D] == MAX_INF) {
        return false;
    } else {
        int flow = MAX_INF;
        for(int node = D; node != S; node = before[node]) {
            flow = min(flow, cap[before[node]][node]);
        }
        totalFlow += flow;

        for(int node = D; node != S; node = before[node]) {
            cap[before[node]][node] -= flow;
            cap[node][before[node]] += flow;
            totalCost += flow * cost[before[node]][node];
        }

        return true;
    }
}

void resetGraph() {
    for(int i = 1; i <= N; i++) {
        graph[i].clear();
    }
    for(int i = 1; i <= N; i++) {
        checked[i] = 0;
        left[i] = 0;
        right[i] = 0;
    }
}

bool pairUp(int node) {

    if(checked[node])
        return 0;
    checked[node] = true;

    for(int nxt : graph[node])
        if(!right[nxt]) {

            left[node] = nxt;
            right[nxt] = node;
            cuplaj++;
            return 1;
        }
    for(int nxt : graph[node])
        if(pairUp(right[nxt])) {

            left[node] = nxt;
            right[nxt] = node;
            return 1;
        }

    return 0;
}

bool goodFlow(double distLimit, bool reset = true) {
    if(reset) { /* Facem cuplaj */
        cuplaj = 0;

        for(int i = 1; i <= N; i++) {
            for(int j = N + 1; j <= 2 * N; j++) {
                if(dist[i][j] <= distLimit) {
                    graph[i].push_back(j - N);
                }
            }
        }

        bool ok;
        do {
            ok = false;
            for(int i = 1; i <= N; i++) {
                checked[i] = false;
            }
            for(int i = 1; i <= N; i++) {
                if(!left[i]) {
                    ok |= pairUp(i);
                }
            }
        }while(ok);

        resetGraph();
        return (cuplaj == N);

    } else { /* Facem flux maxim de cost minim */
        buildGraph(distLimit);
        totalFlow = 0; totalCost = 0;
        while(bellmanFord());

        return true;
    }
}

void binarySearch() {
    double dmax = 0, dtotal = 0;


    for(double step = MAX_DIST; step > 1e-7; step *= 0.5) {
        if(dmax + step <= MAX_DIST && !goodFlow(dmax + step)) {
            dmax += step;
        }
    }
    dmax += 1e-6;

    printf("%.6f ", dmax);
    goodFlow(dmax, false);
    for(int i = 1; i <= N; i++) {
        for(vector< int >::iterator it = graph[i].begin(); it != graph[i].end(); it++) {
            if(*it != 1 && cap[i][*it] == 0) {
                dtotal += dist[i][*it]; break;
            }
        }
    }
    printf("%.6f\n", dtotal);

}

int main() {
    readData();
    binarySearch();
    return 0;
}
