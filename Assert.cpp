/**
  *  Worg
  *  This is just used for asserting stuff...
  */
#include <cstdio>
#include <cassert>

using namespace std;
FILE *fin = freopen("strigat.in", "r", stdin);
FILE *fout = freopen("strigat.out", "w", stdout);

int main() {
    int N, M; scanf("%d%d ", &N, &M);

    for(int i = 1; i <= M; i++) {
        char word[1000]; gets(word); printf("%s\n", word);
        int useless; scanf("%d ", &useless);

        char *p = word;
        while(*p != '\0'){
            assert('a' <= *p && *p <= 'z');
            p ++;
        }

    }
}
