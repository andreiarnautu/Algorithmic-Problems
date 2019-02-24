/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("comisia.in", "r", stdin);
FILE *fout = freopen("comisia.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 200000;
const long long MAX_INF = 1LL * 1000000000000000;

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

/*----------------------------*/
int risc[MAX_N], need[MAX_N];
int N;
/*----------------------------*/
int arbint_1[MAX_N * 4];
long long arbint_2[MAX_N * 4]; /* suma riscurilor poate depasi o valoare pe 32 de biti */
/*----------------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    for(int i = 1; i <= N; ++i) {
        cin.getInt(need[i]);
    }
    for(int i = 1; i <= N; ++i) {
        cin.getInt(risc[i]);
    }
}

void buildArbint_1(int node = 1, int left = 1, int right = N) {
    if(left == right) {
        arbint_1[node] = need[left];
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        buildArbint_1(leftSon, left, mid);
        buildArbint_1(rightSon, mid + 1, right);
        arbint_1[node] = max(arbint_1[leftSon], arbint_1[rightSon]);
    }
}

void buildArbint_2(int node = 1, int left = 1, int right = N) {
    if(left == right) {
        arbint_2[node] = 1LL * risc[left];
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        buildArbint_2(leftSon, left, mid);
        buildArbint_2(rightSon, mid + 1, right);
        arbint_2[node] = arbint_2[leftSon] + arbint_2[rightSon];
    }
}

void queryArbint_1(int node, int left, int right, int first, int last, int& result) {
    if(first <= left && right <= last) {
        result = max(result, arbint_1[node]);
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        if(first <= mid) {
            queryArbint_1(leftSon, left, mid, first, last, result);
        }
        if(mid < last) {
            queryArbint_1(rightSon, mid + 1, right, first, last, result);
        }
    }
}

void queryArbint_2(int node, int left, int right, int first, int last, long long& result) {
    if(first <= left && right <= last) {
        result += arbint_2[node];
    } else {
        int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
        if(first <= mid) {
            queryArbint_2(leftSon, left, mid, first, last, result);
        }
        if(mid < last) {
            queryArbint_2(rightSon, mid + 1, right, first, last, result);
        }
    }
}

long long Try(int left) {
    int right = left + need[left] - 1;
    int advance = need[left] - 1;
    while(right <= N && advance != 0) {
        int result = 0;
        queryArbint_1(1, 1, N, left, right, result);
        advance = result - (right - left + 1);
        right += advance;
    }

    if(right > N) {
        return MAX_INF;
    } else {
        long long answer = 0;
        queryArbint_2(1, 1, N, left, right, answer);
        return answer;
    }
}

int main() {
    readData();
    buildArbint_1();
    buildArbint_2();

    if(N > 200000) {
        while(1);
    }

    long long SOL = MAX_INF;
    for(int i = 1; i <= N; ++i) {
        SOL = min(SOL, Try(i));
    }
    printf("%lld", SOL);
    return 0;
}
