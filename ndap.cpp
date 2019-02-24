/**
  *  Worg
  */
#include <cstdio>
FILE *fin = freopen("ndap.in", "r", stdin);
FILE *fout = freopen("ndap.out", "w", stdout);

const int kMaxN = 15;
const int kMaxE = kMaxN * kMaxN + 1;
const int kModulo = 30103;

/*-------- Input data --------*/
int N, M;
bool adj[kMaxN][kMaxN];
/*-------- Solution data --------*/
int power[kMaxE];
int connected[1 << kMaxN], unconnected[1 << kMaxN], edgeNumber[1 << kMaxN];
/*-------- --------*/

void GeneratePowers() {
    power[0] = 1;
    for(int i = 1; i < kMaxE; i++) {
        power[i] = (power[i - 1] * 2) % kModulo;
    }
}

void ReadInput() {
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; i++) {
        int u, v; scanf("%d%d", &u, &v);
        adj[u][v] = adj[v][u] = true;
    }
}

void GetEdgeNumbers() {
    for(int i = 1; i < (1 << N); i++) {
        int bit[kMaxN], bits = 0;
        for(int j = 0; j < N; j++) {
            if(i & (1 << j)) {
                bit[bits++] = j;
            }
        }
        edgeNumber[i] = edgeNumber[i ^ (1 << bit[bits - 1])];
        for(int j = 0; j < bits - 1; j++) {
            if(adj[bit[bits - 1]][bit[j]]) {
                edgeNumber[i] ++;
            }
        }
    }
}

void Compute(int mask) {
    if(connected[mask] || unconnected[mask]) return;

    bool used[kMaxN];
    int bit[kMaxN], bits = 0;
    for(int i = 0; i < N; i++) {
        used[i] = (mask & (1 << i)) ? true : false;
        bit[bits] = i;
        bits += used[i];
    }
    for(int i = 0; i < (1 << (bits - 1)); i++) {
        int newMask = (1 << bit[bits - 1]);
        for(int j = 0, pow = 1; pow <= i; j++, pow <<= 1) {
            newMask ^= ((1 << bit[j]) * ((i & pow) > 0));
        }

        if(newMask != mask) {
            Compute(newMask);
            unconnected[mask] += connected[newMask] * power[edgeNumber[mask ^ newMask]];
            unconnected[mask] %= kModulo;
        }
    }
    connected[mask] = (power[edgeNumber[mask]] - unconnected[mask] + kModulo) % kModulo;
}

int main() {
    GeneratePowers();
    ReadInput();
    GetEdgeNumbers();
    Compute((1 << N) - 1);
    printf("%d\n", connected[(1 << N) - 1]);
    return 0;
}
