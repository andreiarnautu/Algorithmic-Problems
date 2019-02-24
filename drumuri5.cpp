/**
  *  Worg
  */
#include <set>
#include <queue>
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("drumuri5.in", "r", stdin);
FILE *fout = freopen("drumuri5.out", "w", stdout);

const int MAX_N = 1 + 150000;
const int bufferDim = 100000;

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

        void getInt(int &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

struct Info {
    int index, lowlink;
    Info() {
        this->index = this->lowlink = 0;
    }
};
/*---------------------------*/
vector <int> G[MAX_N], G2[MAX_N], G3[MAX_N];
int N, M;
/*---------------------------*/
Info vec[MAX_N];
int currentIndex;
stack <int> Stack;
bool inStack[MAX_N];
/*---------------------------*/
vector <int> current;
vector < vector<int> > CTC;
int comp[MAX_N], degree[MAX_N];
set <int> Set;
/*---------------------------*/
int dist[MAX_N];
vector <int> marginal, nxt, goodCTC, SOL;
/*---------------------------*/
void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    for(int i = 1; i <= M; ++i) {
        int u, v; cin.getInt(u); cin.getInt(v);
        G[u].push_back(v);
    }
}

void strongConnect(int node) {
    vec[node].index = vec[node].lowlink = currentIndex;
    currentIndex++;

    Stack.push(node); inStack[node] = true;
    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(!vec[*it].index) {
            strongConnect(*it);
            vec[node].lowlink = min(vec[node].lowlink, vec[*it].lowlink);
        }
        else if(inStack[*it]) {
            vec[node].lowlink = min(vec[node].lowlink, vec[*it].index);
        }
    }

    if(vec[node].index == vec[node].lowlink) {
        current.clear();
        int now;
        do {
            now = Stack.top(); Stack.pop();
            inStack[now] = false;
            comp[now] = CTC.size() + 1;
            current.push_back(now);
        }while(now != node);
        CTC.push_back(current);
    }
}

void runTarjan() {
    currentIndex = 1;
    for(int i = 1; i <= N; ++i) {
        if(!vec[i].index) {
            strongConnect(i);
        }
    }
}

void getNewEdges() {
    for(int i = 0; i < (int)CTC.size(); ++i) {
        Set.clear();
        for(vector <int>::iterator it = CTC[i].begin(); it != CTC[i].end(); ++it) {
            for(vector <int>::iterator it2 = G[*it].begin(); it2 != G[*it].end(); ++it2) {
                if(Set.find(comp[*it2]) == Set.end()) {
                    if(comp[*it2] == i + 1) {
                        continue;
                    }
                    G2[i + 1].push_back(comp[*it2]);
                    degree[comp[*it2]]++;
                    G3[i + 1].push_back(comp[*it2]);
                    G3[comp[*it2]].push_back(i + 1);
                    Set.insert(comp[*it2]);
                }
            }
        }
    }
}
bool Comp(int x, int y) {
    return dist[x] < dist[y];
}

void Solve() {
    for(int i = 1; i <= (int)CTC.size(); ++i) {
        if(!degree[i]) {
            marginal.push_back(i);
        }
    }
    while((int)marginal.size() > 0) {
        int pos = 0;
        if((int)marginal.size() == 1) {
            goodCTC.push_back(marginal[0]);
        }
        else {
            pos = (int)marginal.size() - 1;
            sort(marginal.begin(), marginal.end(), Comp);
            int DMAX = dist[marginal[(int)marginal.size() - 1]];
            for(; pos >= 0 && dist[marginal[pos]] == DMAX; --pos);
            for(int i = 0; i <= pos; ++i) {
                nxt.push_back(marginal[i]);
            }
            pos++;
        }
        for(; pos < (int)marginal.size(); ++pos) {
            for(vector <int>::iterator it = G2[marginal[pos]].begin(); it != G2[marginal[pos]].end(); ++it) {
                degree[*it]--;
                if(!degree[*it]) {
                    nxt.push_back(*it);
                }
            }
        }
        marginal.clear();
        for(vector <int>::iterator it = nxt.begin(); it != nxt.end(); ++it) {
            marginal.push_back(*it);
        }
        nxt.clear();
    }
    for(vector <int>::iterator it = goodCTC.begin(); it != goodCTC.end(); ++it) {
        for(vector <int>::iterator it2 = CTC[*it - 1].begin(); it2 != CTC[*it - 1].end(); ++it2) {
            SOL.push_back(*it2);
        }
    }
    sort(SOL.begin(), SOL.end());
    printf("%d\n", (int)SOL.size());
    for(vector <int>::iterator it = SOL.begin(); it != SOL.end(); ++it) {
        printf("%d ", *it);
    }
}

void getDist(int node) {
    dist[node] = 1;
    for(vector <int>::iterator it = G2[node].begin(); it != G2[node].end(); ++it) {
        if(!dist[*it]) {
            getDist(*it);
        }
        dist[node] = max(dist[node], dist[*it] + 1);
    }
}

void getMinDist() {
    for(int i = 1; i <= (int)CTC.size(); ++i) {
        if(!dist[i]) {
            getDist(i);
        }
    }
}

int main() {
    readData();
    runTarjan();
    getNewEdges();
    getMinDist();
    Solve();
    return 0;
}
