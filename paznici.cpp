/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("paznici.in", "r", stdin);
FILE *fout = freopen("paznici.out", "w", stdout);

const int MAX_N = 1 + 26;

/*-----------------------*/
char S[MAX_N];
int N, M;
vector< int > G[MAX_N];
/*-----------------------*/
bool checked[MAX_N], suppLeft[MAX_N], suppRight[MAX_N];
int left[MAX_N], right[MAX_N];
/*-----------------------*/

void readData() {
    scanf("%d%d ", &N, &M);
    for(int i = 1; i <= N; i++) {
        scanf("%s", S);
        for(int j = 1; j <= M; j++) {
            if(S[j - 1] == '1') {
                G[i].push_back(j);
            }
        }
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
            suppLeft[node] = true;
            left[node] = *it;
            right[*it] = node;
            return true;
        }
    }

    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
        if(pairUp(right[*it])) {
            suppLeft[node] = true;
            left[node] = *it;
            right[*it] = node;
            return true;
        }
    }

    return false;
}

void Support(int node) {
    for(vector< int >::iterator it = G[node].begin(); it != G[node].end(); it++) {
        if(!suppRight[*it]) {
            suppRight[*it] = true;
            suppLeft[right[*it]] = false;
            Support(right[*it]);
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
    for(int i = 0; i <= 25; i++) {
        if(suppLeft[i + 1]) {
            printf("%c", 'A' + i);
        }
    }
    for(int i = 0; i <= 25; i++) {
        if(suppRight[i + 1]) {
            printf("%c", 'a' + i);
        }
    }
}

int main() {
    readData();
    hopcroftKarp();
    writeData();
}
