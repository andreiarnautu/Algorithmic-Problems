/**
  *  Worg
  */

#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_LEN = 260;

char exp[MAX_LEN];
bool inText[3];
int totalCoef[3];

int main() {

    gets(exp + 1);
    if(exp[1] != '-')
        exp[0] = '+';
    int len = strlen(exp + 1);

    for(int i = 1; i <= len; ++i)
        if('x' <= exp[i] && exp[i] <= 'z') {

            inText[exp[i] - 'x'] = true;

            int coef = 0, sign;
            if(exp[i - 1] == '+') {
                coef = 1;
            }
            else if(exp[i - 1] == '-') {
                coef = -1;
            }
            else {
                int j = i - 1;
                while(exp[j] != '+' && exp[j] != '-') {
                    j--;
                }
                if(exp[j] == '+') {
                    sign = 1;
                }
                else {
                    sign = -1;
                }

                for(int l = j + 1; l < i; ++l)
                    if(exp[l] != ' ') {
                        coef = coef * 10 + exp[l] - '0';
                    }
                coef *= sign;
            }

            totalCoef[exp[i] - 'x'] += coef;
        }

    int maxim = -2000000001, sol = 0;
    for(int i = 0; i < 3; ++i)
        if(inText[i] && maxim < totalCoef[i]) {

            sol = i;
            maxim = totalCoef[i];
        }

    printf("%d%c", maxim, 'x' + sol);
    return 0;
}
