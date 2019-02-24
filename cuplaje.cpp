/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("cuplaje.in", "r", stdin);
FILE *fout = freopen("cuplaje.out", "w", stdout);

const int bufferDim = 100000;
const int MAX_N = 1 + 200000;

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
/*---------------*/
int N, M;
int pref[MAX_N];
/*---------------*/
multiset<int> MSet;
set<int> indexes[MAX_N];
/*---------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N); cin.getInt(M);
    for(int i = 1; i <= N; ++i) {
        cin.getInt(pref[i]);
    }
    for(int i = 1; i <= M; ++i) {
        int x; cin.getInt(x);
        indexes[x].insert(i);
        MSet.insert(x);
    }
}

void makeCouples() {
    int answer = 0;
    for(int i = N; i >= 1; --i) {
        multiset<int>::iterator it = MSet.lower_bound(i);
        if(it != MSet.end()) {
            multiset<int>::reverse_iterator it2 = MSet.rbegin();
            for(int j = *it2; j >= *it; j--) {
                if(!indexes[j].empty() && *indexes[j].begin() <= pref[i]) {
                    set<int>::iterator it3 = indexes[j].upper_bound(pref[i]);
                    it3--;
                    answer++;
                    indexes[j].erase(it3);
                    break;
                }
            }
        }
    }
    printf("%d", answer);
}

int main() {
    readData();
    makeCouples();
    return 0;
}
