/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("entanglement.in", "r", stdin);
FILE *fout = freopen("entanglement.out", "w", stdout);

const int MAX_N = 1 + 300;
const int MOD = 1000000007;

/*-------- Input data --------*/
int T, N, M, K;
int mat[MAX_N][MAX_N];
/*-------- --------*/

void readInput() {
    scanf("%d%d%d%d", &T, &N, &M, &K);
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

int main() {
    readInput();

    return 0;
}
