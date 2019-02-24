/**
  * Worg
  */
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
FILE *fin = freopen("match.in", "r", stdin);
FILE *fout = freopen("match.out", "w", stdout);

const int MAX_N = 1 + 1000000;
const int N_PARTIAL = 1 + 2000;

/*------------*/
char S[MAX_N];
int N;
/*------------*/
bool valid[N_PARTIAL][N_PARTIAL];
bool checked[N_PARTIAL][N_PARTIAL];
bool possible[MAX_N][MAX_N];
bool SOL[MAX_N];
/*------------*/


void noChance() {
    printf("-1\n"); exit(0);
}

void readData() {
    scanf("%s", S + 1);
    N = strlen(S + 1);
}

void validSequence(int left, int right) {
    if(checked[left][right]) {
        return;
    } else {
        checked[left][right] = true;
        valid[left][right] = false;
    }

    if((right - left + 1) % 2 == 1) {
        printf("wtf" ); return;
    }

    if(left == right - 1) {
        if(S[left] == S[right]) {
            valid[left][right] = true;
        }
    } else {
        for(int i = right; i >= left + 1; i -= 2) {
            if(S[left] == S[i]) {
                if(i != left + 1) {
                    validSequence(left + 1, i - 1);
                } else {
                    valid[left][left + 1] = true;
                }
                if(valid[left + 1][i - 1] || i == left + 1) {
                    /* we check the other part */
                    if(i != right) {
                        validSequence(i + 1, right);
                        if(valid[i + 1][right]) {
                            valid[left][right] = true;
                        }
                    }
                }
            }
        }
    }

    if(valid[left][right]) {
        possible[left] = true;
    }
}

void getSequence(int left, int right) {

}

void writeData() {
    for(int i = 1; i <= N; i++) {
        if(SOL[i] == true) {
            printf("(");
        } else {
            printf(")");
        }
    }
}

int main() {
    readData();
    if(N % 2 == 1) {noChance();} /** !!! */
    validSequence(1, N);
    if(!valid[1][N]) {noChance();} /** !!! */
    getSequence(1, N);
    writeData();
    return 0;
}
