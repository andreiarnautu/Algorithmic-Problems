/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("arcas.in", "r", stdin);
FILE *fout = freopen("arcas.out", "w", stdout);

const int MAX_N = 1 + 100000 + 1;
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

struct Triplet {
    int x, y1, y2;
    Triplet() {
        this->x = this->y1 = this->y2 = 0;
    }
    Triplet(const int &x, const int &y1, const int &y2) {
        this->x = x; this->y1 = y1; this->y2 = y2;
    }
    bool operator < (const Triplet &other) const {
        return this->x < other.x;
    }
};
/*-------------------*/
Triplet T[MAX_N];
int N, M;
/*-------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    for(int i = 1; i <= N; ++i) {
        int x, y1, y2; cin.getInt(x); cin.getInt(y1); cin.getInt(y2);
        T[i] = Triplet(x, y1, y2);
    }
    sort(T + 1, T + N + 1);
}

int rightBinary(int val) {
    int answer = 1, left = 1, right = N;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(T[mid].x <= val) {
            answer = mid; left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return answer;
}

int leftBinary(int val) {
    int answer = N, left = 1, right = N;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(T[mid].x >= val) {
            answer = mid; right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}

void solveQuery() {
    int X, Y, R;
    cin.getInt(X); cin.getInt(Y); cin.getInt(R);

    int answer = 0;
    /* cautam triplete cu X intre X si X + R */
    if(X > T[N].x || X + R < T[1].x) {
        printf("%d\n", answer); return;
    }

    int left = leftBinary(X);
    int right = rightBinary(X + R);

    for(int i = left; i <= right; ++i) {
        /* verificam daca segmentul (x, y1, y2) este atins de (x + ADD, y + ADD) */
        int ADD = T[i].x - X;
        if(T[i].y1 <= Y + ADD && Y + ADD <= T[i].y2) {
            answer++;
        }
    }

    printf("%d\n", answer);
}

int main() {
    readData();
    for(int i = 1; i <= M; ++i) {
        solveQuery();
    }
    return 0;
}
