/**
  *  Worg
  */
#include <cmath>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("monede1.in", "r", stdin);
FILE *fout = freopen("monede1.out", "w", stdout);

const int MAX_N = 200;
const int S = 150;
const int D = 151;
const int MAX_INF = 0x3fffffff;

/*-------------------------------*/
int coins[MAX_N][MAX_N];
int N, M, totalCoins, shelfCount, averageCoins;
/*-------------------------------*/ /** Graph stuff */
vector< pair< int,int > > underAverage, aboveAverage;
vector< int > graph[MAX_N];

int cap[MAX_N][MAX_N], cost[MAX_N][MAX_N];
/*-------------------------------*/ /** Min cost max flow */
queue< int > Q;
bool inQueue[MAX_N];
int dmin[MAX_N], before[MAX_N];
/*-------------------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            scanf("%d", &coins[i][j]);
            totalCoins += coins[i][j];
            shelfCount += (coins[i][j] > 0);
        }
    }
    averageCoins = totalCoins / shelfCount;
}

int getDist(pair< int,int > &a, pair< int,int > &b) {
    return abs(a.first - b.first) + abs(a.second - b.second) + 1;
}

void constructBipartiteGraph() {
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(coins[i][j] < averageCoins && coins[i][j] > 0) {
                underAverage.push_back(make_pair(i, j));
            } else if(coins[i][j] > averageCoins) {
                aboveAverage.push_back(make_pair(i, j));
            }
        }
    }
 //   printf("%d %d\n", (int)aboveAverage.size(), (int)underAverage.size());

    for(int i = 0; i < (int)aboveAverage.size(); i++) {
        graph[S].push_back(i); graph[i].push_back(S);
        cap[S][i] = coins[aboveAverage[i].first][aboveAverage[i].second] - averageCoins;
    }

    const int delay = (int)aboveAverage.size();

    for(int i = 0; i < (int)aboveAverage.size(); i++) {
        for(int j = 0; j < (int)underAverage.size(); j++) {
            graph[i].push_back(j + delay); graph[j + delay].push_back(i);
            cap[i][j + delay] = MAX_INF;
            cost[i][j + delay] = getDist(aboveAverage[i], underAverage[j]); cost[j + delay][i] = -cost[i][j + delay];
        }
    }
    for(int i = 0; i < (int)underAverage.size(); i++) {
        graph[i + delay].push_back(D); graph[D].push_back(i + delay);
        cap[i + delay][D] = averageCoins - coins[underAverage[i].first][underAverage[i].second];
    }
}

bool bellmanFord(int &totalCost) {
    for(int i = 0; i <= D; i++) {
        dmin[i] = MAX_INF;
    }
    dmin[S] = 0; Q.push(S);
    while(!Q.empty()) {
        int node = Q.front(); Q.pop(); inQueue[node] = false;
        for(vector< int >::iterator it = graph[node].begin(); it != graph[node].end(); it++) {
            if(cap[node][*it] && dmin[*it] > dmin[node] + cost[node][*it]) {
                dmin[*it] = dmin[node] + cost[node][*it];
                before[*it] = node;
                if(!inQueue[*it]) {Q.push(*it); inQueue[*it] = true;}
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
        for(int node = D; node != S; node = before[node]) {
            totalCost += flow * cost[before[node]][node];
            cap[before[node]][node] -= flow;
            cap[node][before[node]] += flow;
        }

        return true;
    }
}

int minCostMaxFlow() {
    int totalCost = 0;
    while(bellmanFord(totalCost));
    return totalCost;
}

int main() {
    readData();
    constructBipartiteGraph();
    printf("%d", minCostMaxFlow());
    return 0;
}
