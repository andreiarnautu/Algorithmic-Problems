/**
  *  Worg
  */
#include <queue>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("hektor.in", "r", stdin);
FILE *fout = freopen("hektor.out", "w", stdout);

const int MAX_N = 1 + 100000;
/*----------------------------------*/
int N, M, A, B;
int cost[MAX_N];
vector <int> G[MAX_N], Gt[MAX_N];
/*----------------------------------*/
queue <int> q;
int degree[MAX_N];
bool marked[MAX_N];
/*----------------------------------*/
vector <double> partial[MAX_N];
double SOL[MAX_N];
/*----------------------------------*/


void readData() {
    scanf("%d%d%d%d", &N, &M, &A, &B);
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &cost[i]);
    }
    for(int i = 1; i <= M; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v); Gt[v].push_back(u);
    }
}

void getDegree() {
    q.push(B);
    marked[B] = true;
    while(!q.empty()) {
        int node = q.front(); q.pop();
        for(vector <int>::iterator it = Gt[node].begin(); it != Gt[node].end(); ++it) {
            degree[*it]++;
            if(!marked[*it]) {
                marked[*it] = true;
                q.push(*it);
            }
        }
    }
}

void solveProblem() {
    q.push(B);
    SOL[B] = (double)cost[B];
    while(!q.empty()) {
        int node = q.front(); q.pop();
        for(vector <int>::iterator it = Gt[node].begin(); it != Gt[node].end(); ++it) {
            degree[*it]--;
            partial[*it].push_back(SOL[node]);
            if(!degree[*it]) {
                SOL[*it] = (double)cost[*it] * (double)partial[*it].size();
                for(vector <double>::iterator it2 = partial[*it].begin(); it2 != partial[*it].end(); ++it2) {
                    SOL[*it] += *it2;
                }
                SOL[*it] /= (double)partial[*it].size();
                partial[*it].clear();
                q.push(*it);
            }
        }
    }
    printf("%.10f", SOL[A]);
}

int main() {
    readData();
    getDegree();
    solveProblem();
    return 0;
}
