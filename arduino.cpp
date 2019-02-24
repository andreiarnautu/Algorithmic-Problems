/**
  *  Worg
  */
#include <set>
#include <cstdio>
#include <vector>

using std::set;
using std::vector;

FILE *fin = freopen("arduino.in", "r", stdin);
FILE *fout = freopen("arduino.out", "w", stdout);

const int kMaxRestrict = 1 + 100;
const int mod = 1e9 + 7;
const int kMaxN = 1 + 10;
const int kMaxM = 1 + 1000;

/*-------- Input data --------*/
int N, M, R;
int nr[kMaxRestrict];
vector<int > indexes[kMaxRestrict];
/*-------- Backtracking --------*/
int where[kMaxN];
/*-------- Case validation --------*/
set<int > my_set;
/*-------- Solution --------*/
long long fact[kMaxM];
long long solution;

int global;
/*-------- --------*/

void GetFact() {
    fact[0] = 1;
    for(int i = 1; i < kMaxM; i++) {
        fact[i] = 1LL * fact[i - 1] * i % mod;
    }
}

void ReadInput() {
    scanf("%d%d%d", &N, &M, &R);

    for(int i = 1; i <= R; i++) {
        scanf("%d", &nr[i]);
        int cnt; scanf("%d", &cnt);
        for(int j = 1; j <= cnt; j++) {
            int x; scanf("%d", &x);
            indexes[i].push_back(x);
        }
    }
}

long long Power(long long base, long long exp) {
    long long answer = 1, aux = base;
    for(long long i = 1; i <= exp; i <<= 1) {
        if(i & exp) {
            answer = answer * aux % mod;
        }
        aux = aux * aux % mod;
    }
    return answer;
}

long long Aran(int n, int k) {
    if(k > n) {
        return 0;
    } else {
        return (1LL * fact[n] * Power(fact[n - k], mod - 2)) % mod;
    }
}

void CheckNewCase(int k) {
    for(int i = 1; i <= R; i++) {
        my_set.clear();
        for(int x : indexes[i]) {
            my_set.insert(where[x]);
        }

        if((int)my_set.size() != nr[i]) {
            return;
        }
    }

    //global ++;
    solution = (solution + Aran(M, k)) % mod;
}

void Back(int node, int k) {
    if(node == N + 1) {
        CheckNewCase(k);
    } else {
        for(int i = 1; i <= k; i++) {
            where[node] = i;
            Back(node + 1, k);
        }
        where[node] = k + 1;
        Back(node + 1, k + 1);
    }
}

int main() {
    GetFact();
    ReadInput();
    where[1] = 1;
    Back(1, 0);
    printf("%lld\n", solution);
    return 0;
}
