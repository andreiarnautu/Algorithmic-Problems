/**
  *  Worg
  *  Solutie de 60p, acopera doar primele 3 cazuri
  */
#include <cstdio>
#include <cstring>

using namespace std;
FILE *fin = freopen("evaluare1.in", "r", stdin);
FILE *fout = freopen("evaluare1.out", "w", stdout);

const int MAX_LEN = 1 + 100 + 1;

/*-------- --------*/
char text[MAX_LEN];
int length;
/*-------- --------*/
char *cursor;
/*-------- --------*/

long long eval();
long long number();
long long factor();

long long eval() {
    int value = number();
    while(*cursor == '+') {
        ++cursor;
        value += number();
    }
    return value;
}

long long number() {
    long long value = factor();

    while(*cursor == '/') {
        ++cursor;
        value /= factor();
    }

    return value;
}

long long factor() {
    long long value = 0;
    if(*cursor == '(') {
        ++cursor;
        value = eval();
        ++cursor;
    } else {
        while('0' <= *cursor && *cursor <= '9') {
            value = value * 10 + *cursor - '0';
            ++cursor;
        }
    }

    return value;
}

int main() {
    scanf("%s", text + 1); length = strlen(text + 1);
    cursor = text + 1;
    printf("%lld\n", eval());

    return 0;
}
