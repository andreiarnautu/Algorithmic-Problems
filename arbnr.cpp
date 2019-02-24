/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using std::vector;
FILE *fin = freopen("arbnr.in", "r", stdin);
FILE *fout = freopen("arbnr.out", "w", stdout);

const int kMaxN = 1 + 10000;
const int kMaxT = 1 + 40;
const int mod = 9907;
const int kMaxBufferDim = 1 + 100000;

/*-------- Input Reader --------*/
class inputReader {
private:
        char buffer[kMaxBufferDim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void GetBuffer() {
            fread(buffer, 1, kMaxBufferDim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == kMaxBufferDim) {
                    GetBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == kMaxBufferDim) {
                    GetBuffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;
/*-------- Input data --------*/
int N, T;
int M[kMaxT];
vector<int > graph[kMaxN];
/*-------- Model trees data --------*/
char encrypted_form[kMaxT][2 * kMaxN];
int cursor;

int pi[kMaxT][2 * kMaxN];
bool not_needed[kMaxT];

int how_many[kMaxN];
/*-------- DP --------*/
int dp[kMaxN];
int sets[kMaxN];
/*-------- --------*/

inline void DFS(int node, int t) {
    cursor ++;
    encrypted_form[t][cursor] = '(';
    for(int son : graph[node]) {
        DFS(son, t);
    }
    cursor ++;
    encrypted_form[t][cursor] = ')';
}

void ReadInput() {
    cin.GetBuffer();
    cin >> N; cin >> T;
    for(int i = 1; i <= T; i++) {
        cin >> M[i];
        for(int j = 2; j <= M[i]; j++) {
            int dad; cin >> dad;
            graph[dad].push_back(j);
        }
        cursor = 0;
        DFS(1, i);
        for(int j = 1; j <= M[i]; j++) {
            graph[j].clear();
        }
    }
}

inline void GetPi(int index) {
    int k = 0;
    for(int i = 2; i <= M[index] * 2; i++) {
        while(k > 0 && encrypted_form[index][i] != encrypted_form[index][k + 1]) {
            k = pi[index][k];
        }
        if(encrypted_form[index][i] == encrypted_form[index][k + 1]) {
            k ++;
        }
        pi[index][i] = k;
    }
}

inline bool Find(int a, int b) {  //  Verificam daca {b} apare in {a}
    int k = 0;
    for(int i = 1; i <= M[b] * 2; i++) {
        while(k > 0 && encrypted_form[b][i] != encrypted_form[a][k + 1]) {
            k = pi[a][k];
        }
        if(encrypted_form[b][i] == encrypted_form[a][k + 1]) {
            k ++;
        }
        if(k == M[a] * 2) {
            return true;
        }
    }

    return false;
}

void GetNotNeededTrees() {
    for(int i = 1; i <= T; i++) {
        GetPi(i);
    }
    for(int i = 1; i <= T; i++) {
        for(int j = 1; j <= T; j++) {
            if(i == j) continue;
            if(M[i] < M[j]) continue;
            bool ok = Find(j, i);

            if(ok) {
                if(M[i] != M[j]) {
                    not_needed[i] = true; break;
                } else if(i > j) {
                    not_needed[i] = true; break;
                }
            }
        }
    }
    for(int i = 1; i <= T; i++) {
        if(!not_needed[i]) {
            //printf("%d; ", M[i]);
            how_many[M[i]] ++;
        }
    }
}

void RunDP() {
    dp[0] = sets[0] = 1;
    for(int i = 1; i <= N; i++) {
        dp[i] = (sets[i - 1] - how_many[i] + mod) % mod;
        for(int j = 1; j <= i; j++) {
            sets[i] = (sets[i] + dp[j] * sets[i - j]) % mod;
        }
    }
}

void WriteOutput() {
    printf("%d\n", dp[N]);
}

int main() {
    ReadInput();
    GetNotNeededTrees();
    RunDP();
    WriteOutput();
    return 0;
}
