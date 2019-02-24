/**
  *  Worg
  */
#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("hamster.in", "r", stdin);
FILE *fout = freopen("hamster.out", "w", stdout);

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

        void getLongLong(long long &nr) {
            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + 1LL * buffer[pos] - 1LL * '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

const int MAX_N = 1 + 3000;
const int MAX_Q = 1 + 300000;

/*--------------------------------*/
long long X[MAX_N], D[MAX_Q];
int K[MAX_Q];
int N, Q;
/*--------------------------------*/
pair< long long,int > queries[MAX_Q];
/*--------------------------------*/

void readInput() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(Q);
    for(int i = 1; i <= N; i++) {
        cin.getLongLong(X[i]);
    }
    for(int i = 1; i <= Q; i++) {
        cin.getInt(K[i]); cin.getLongLong(D[i]);
    }
}

void subtaskOne() {
    /* Score: 20 points
       Complexity: O(Q*N) */


    for(int i = 1; i <= Q; i++) {
        int crtIndex = 1, crtAnswer = 0;
        long long crtPos = X[1];
        while(crtIndex <= K[i]) {
            crtAnswer++;
            crtPos += D[i];
            while(X[crtIndex] <= crtPos && crtIndex <= K[i]) {
                crtIndex++;
            }
            if(crtIndex <= K[i]) {
                crtPos = X[crtIndex];
            }
        }
        printf("%d\n", crtAnswer);
    }

}

void sortQueries() {
    for(int i = 1; i <= Q; i++) {
        queries[i].first = D[i]; queries[i].second = i;
    }
    sort(queries + 1, queries + Q + 1);
}

void subtaskTwo() {
    sortQueries(); /* we sort the queries by the length of the blocks */


}

int main() {
    readInput();
    if(Q <= 2000) {
        subtaskOne();
    } else {
        subtaskTwo();
    }

    return 0;
}
