/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;
FILE *fin = freopen("arbore3.in", "r", stdin);
FILE *fout = freopen("arbore3.out", "w", stdout);

const int MAX_N = 1 + 1000000;
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

            char sign = '+';
            nr = 0;
            while(!digit(buffer[pos])) {
                sign = buffer[pos];
                if(++pos == bufferDim)
                    getBuffer();
            }
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }

            if(sign == '-') {
                nr = -nr;
            }
        }
} cin;

vector <int> G[MAX_N];
int v[MAX_N];
int n, s;

bool checked[MAX_N];
int rootSum[MAX_N];

unordered_map <int, int> sums;

void readData() {

    cin.getBuffer();
    cin.getInt(n); cin.getInt(s);
    for(int i = 1; i <= n; ++i) {
        int father;
        cin.getInt(father); cin.getInt(v[i]);

        G[father].push_back(i);
    }
}

void getRootSums(int node) {

    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        rootSum[*it] = rootSum[node] + v[*it];
        getRootSums(*it);
    }
}

long long int answer;

void getSumS(int node) {

    answer += (1LL * sums[rootSum[node] - s]);
    sums[rootSum[node]]++;

    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
        getSumS(*it);
    }
    sums[rootSum[node]]--;
}

int main() {

    readData();
    rootSum[1] = v[1];
    getRootSums(1);
    sums[0] = 1;
    getSumS(1);
    printf("%lld", answer);
    return 0;
}
