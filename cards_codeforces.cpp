/**
  *  Worg
  */
#include <cstdio>

using namespace std;

const int MAX_N = 1 + 200;

int n;
char s[MAX_N];

int count[3];

int main() {
    scanf("%d", &n);
    scanf("%s", s);

    for(int i = 0; i < n; ++i) {
        if(s[i] == 'B') {
            count[0]++;
        }
        if(s[i] == 'G') {
            count[1]++;
        }
        if(s[i] == 'R') {
            count[2]++;
        }
    }

    int differentLetters = 0;
    for(int i = 0; i < 3; ++i) {
        if(count[i]) {
            differentLetters++;
        }
    }

    if(differentLetters == 3) {
        /* daca avem cel putin una din fiecare litera, putem forma orice alta litera */
        /* din starea (i, j, k) cu i > 0, j > 0, k > 0 putem ajunge in (1, 1, 1) si dupa este evident */
        printf("BGR");
    }
    else if(differentLetters == 2) {
        if(!count[0]) {
            /* daca avem doar G si R */
            if(count[1] == 1 && count[2] == 1) {
                printf("B");
            }
            else if(count[1] == 1 && count[2] > 1) {
                printf("BG");
            }
            else if(count[1] > 1 && count[2] == 1) {
                printf("BR");
            }
            else {
                /* daca exista cel putin doua din fiecare, putem forma si a treia culoare si sa ajungem iarasi in stadiul (i,j,k) */
                printf("BGR");
            }
        }

        if(!count[1]) {
            /* aici e similar cu cazul de mai sus */
            if(count[0] == 1 && count[2] == 1) {
                printf("G");
            }
            else if(count[0] == 1 && count[2] > 1) {
                printf("BG");
            }
            else if(count[0] > 1 && count[2] == 1) {
                printf("GR");
            }
            else {
                printf("BGR");
            }
        }

        if(!count[2]) {
            if(count[0] == 1 && count[1] == 1) {
                printf("R");
            }
            else if(count[0] == 1 && count[1] > 1) {
                printf("BR");
            }
            else if(count[0] > 1 && count[1] == 1) {
                printf("GR");
            }
            else {
                printf("BGR");
            }
        }
    }

    else {
        /* daca avem doar o singura culoare, doar aceea va putea fi obtinuta */
        if(count[0]) {
            printf("B");
        }
        if(count[1]) {
            printf("G");
        }
        if(count[2]) {
            printf("R");
        }
    }

    return 0;
}
