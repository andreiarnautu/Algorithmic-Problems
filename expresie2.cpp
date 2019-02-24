/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
FILE *fin = freopen("expresie2.in", "r", stdin);
FILE *fout = freopen("expresie2.out", "w", stdout);

const int MAX_LEN = 1 + 100000;

char text[MAX_LEN];
int len;

void readData()  {
    scanf("%s", text);
    len = strlen(text);
}

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

int val(char c) {
    return c - '0';
}

void solveFirst() {
    int answer = 0;
    for(int i = 0; i < len; ++i) {
        if(isDigit(text[i])) {
            answer++;
            if(i + 1 < len && isDigit(text[i + 1])) {
                i++;
            }
        }
    }
    printf("%d\n", answer);
}

int getTerm();
int getExp();
int evalSimple();
int evalSmall();
int evalBig();

int pos;

int getTerm() {
    /* obtine valoarea unui numar */
    int answer = 0, sign = 1;
    if(text[pos] == '-') {
        sign = -1;
        pos++;
    }
    for(; pos < len && isDigit(text[pos]); ++pos) {
        answer = answer * 10 + val(text[pos]);
    }
    return answer * sign;
}

int evalSmall() {
    pos++; /* sarim peste paranteza */
    int answer = getExp(), s = answer;
    while(text[pos] == ',') {
        pos++; /* trecem peste virgula */
        int current = getExp();
        s = max(s, 0);
        s += current;
        answer = max(answer, s);
    }
    pos++; /* sarim peste paranteza */
    return answer;
}

int evalBig() {

    vector <int> vec;
    pos++; /* sarim peste paranteza */
    vec.push_back(getExp());

    while(text[pos] == ',') {
        pos++; /* trecem peste virgula */
        vec.push_back(getExp());
    }
    pos++; /* sarim peste paranteza */

    sort(vec.begin(), vec.end());
    int k = vec.size();
    return vec[(k + 1) / 2 - 1];
}

int getExp() {
    /* expresia urmatoare poate fi un numar, o secventa intre paranteze rotunde sau una intre paranteze patrate */

    if(text[pos] == '-' || isDigit(text[pos])) {
        return getTerm();
    }
    else if(text[pos] == '(') {
        return evalSmall();
    }
    else {
        return evalBig();
    }
}

int evalSimple() {
    int answer = getExp();
    while(text[pos] == ',') {
        pos++; /* trecem peste virgula */
        int current = getExp();
        answer += current;
    }
    return answer;
}

int main() {
    readData();
    solveFirst();
    printf("%d", evalSimple());
    return 0;
}
