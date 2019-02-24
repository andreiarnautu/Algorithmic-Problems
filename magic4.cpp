/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("magic4.in", "r", stdin);
FILE *fout = freopen("magic4.out", "w", stdout);

const int MAX_N = 1 + (1 << 16);

int vec[16] = {
1+2+4+8+16+32+64+128+256+512+1024+2048+4096+8192+16384+32768,
1  +4  +16   +64    +256    +1024     +4096     +16384,
1+2    +16+32       +256+512          +4096+8192,
1      +16          +256              +4096,
1+2+4+8             +256+512+1024+2048,
1  +4               +256    +1024,
1+2                 +256+512,
1                   +256,
1+2+4+8+16+32+64+128,
1  +4  +16   +64,
1+2    +16+32,
1      +16,
1+2+4+8,
1  +4,
1+2,
1};

int Solution[MAX_N];

void preCalculate() {
    const int maxSteps = (1 << 16);

    for(int i = 0, rest = 1, step = 2; i < 16; i++, rest <<= 1, step <<= 1) {
        for(int j = rest; j < maxSteps; j += step) {
            Solution[j] = vec[i];
        }
    }
}

void outputData() {
    const int maxSteps = (1 << 16);
    for(int i = 0; i < maxSteps; i++) {
        printf("%d\n", Solution[i]);
    }
}

int main() {
    preCalculate();
    outputData();
    return 0;
}
