/**
  *  Worg
  */
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;
FILE *fin = freopen("infinitepatternmatching.in", "r", stdin);
FILE *fout = freopen("infinitepatternmatching.out", "w", stdout);

const int MAX_N = 55;

char text[1 + MAX_N], aux[MAX_N];
int pi[1 + MAX_N];
int n;

string sir;

void makePrefix() {

    int k = 0;
    n = strlen(text + 1);

    for(int i = 2; i <= n; ++i) {

        while(k && text[i] != text[k + 1])
            k = pi[k];
        if(text[i] == text[k + 1])
            k++;
        pi[i] = k;
    }
}

void generate() {

    int nrMax = 0;
    for(int i = 1; i <= n; ++i)
        nrMax = nrMax * 2 + text[i] - '0';

    nrMax = (1 << 18) - 1;
    for(int i = 1; i <= nrMax; ++i) {

        int j = i, pos = 0;
        while(j) {

            aux[pos++] = (j & 1) + '0';
            j >>= 1;
        }
        for(j = pos - 1; j >= 0; --j)
            sir += aux[j];
    }
}

void match() {

    int len = sir.size(), k = 0;
    for(int i = 0; i < len; ++i) {

        while(k && sir[i] != text[k + 1])
            k = pi[k];
        if(sir[i] == text[k + 1])
            k++;
        if(k == n) {

            printf("%d\n", i + 1);
            return ;
        }
    }
    //while(3);
}

int main() {

    gets(text + 1);
    makePrefix();
    generate();
    match();
    return 0;
}
