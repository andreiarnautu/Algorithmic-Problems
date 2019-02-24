/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
FILE *fin = freopen("ciuperci.in", "r", stdin);
FILE *fout = freopen("ciuperci.out", "w", stdout);

const int bufferDim = 500;
const int P = 666013;
const int mask = 1023;

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

        void getLongLong(long long &nr) {

            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + 1LL * (buffer[pos] - '0');
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

vector < pair<long long int,int> > h[1 + mask];

int find(long long int key) {
    int level = key & mask;
    for(int i = 0; i < (int)h[level].size(); ++i)
        if(h[level][i].first == key) {
            return h[level][i].second;
        }
    return 0;
}

void insert(long long int key, int value) {
    int level = key & mask;
    h[level].push_back(make_pair(key, value));
}

int back(long long int n) {

    int answer = find(n);
    if(!answer) {
        n--;
        if(n % 2 == 0) {
            int k = back(n / 2);
            int answer = (1LL * k * k) % P;
            insert(n + 1, answer);
            return answer;
        }
        else {
            int k1 = back(n / 2), k2 = back(n / 2 + 1);
            int answer = (2LL * k1 * k2) % P;
            insert(n + 1, answer);
            return answer;
        }
    }
    else {
        return answer;
    }
}

int main() {

    cin.getBuffer();
    h[1].push_back(make_pair(1, 1));
    h[2].push_back(make_pair(2, 2));

    long long q;
    for(cin.getLongLong(q); q > 0; --q) {
        long long n; cin.getLongLong(n);
        printf("%d\n", back(n));
        for(int i = 0; i < mask; ++i) {
            h[i].clear();
        }
        h[1].push_back(make_pair(1, 1));
        h[2].push_back(make_pair(2, 2));
    }

    return 0;
}
