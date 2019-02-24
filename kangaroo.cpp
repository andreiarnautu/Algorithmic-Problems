/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("kangaroo.in", "r", stdin);
FILE *fout = freopen("kangaroo.out", "w", stdout);

const int MAX_N = 1 + 2000;
const int MOD = 1000000000 + 7;

/*-----------------------*/
int N, cs, cf;
/*-----------------------*/
int SOL = 0;
bool marked[MAX_N];
/*-----------------------*/

void readData() {
    scanf("%d%d%d", &N, &cs, &cf);
}

void Back(int step, int pos, bool where) {
    marked[pos] = true;
    if(step == N && pos == cf) {
        SOL++; marked[pos] = false; return;
    }

    if(where == 0) {
        for(int i = pos - 1; i >= 1; --i) {
            if(!marked[i]) {
                Back(step + 1, i, 1);
            }
        }
    } else {
        for(int i = pos + 1; i <= N; i++) {
            if(!marked[i]) {
                Back(step + 1, i, 0);
            }
        }
    }

    marked[pos] = false;
}

int main() {
    readData();
    Back(1, cs, 0);
    Back(1, cs, 1);
    printf("%d", SOL);
    return 0;
}
