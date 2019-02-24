/**
  *  Worg
  */
#include <ctime>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("minlcm.in", "r", stdin);
FILE *fout = freopen("minlcm.out", "w", stdout);

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

bool ok[MAX_N];

int V[MAX_N];

int T, N;
int elemMax;
long long sol;

void readData() {
    cin.getInt(N);
    elemMax = 0;
    for(int i = 1; i <= N; ++i) {
        int x; cin.getInt(x);
        V[i] = x;
        elemMax = max(elemMax, x);
        ok[x] = true;
    }
}

void go(int div) {
    int first = 0, second = 0;
    for(int i = div; i <= elemMax; i += div) {
        if(ok[i]) {
            if(!first) {
                first = i; continue;
            }
            else {
                second = i;
                sol = min(sol, 1LL * first * second / div);
                return;
            }
        }
    }
}

int main() {
    clock_t startTime = clock();


    cin.getBuffer();
    cin.getInt(T);
    for(; T; --T) {
        readData();
      //  printf("%d\n", elemMax);
        sol = 1LL * 100100 * 100100;
        for(int i = 1; i <= elemMax; ++i) {
            go(i);
        }
        for(int i = 1; i <= N; ++i) {
            ok[V[i]] = false;
        }
        printf("%lld\n", sol);
    }

    clock_t finishTime = clock();
   // printf("%.3f", (float) (finishTime - startTime) / CLOCKS_PER_SEC);
    return 0;
}
