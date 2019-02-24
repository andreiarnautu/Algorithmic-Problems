/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

const int MAX_LEN = 1 + 100000;

/*--------------------*/
char S[MAX_LEN];
int N, lenS;
/*--------------------*/
char word[MAX_LEN];
int lenW;
/*--------------------*/

void readData() {
    scanf("%d", &N);
    scanf("%s", S);
    lenS = strlen(S);
}

bool verif_1() {
    bool found = false;
    for(int i = 0; i < lenS; i++) {
        if(S[i] != word[i]) {
            if(!found) {
                found = true;
            } else {
                return false;
            }
        }
    }
    return true;
}

bool verif_2(char *A, char *B, int lenA, int lenB) {
    /* A has one more character than B */
    bool found = false;
    int i = 0, j = 0;
    while(i < lenA && j < lenB) {
        if(A[i] != B[j]) {
            if(!found) {
                found = true; i++;
            } else {
                return false;
            }
        } else {
            i++; j++;
        }
    }

    return true;
}

int main() {
    readData();

    int answer = 0;

    for(int i = 1; i <= N; ++i) {
        scanf("%s", word);
        lenW = strlen(word);
        if(lenW == lenS) {
            answer += verif_1();
        } else if(lenW == lenS - 1) {
            answer += verif_2(S, word, lenS, lenW);
        } else if(lenS == lenW - 1) {
            answer += verif_2(word, S, lenW, lenS);
        }

        //printf("%d\n", answer);
    }

    printf("%d", answer);
}
