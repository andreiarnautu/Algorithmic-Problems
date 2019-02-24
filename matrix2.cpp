/**
  *  Worg
  */
#include <stack>
#include <cstdio>

using namespace std;
FILE *fin = freopen("matrix2.in", "r", stdin);
FILE *fout = freopen("matrix2.out", "w", stdout);

const int MAX_N = 1000, bufferDim = 1000;

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

int n, m;
int bit[1 + MAX_N], len[1 + MAX_N];
int maxArea;

int ST[1 + MAX_N], pos;

int main() {

    cin.getBuffer();
    cin.getInt(n); cin.getInt(m);
    for(int i = 1; i <= n; ++i) {

        pos = 0;

        for(int j = 1; j <= m; ++j) {

            cin.getInt(bit[j]);
            if(bit[j] == 0)
                len[j]++;
            else
                len[j] = 0;

            while(pos && len[j] <= len[ST[pos]])
                pos--;
            ST[++pos] = j;

            for(int l = 1; l <= pos; ++l)
                maxArea = max(maxArea, len[ST[l]] * (j - ST[l - 1]));
        }
    }

    printf("%d\n", maxArea);
    return 0;
}
