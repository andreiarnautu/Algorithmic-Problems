/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("bal2.in", "r", stdin);
FILE *fout = freopen("bal2.out", "w", stdout);

const int MAX_N = 600;
const int S = 550;
const int D = 551;
const int MAX_INF = 0x3fffffff;

/*------------------------*/
int N, K;
/*------------------------*/ /** Graph stuff */
int cap[MAX_N][MAX_N];
double cost[MAX_N][MAX_N];
vector< int > graph[MAX_N];
/*------------------------*/ /** Min cost max flow */
queue< int > Q;
double pmax[MAX_N];
bool inQueue[MAX_N];
int before[MAX_N];

int totalFlow;
/*------------------------*/

void readData() {
    scanf("%d%d", &N, &K);
}

void constructGraph() {
    for(int i = 1; i <= N; i++) {
        graph[S].push_back(i); graph[i].push_back(S);
        cap[S][i] = K; cost[S][i] = cost[i][S] = 1;
    }
    for(int i = 1; i <= N; i++) {
        for(int j = N + 1; j <= 2 * N; j++) {
            int prob; scanf("%d", &prob);
            if(prob == 0) {continue;}
            graph[i].push_back(j); graph[j].push_back(i);
            cap[i][j] = 1;
            cost[i][j] = (double)prob / 100;
            cost[j][i] = 100 / (double)prob;
        }
    }
    for(int j = N + 1; j <= 2 * N; j++) {
        graph[j].push_back(D); graph[D].push_back(j);
        cap[j][D] = 1;
        cost[j][D] = cost[D][j] = 1;
    }
}

bool bellmanFord(double &prob) {
    for(int i = 1; i <= 2 * N; i++) {
        pmax[i] = 0;
    }
    pmax[D] = 0; pmax[S] = 1; Q.push(S);
    while(!Q.empty()) {
        int node = Q.front(); Q.pop(); inQueue[node] = false;
        if(node == D) {continue;}
        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(cap[node][*it] && pmax[*it] < pmax[node] * cost[node][*it]) {
                pmax[*it] = pmax[node] * cost[node][*it];
                before[*it] = node;
                if(!inQueue[*it]) {Q.push(*it); inQueue[*it] = true;}
            }
        }
    }

    if(pmax[D] == 0) {
        return false;
    } else {
        int flow = MAX_INF;
        for(int node = D; node != S; node = before[node]) {
            flow = min(flow, cap[before[node]][node]);
        }
        for(int node = D; node != S; node = before[node]) {
            cap[before[node]][node] -= flow;
            cap[node][before[node]] += flow;
        }
        for(int i = 1; i <= flow; i++) {
            prob *= pmax[D];
        }
        totalFlow += flow;

        return true;
    }
}

double minCostMaxFlow() {
    double prob = 1.0;
    while(bellmanFord(prob));
    if(totalFlow < N) {
        return 0;
    } else {
        return prob * 100;
    }
}

int main() {
    readData();
    constructGraph();
    printf("%.6f", minCostMaxFlow());
}
