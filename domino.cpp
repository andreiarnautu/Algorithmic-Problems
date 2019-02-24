/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <utility>

using namespace std;
FILE *fin = freopen("domino.in", "r", stdin);
FILE *fout = freopen("domino.out", "w", stdout);

const int MAX_N = 1 + 50000;
const int MAX_VAL = 10;

/*----------------------------------------*/
vector< pair< int,int > > graph[MAX_VAL];
vector< pair< int,int > > vec[MAX_VAL][MAX_VAL];
int degree[MAX_VAL];
int N;
/*----------------------------------------*/ /** Eulerian path */
int remainingEdges;
bool checked[MAX_N];
stack< int > Stack;
vector< int > sol;
/*----------------------------------------*/


void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        int u, v; scanf("%d%d", &u, &v);
        degree[u]++; degree[v]++;
        graph[u].push_back(make_pair(v, i));
        graph[v].push_back(make_pair(u, i));
        vec[u][v].push_back(make_pair(i, 0)); vec[v][u].push_back(make_pair(i, 1));
    }
}

void outputImpossible() {
    printf("0\n"); exit(0);
}

void outputPossible() {
    for(int i = 1; i <= N; i++) {
        checked[i] = false;
    }


    printf("1\n");
    for(int i = 0; i < (int)sol.size() - 1; i++) {
        int u = sol[i], v = sol[i + 1];
        while(checked[vec[u][v].back().first]) {
            vec[u][v].pop_back();
        }
        printf("%d %d\n", vec[u][v].back().first, vec[u][v].back().second);
        checked[vec[u][v].back().first] = true;
    }
}

void checkIfValid() {
    int countOddDegrees = 0;
    for(int i = 0; i < MAX_VAL; i++) {
        countOddDegrees += (degree[i] % 2 == 1);
    }

    if(countOddDegrees == 1 || countOddDegrees > 2) {
        outputImpossible();
    } else {
        if(countOddDegrees == 2) {
            for(int i = 0; i < MAX_VAL; i++) {
                if(degree[i] % 2 == 1) {
                    Stack.push(i); break;
                }
            }
        } else { /* countOddDegrees == 0 */
            for(int i = 0; i < MAX_VAL; i++) {
                if(degree[i] > 0) {
                    Stack.push(i); break;
                }
            }
        }
    }
}

int deleteNext(const int &node) {
    while(!graph[node].empty() && checked[graph[node].back().second]) {
        graph[node].pop_back();
    }
    /* if we reach this state, it's 100% sure that there is at least 1 more edge left in the array */

    checked[graph[node].back().second] = true;
    int nextNode = graph[node].back().first;
    graph[node].pop_back(); remainingEdges--;
    degree[node]--; degree[nextNode]--;

    return nextNode;
}

void getEulerianPath() {
    checkIfValid();
    remainingEdges = N;
    while(!Stack.empty()) {
        int node = Stack.top();
        if(degree[node]) { /* if we can continue */
            Stack.push(deleteNext(node));
        } else {
            sol.push_back(node);
            Stack.pop();
        }
    }

    if(remainingEdges > 0) {
        outputImpossible();
    } else {
        outputPossible();
    }
}

int main() {
    readData();
    getEulerianPath();
    return 0;
}
