/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

#define DIM 1010

using namespace std;
FILE *fin=freopen("bool.in","r",stdin);
FILE *fout=freopen("bool.out","w",stdout);

char S[DIM], *s, CH[DIM];
int val[30];
int n;

void checkSpace();
int giveValue();
int eval1();    // OR
int eval2();    // AND
int eval3();    //

void checkSpace() {
    while( *s == ' ' )
        ++s;
}

int giveValue(char c) {
    return c - 'A';
}

int eval1() {
    checkSpace();
    int ret = eval2();

    while( *s == 'O' && *(s + 1) == 'R' ) {
        s += 2;
        ret |= eval2();
    }
    checkSpace();
    return ret;
}

int eval2() {
    checkSpace();
    int ret = eval3();

    while( *s == 'A' && *(s + 1) == 'N' ) {
        s += 3;
        ret &= eval3();
    }
    checkSpace();

    return ret;
}

int eval3() {
    checkSpace();
    int ret = 0;

    if( *s == 'N' && *(s + 1) == 'O' ) {
        s += 3;
        ret = 1 - eval3();
    }

    else if( *s == '(' ) {
        ++s;
        ret = eval1();
        ++s;
    }

    else if( *s == 'T' && *(s + 1) == 'R' ) {
        s += 4;
        ret = 1;
    }

    else if( *s == 'F' && *(s + 1) == 'A' ) {
        s += 5;
        ret = 0;
    }

    else {
        ret = val[ giveValue(*s) ];
        ++s;
    }

    checkSpace();
    return ret;
}

int main() {
    gets(S);
    scanf("%d ", &n);
    gets(CH);

    for(int i = 0; i < n; ++i) {
        s = S;
        val[ giveValue(CH[i]) ] = 1 - val[ giveValue(CH[i])];
        printf("%d", eval1());
    }
    return 0;
}
