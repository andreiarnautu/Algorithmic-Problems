/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("flori5.in", "r", stdin);
FILE *fout = freopen("flori5.out", "w", stdout);

const int MAX_N = 1 + 100000;
const int bufferDim = 100000;

class inputReader {

private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {

            return('0' <= c && c <= '9');
        }
public:

        void getBuffer() {

            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {

            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

/*------------------------------------*/
long long flowers[MAX_N], rest[MAX_N];
int N, K;

/*
    flowers[i] = cate flori cu K petale putem forma cu primele i culori, fata a vopsi mijloacele
    rest[i] = cu cate unitati de culoare mai ramanem din primele i culori, daca vopsim K * flowers[i] petale */

/*------------------------------------*/

int readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(K);
    for(int i = 1; i <= N; ++i) {
        int x; cin.getInt(x);
        flowers[i] = flowers[i - 1] + 1LL * x / K;
        rest[i] = rest[i - 1] + 1LL * x - 1LL * (x / K) * K;
    }
    int answer; cin.getInt(answer);
    return answer;
}

int main() {
    for(int M = readData(); M; --M) {
        int x, y; cin.getInt(x); cin.getInt(y);

        long long flowerCount = flowers[y] - flowers[x - 1];
        long long notUsed = rest[y] - rest[x - 1];
        if(flowerCount > notUsed) {
        /* daca putem vopsi florile, dar nu mai avem suficienta vopsea pentru a vopsi centrele florilor
           vom determina numarul x de flori la care tb sa renuntam, astfel incat sa putem vopsi si mijloacele */
            long long x = (flowerCount - notUsed) / (K + 1);
            if(x * (K + 1) != flowerCount - notUsed) {
                x++;
            }
            flowerCount -= x;
        }
        printf("%lld\n", flowerCount);
    }
    return 0;
}
