/**
  *  Worg
  */
#include <stack>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("ctc.in", "r", stdin);
FILE *fout = freopen("ctc.out", "w", stdout);

const int MAX_N = 1 + 100000;
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

/*-------------------------*/
vector <int> G[MAX_N];
int N, M;
/*-------------------------*/
Info vec[MAX_N];
int currentIndex;
stack <int> Stack;
bool inStack[MAX_N];

vector <int> current;
vector < vector<int> > SOL;
/*-------------------------*/


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

    if(vec[node].lowlink == vec[node].index) {
        current.clear();
        int now;
        do {
            now = Stack.top(); Stack.pop();
            inStack[now] = false;
            current.push_back(now);
        }while(now != node);
        SOL.push_back(current);
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

void writeData() {
    printf("%d\n", (int)SOL.size());
    for(int i = 0; i < (int)SOL.size(); ++i) {
        for(vector <int>::iterator it = SOL[i].begin(); it != SOL[i].end(); ++it) {
            printf("%d ", *it);
        }
        printf("\n");
    }
}

int main() {
    readData();
    runTarjan();
    writeData();
    return 0;
}
