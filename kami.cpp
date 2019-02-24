/**
  *  Worg
  *  Smenul lui Batog
  *  update: O(sqrt(N))
  *  query: O(sqrt(N))
  */
#include <cstdio>
#include <algorithm>

#define lsb(x) (x & (-x))

using namespace std;
FILE *fin = freopen("kami.in", "r", stdin);
FILE *fout = freopen("kami.out", "w", stdout);

const int MAX_N = 1 + 100000,
          bufferSize = 50000,
          blockSize = 295,
          maxBlocks = MAX_N / blockSize + 1;

class inputReader {

private:
        char buffer[bufferSize];
        int pos = 0;
public:
        void getBuffer() {

            fread(buffer, 1, bufferSize, stdin);
            pos = 0;
        }

        bool digit(char c) {

            return ('0' <= c && c <= '9');
        }

        void getInt(int &nr) {

            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferSize)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferSize)
                    getBuffer();
            }
        }
} cin;

long long int z[MAX_N], a[MAX_N], aib[MAX_N], maxVal[maxBlocks], lazy[maxBlocks];
int n, m;
bool queryResult;

void updateAib(int pos, long long int val) {

    for(; pos <= n; pos += lsb(pos))
        aib[pos] += val;
}

long long int queryAib(int pos) {

    long long int ret = 0;
    for(; pos; pos -= lsb(pos))
        ret += aib[pos];
    return ret;
}

int getBlock(int pos) {

    return (pos - 1) / blockSize + 1;
}

void updateBlocks(int pos, long long int val) {

    int block = getBlock(pos), first = blockSize * (block - 1) + 1;

    z[pos] += val;
    maxVal[block] = max(maxVal[block], z[pos]);

    for(--pos; pos >= first; --pos) { /* facem update pe elementele blocului curent */

        z[pos] -= val;
        maxVal[block] = max(maxVal[block], z[pos]);
    }
    for(--block; block > 0; --block) /* pe celelalte blocuri facem lazy update */
        lazy[block] -= val;
}

int query(int pos, long long int val) {

    int block = getBlock(pos), first = blockSize * (block - 1) + 1;
    long long int needed = val - lazy[block];
    for(; pos >= first; --pos)          /* verificam fiecare element din blocul curent */
        if(z[pos] >= needed)
            return pos;
    for(--block; block > 0; --block)
        if(maxVal[block] + lazy[block] >= val) { /* daca in blocul curent este un element care satisface conditia, il cautam */

            int first = (block - 1) * blockSize + 1;
            needed = val - lazy[block];
            for(pos = block * blockSize; pos >= first; --pos)
                if(z[pos] >= needed)
                    return pos;
        }
    /* daca nu exista elemente care sa satisfaca conditia, avalansa se opreste in 0 */
    return 0;
}

void readData() {

    cin.getBuffer();
    cin.getInt(n);
    for(int i = 1; i <= n; ++i) {

        int x; cin.getInt(x);
        a[i] = x;
        updateAib(i, x);
        updateBlocks(i, x);
    }
    cin.getInt(m);
}

int main() {

    readData();
    for(int i = 1; i <= m; ++i) {

        int op; cin.getInt(op);
        if(!op) { /* avem update */

            int x, val;
            cin.getInt(x); cin.getInt(val);
            updateAib(x, 1LL * val - a[x]);
            updateBlocks(x, val - a[x]);
            a[x] = val;
        }
        else { /* avem query */

            int b; cin.getInt(b);
            long long int val = queryAib(b) - queryAib(n);
            if(b > 1)
                printf("%d\n", query(b - 1, val));
            else
                printf("0\n");
        }
    }
    return 0;
}
