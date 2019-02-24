/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

using namespace std;

FILE *fin = freopen("numere7.in", "r", stdin);
FILE *fout = freopen("numere7.out", "w", stdout);

const int MAX_LEN = 1 + 20;

/*-----------------*/
long long N;
char str[MAX_LEN];
/*-----------------*/
int lg, digitCount[10];
int crtCount[10];
long long fact[MAX_LEN];

int answer[MAX_LEN];
/*-----------------*/


void readInput() {
    scanf("%lld", &N);
    scanf("%s", str);

    fact[0] = 1;
    for(int i = 1; i <= 20; i++) {
        fact[i] = fact[i - 1] * i;
    }
}

void getDigits() {
    lg = strlen(str);
    for(int i = 0; i < lg; i++) {
        digitCount[str[i] - '0']++;
    }
    for(int i = 1; i <= 9; i++) {
        crtCount[i] = digitCount[i];
    }
}

void writeOutput() {
    for(int i = 1; i <= lg; i++) {
        printf("%d", answer[i]);
    }
}

long long getPerm(int digits, int crtDigit) {
    crtCount[crtDigit]--;

    long long answer = fact[digits];
    for(int i = 1; i <= 9; i++) {
        answer /= fact[crtCount[i]];
    }

    crtCount[crtDigit]++;
    return answer;
}

void findDigit(int crtPos) {
    if(crtPos == lg) { /* found the answer */
        for(int i = 1; i <= 9; i++) {
            if(crtCount[i]) {
                answer[crtPos] = i;
                writeOutput();
            }
        }
    } else { /* fix the current digit */
        for(int i = 1; i <= 9; i++) {
            if(crtCount[i]) {
                long long permCount = 0;
                permCount = getPerm(lg - crtPos, i);
                if(permCount >= N) {
                    crtCount[i]--;
                    answer[crtPos] = i;
                    findDigit(crtPos + 1);
                    return;
                } else {
                    N -= permCount;
                }
            }
        }
    }
}

int main() {
    readInput();
    getDigits();
    findDigit(1);
    return 0;
}
