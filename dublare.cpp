/**
  *  Worg
  */
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_LEN = 260;

char text[MAX_LEN];
char nou[MAX_LEN];
int len, stop = 0;

bool powerOfTwo(int number) {

    return !(number & (number - 1));
}

void giveItAGo(int lg) {

    int current = lg;
    for(int i = 1; i <= lg; i++)
        nou[i] = text[i];
    while(lg < len) {

        for(int i = lg + 1; i <= lg << 1; ++i)
            nou[i] = nou[(lg << 1) - i + 1];
        lg <<= 1;
    }

    for(int i = 1; i <= len; ++i)
        if(text[i] != nou[i])
            return;
    stop = current;
}

int main() {

    gets(text + 1);
    len = strlen(text + 1);

    for(int i = 1; i <= len / 2 && !stop; i++)
        if(powerOfTwo(len / i)) {
            giveItAGo(i);
        }

    if(!stop) {
        printf("0");
    }
    else {
        int p2 = 0;
        while(stop < len) {
            stop <<= 1;
            p2++;
        }
        printf("%d", p2);
    }
    return 0;
}
