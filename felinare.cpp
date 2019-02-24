/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("felinare.in", "r", stdin);
FILE *fout = freopen("felinare.out", "w", stdout);

const int MAX_N = 8500;

/*-----------------------*/
vector< int > G[MAX_N];
int N, M;
/*-----------------------*/
bool checked[MAX_N];
bool suppLeft[MAX_N], suppRight[MAX_N];
int left[MAX_N], right[MAX_N];

int cuplajValue = 0;
/*-----------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v);
    }
}

bool pairUp(int node) {
    if(checked[node]) {
        return false;
    } else {
        checked[node] = true;
    }

    for(vector< int >::iterator nxt = G[node].begin(); nxt != G[node].end(); nxt++) {
        if(!right[*nxt]) {
            suppLeft[node] = true;

            left[node] = *nxt;
            right[*nxt] = node;
            cuplajValue++;
          //  printf("%d %d\n", node, *nxt);
            return true;
        }
    }

    for(vector< int >::iterator nxt = G[node].begin(); nxt != G[node].end(); nxt++) {
        if(pairUp(right[*nxt])) {
            suppLeft[node] = true;

            left[node] = *nxt;
            right[*nxt] = node;
            return true;
        }
    }

    return false;
}

void Support(int node) {
    for(vector< int >::iterator nxt = G[node].begin(); nxt != G[node].end(); nxt++) {
        if(!suppRight[*nxt]) {
            suppRight[*nxt] = true;
            suppLeft[right[*nxt]] = false;
            Support(right[*nxt]);
        }
    }
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

    for(int i = 1; i <= N; i++) {
        if(!suppLeft[i]) {
            Support(i);
        }
    }
}

void writeData() {
    printf("%d\n", 2 * N - cuplajValue);
    for(int i = 1; i <= N; i++) {
        int val = 3;
        if(suppLeft[i]) {
            val--;
        }
        if(suppRight[i]) {
            val -= 2;
        }
        printf("%d\n", val);
    }
}

int main() {
    readData();
    hopcroftKarp();
    writeData();
}
