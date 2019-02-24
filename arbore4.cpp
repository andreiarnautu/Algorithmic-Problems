/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("arbore4.in", "r", stdin);
FILE *fout = freopen("arbore4.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int MOD = 666013;
/*------------------------*/
vector <int> G[MAX_N];
int N;
int fact[MAX_N];
/*------------------------*/
bool checked[MAX_N];
int subTree[MAX_N], SOL[MAX_N];
/*------------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 2; i <= N; ++i) {
        int u, v; scanf("%d%d", &u, &v);
        G[u].push_back(v); G[v].push_back(u);
    }

    fact[0] = 1;
    for(int i = 1; i <= N; ++i) {
        fact[i] = (1LL * fact[i - 1] * i) % MOD;
    }
}

int pow(int base, int exp) {
    int answer = 1, aux = base;
    for(int i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = (1LL * answer * aux) % MOD;
        }
        aux = (1LL * aux * aux) % MOD;
    }
    return answer;
}

int C(int p, int q) {
    int aux = 1LL * (1LL * fact[p - q] * fact[q]) % MOD;
    int answer = (1LL * fact[p] * pow(aux, MOD - 2)) % MOD;
    return answer;
}

void DFS(int node = 1) {
    checked[node] = true;
    subTree[node] = SOL[node] = 1;

    int father = 0;
    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(!checked[*it]) {
            DFS(*it);
            subTree[node] += subTree[*it];
        } else {
            father = *it;
        }
    }

    int count = subTree[node] - 1;
    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        if(*it != father) {
            SOL[node] = (1LL * SOL[node] * SOL[*it]) % MOD;
            SOL[node] = (1LL * SOL[node] * C(count, subTree[*it])) % MOD;
            count -= subTree[*it];
        }
    }
}

int main() {
    readData();
    DFS();
    printf("%d", SOL[1]);
    return 0;
}
