/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("main.in", "r", stdin);
FILE *fout = freopen("main.out", "w", stdout);

const int MAX_SIZE = 1 + 1000000;

/*-------------------*/
vector< int > mat[MAX_SIZE];
int N, M;
/*-------------------*/

void readData() {
    scanf("%d%d", &N, &M);
    for(int i = 1; i <= N; ++i) {
        mat[i].reserve(M + 1);
    }
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= M; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

bool comp(const vector< int > &a, const vector< int > &b) {
    for(int i = 1; i <= M; ++i) {
        if()
    }
}

int main() {
    readData();
}
