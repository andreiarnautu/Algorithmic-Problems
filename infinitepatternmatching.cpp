/**
  *  Worg
  */
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
FILE *fin = freopen("infinitepatternmatching.in", "r", stdin);
FILE *fout = freopen("infinitepatternmatching.out", "w", stdout);

const int MAX_N = 55;

int n;
char text[MAX_N];
bool B[MAX_N];

void readData() {

    gets(text);
    n = (int)strlen(text);

    for(int i = 0; i < n; ++i) {

        if(text[i] == '0')
            B[i] = 0;
        else
            B[i] = 1;
    }
}

int check(int nr) {   /* presupunem ca primul numar al carui prefix este continut in sir are nr caractere in baza 2 */

    int start, pos, answer = 1000000;
    bool ret = false, ok;

    for(start = 0; start < nr; ++start) {

        if(B[start] == 0)
            continue; /* primul bit tb sa fie 1 */

        ok = true;
        int firstVal = 0;
        for(pos = start; pos < n && pos - start < nr; ++pos)
            firstVal = firstVal * 2 + B[pos];

        if(pos - start < nr) {
        /* daca numarul nu este complet continut in sir */

            int minFirstVal = (firstVal << (nr - pos + start));
            int unusedBits = nr - pos + start;
            int maxFirstVal = minFirstVal + (1 << unusedBits) - 1;

            if(minFirstVal == 1 << (nr - 1)) {
            /* daca numarul e posibil sa fie o putere a lui 2 */

                bool noZeros = true;
                for(int i = 0; i < start - 1; ++i)
                    if(B[i] == 0)
                        noZeros = false;
                if(noZeros == true && B[start - 1] == 0) {

                    ret = true;
                    answer = minFirstVal;
                }
            }

            int before = 0;
            for(int i = 0; i < start; ++i)
                before = before * 2 + B[i];
            int minBefore = before + (1 << (nr - 1));
            unusedBits = nr - start;
            int maxBefore = before + (((1 << unusedBits) - 1) << start);
            //printf("%d %d %d; ", before, minBefore, maxBefore);
            minBefore++;


        }
    }

    printf("%d\n", answer);
    return ret;
}

int main() {

    readData();
    for(int i = 1; i <= n; i++) {

        printf("%d: ", i);
        int ok = check(i);
        printf("\n");
    }
    return 0;
}
