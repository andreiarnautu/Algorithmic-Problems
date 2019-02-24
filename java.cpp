/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("java.in", "r", stdin);
FILE *fout = freopen("java.out", "w", stdout);

const int bufferDim = 1 + 100000;
const int MAX_N = 1 + 10000;

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

/*---------------------------------*/
int N, M, E;
vector< int > G[MAX_N];
/*---------------------------------*/
bool checked[MAX_N];
int left[MAX_N], right[MAX_N];

int cuplaj;
/*---------------------------------*/

void readData() {
    cin.getInt(N); cin.getInt(M); cin.getInt(E);
    for(int i = 1; i <= E; i++) {
        int e, g; cin.getInt(e); cin.getInt(g);
        G[e].push_back(g);
    }
}

void Initialize() {
    cuplaj = 0;
    for(int i = 1; i <= N; i++) {
        left[i] = false;
    }
    for(int i = 1; i <= M; i++) {
        right[i] = false;
    }
}

bool pairUp(int node) {
    if(checked[node]) {
        return false;
    } else {
        checked[node] = true;
    }

    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
        if(!right[*it]) {
            left[node] = *it;
            right[*it] = node;

            cuplaj++;
            return true;
        }
    }

    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
        if(pairUp(right[*it])) {
            left[node] = *it;
            right[*it] = node;
            return true;
        }
    }

    return false;
}

void hopcroftKarp() {
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
}

void Finish() {
    printf("%d\n", cuplaj);
    for(int i = 1; i <= N; i++) {
        G[i].clear();
    }
}

int main() {
    int T; cin.getBuffer();
    for(cin.getInt(T); T; T--) {
        readData();
        Initialize();
        hopcroftKarp();
        Finish();
    }
}
