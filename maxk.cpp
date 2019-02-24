/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("maxk.in", "r", stdin);
FILE *fout = freopen("maxk.out", "w", stdout);

const int MAX_N = 1 + 1000000;
const int bufferDim = 100000;
const int MAX_VAL = 1 + 100000;

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

int N, K;
int a[MAX_N];

int cnt[MAX_VAL];

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(K);
    for(int i = 1; i <= N; ++i) {
        cin.getInt(a[i]);
    }
}

bool Try(int len) {
    int overflow = 0;

    for(int i = 1; i < MAX_VAL; ++i) {
        cnt[i] = 0;
    }
    for(int i = 1; i <= N; ++i) {
        cnt[a[i]]++;
        if(cnt[a[i]] == K + 1) {
            overflow++;
        }
    }

    if(!overflow) {
        return true;
    }

    for(int i = 1; i <= len; ++i) {
        cnt[a[i]]--;
        if(cnt[a[i]] == K) {
            overflow--;
        }
    }

    for(int i = len + 1; i <= N; ++i) {
        if(!overflow) {
            return true;
        }
        cnt[a[i - len]]++;
        if(cnt[a[i - len]] == K + 1) {
            overflow++;
        }

        cnt[a[i]]--;
        if(cnt[a[i]] == K) {
            overflow--;
        }
    }

    if(!overflow) {
        return true;
    }
    return false;
}

int binarySearch() {
    int left = 0, right = N - 1, answer = N - 1;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(Try(mid)) {
            answer = mid;
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}

int main() {
    readData();
    printf("%d", binarySearch());
    return 0;
}
