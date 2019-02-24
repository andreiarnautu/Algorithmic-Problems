/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("marvel.in", "r", stdin);
FILE *fout = freopen("marvel.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int root = 1;
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

/*------------------------*/
int N, M, K, P;
vector< int > G[MAX_N];
int enemy[MAX_N], story[MAX_N];
/*------------------------*/
int degree[MAX_N], dp[MAX_N];
/*------------------------*/

void readData() {
    cin.getBuffer(); cin.getInt(N); cin.getInt(M); cin.getInt(K); cin.getInt(P);

    for(int i = 1; i <= N; ++i) {
        cin.getInt(enemy[i]);
    }
    for(int i = 1; i <= P; ++i) {
        cin.getInt(story[i]);
    }
    for(int i = 1; i <= M; ++i) {
        int u, v; cin.getInt(u); cin.getInt(v);
        G[u].push_back(v); degree[v]++;
    }

    if(enemy[root] == story[root]) {
        dp[root] = 1;
    }
}

void DFS(int node = root) {
    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
        if(dp[node] == P) { /* if we already have the wanted storyline */
            dp[*it] = P;
        } else {
            if(enemy[*it] == story[dp[node] + 1]) {
                dp[*it] = max(dp[*it], dp[node] + 1);
            } else {
                dp[*it] = max(dp[*it], dp[node]);
            }
        }

        degree[*it]--;
        if(!degree[*it]) {
            DFS(*it);
        }
    }
}

void writeData() {
    int SOL = 0;
    for(int i = 1; i <= N; ++i) {
        if(dp[i] == P) {
            SOL++;
        }
    }
    printf("%d\n", SOL);
    for(int i = 1; i <= N; ++i) {
        if(dp[i] == P) {
            printf("%d ", i);
        }
    }
}

int main() {
    readData();
    DFS();
    writeData();
}
