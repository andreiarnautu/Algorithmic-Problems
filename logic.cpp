/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

#define DIM 300

using namespace std;
FILE *fin=freopen("logic.in","r",stdin);
FILE *fout=freopen("logic.out","w",stdout);

int n, ch[15], len1, len2, nr;
char A[DIM], B[DIM], *s;
bool v[DIM], w[DIM], val[DIM];

int isLetter(char c);
int value(char c);
bool check(int x);
bool eval();    // operatorul |
bool eval2();   // operatorul ^
bool eval3();   // operatorul &
bool term();    // termen

int isLetter(char c) {
    return ( 'a' <= c && c <= 'z' );
}

int value(char c) {
    return c - 'a';
}

bool eval() {
    bool ret = eval2();

    while( *s == '|' ) {
        ++s;
        ret |= eval2();
    }

    return ret;
}

bool eval2() {
    bool ret = eval3();

    while( *s == '^' ) {
        ++s;
        ret ^= eval3();
    }

    return ret;
}

bool eval3() {
    bool ret = term();

    while( *s == '&' ) {
        ++s;
        ret &= term();
    }

    return ret;
}

bool term() {
    bool ret;

    if( *s == '~' )
        ++s, ret = 1 - term();

    else if( *s == '(' )
        ++s, ret = eval(), s++;

    else
        ret = val[ value(*s) ], ++s;

    return ret;
}

bool check(int x) {
    memset(val, 0, sizeof(val));
    int i;
    for(i = 0; i <= nr; ++i)
        if( x & (1 << i) )
            val[ ch[i] ] = 1;

    bool q1, q2;

    s = A; q1 = eval();
    s = B; q2 = eval();

    return (q1 == q2);
}

int main() {
    int i, j;
    scanf("%d ", &n);

    for(i = 1; i <= n; ++i) {
        memset(v, 0, sizeof(v));
        memset(w, 0, sizeof(w));

        gets( A ); len1 = strlen( A );
        gets( B ); len2 = strlen( B );

        for(j = 0; j < len1; ++j)
            if( isLetter( A[j] ) )
                v[ value( A[j] ) ] = 1;

        for(j = 0; j < len2; ++j)
            if( isLetter( B[j] ) )
                w[ value( B[j] ) ] = 1;

        for(j = 0; j <= 26; ++j)
            if( v[j] != w[j] )
                break;
        if( j != 27 ) {
            printf("diferite\n");
            continue;
        }


        nr = -1;
        for(j = 0; j <= 26; ++j)
            if( v[j] )
                ch[ ++nr ] = j;

        for(j = 0; j < (1 << (nr + 1)); ++j)
            if( !check(j) ) {
                printf("diferite\n");
                break;
            }
        if( j == (1 << (nr + 1)) )
            printf("egale\n");
    }

    return 0;
}
