/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

FILE *fin = freopen("lss.in", "r", stdin);
FILE *fout = freopen("lss.out", "w", stdout);

using std::pair;

const int kMaxP = 1 + 100000;
const int kMaxInf = 1010000000;
const int buffer_dim = 1 + 100000;

/*-------- Input Reader --------*/
class inputReader {
private:
        char buffer[buffer_dim];
        int pos;

        bool digit(char c) {
            return('0' <= c && c <= '9');
        }

public:
        void GetBuffer() {
            fread(buffer, 1, buffer_dim, stdin);
            pos = 0;
        }

        void operator >>(int &nr) {
            nr = 0;
            char c = '+';
            while(!digit(buffer[pos])) {
                c = buffer[pos];
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == buffer_dim) {
                    GetBuffer();
                }
            }
            if(c == '-') {
                nr = -nr;
            }
        }
} cin;
/*-------- --------*/


/*-------- Structures --------*/
struct Node {
    int minimum, index;
    int first_available, index_first;
};
/*-------- Input data --------*/
int K, P;
int pos[kMaxP];
/*-------- Algorithm data --------*/
long long solution;

Node arbint[kMaxP * 8];
int lazy[kMaxP * 8];
/*-------- --------*/

void ReadInput() {
    cin.GetBuffer();
    cin >> K; cin >> P;
    for(int i = 1; i <= P; i++) {
        cin >> pos[i];
    }
    std::sort(pos + 1, pos + P + 1);
    for(int i = 1; i <= P; i++) {
        if(pos[i] % K == 0) {
            pos[i] = K;
        } else {
            pos[i] = pos[i] % K;
        }
    }
}

void BuildArbint(int node = 1, int left = 1, int right = P) {
    if(left == right) {
        arbint[node].first_available = arbint[node].minimum = pos[left];
        arbint[node].index_first = arbint[node].index = left;
    } else {
        int mid = (left + right) >> 1;
        int left_son = node << 1;
        int right_son = left_son + 1;

        BuildArbint(left_son, left, mid);
        BuildArbint(right_son, mid + 1, right);

        arbint[node].first_available = arbint[left_son].first_available;
        arbint[node].index_first = arbint[left_son].index_first;
        if(arbint[left_son].minimum < arbint[right_son].minimum) {
            arbint[node].minimum = arbint[left_son].minimum;
            arbint[node].index = arbint[left_son].index;
        } else {
            arbint[node].minimum = arbint[right_son].minimum;
            arbint[node].index = arbint[right_son].index;
        }
    }
}

void Propagate(int node, int left, int right) {
    int left_son = node << 1;
    int right_son = left_son + 1;

    if(lazy[node] != 0) {
        arbint[node].minimum += lazy[node];
        arbint[node].first_available += lazy[node];

        if(left != right) {
            lazy[left_son] += lazy[node];
            lazy[right_son] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void Update(int node, int left, int right, int first, int last, int value) {
    int mid = (left + right) >> 1;
    int left_son = node << 1;
    int right_son = left_son + 1;

    Propagate(node, left, right);
    if(first <= left && right <= last) {
        arbint[node].first_available += value;
        arbint[node].minimum += value;
        if(left != right) {
            lazy[left_son] += value;
            lazy[right_son] += value;
        }
    } else {
        if(first <= mid) {
            Update(left_son, left, mid, first, last, value);
        }
        if(mid < last) {
            Update(right_son, mid + 1, right, first, last, value);
        }
        Propagate(left_son, left, mid);
        Propagate(right_son, mid + 1, right);

        ///  Avem de calculat : (first_available, index_first); (minimum, index)
        if(arbint[left_son].first_available <= K) {
            arbint[node].first_available = arbint[left_son].first_available;
            arbint[node].index_first = arbint[left_son].index_first;
        } else {
            arbint[node].first_available = arbint[right_son].first_available;
            arbint[node].index_first = arbint[right_son].index_first;
        }

        if(arbint[right_son].minimum <= arbint[left_son].minimum) {
            arbint[node].minimum = arbint[right_son].minimum;
            arbint[node].index = arbint[right_son].index;
        } else {
            arbint[node].minimum = arbint[left_son].minimum;
            arbint[node].index = arbint[left_son].index;
        }
    }
}

void BruteForce() {
    if(K < P) {
        solution = P - K;
        P = K;
    }
    for(int i = 1; i <= P; i++) {
        int min_value = K + 1;
        int index = 0;
        for(int j = 1; j <= P; j++) {
            if(pos[j] > 0 && pos[j] <= min_value) {
                if(pos[j] < min_value) {
                    min_value = pos[j];
                    index = j;
                } else if(pos[j] == min_value && min_value == 1) {
                    index = j;
                }
            }
        }
        if(min_value != 1) {
            for(int j = 1; j <= P; j++) {
                if(pos[j] > 0) {
                    index = j; break;
                }
            }
        }
        //printf("%d %d\n", index, pos[index]);
        solution += 1LL * pos[index];
        pos[index] = 0;
        for(int j = index + 1; j <= P; j++) {
            pos[j] --;
        }
    }

    printf("%lld\n", solution);
}

void NlogN_Idea() {
    long long NlogN_solution = 0;

    if(K < P) {
        NlogN_solution = P - K;
        P = K;
    }

    BuildArbint();
    for(int i = 1; i <= P; i++) {
        Propagate(1, 1, P);
        if(arbint[1].minimum == 1) {
            NlogN_solution ++;
            int where = arbint[1].index;
            //printf("%d\n", where);
            Update(1, 1, P, where, where, +kMaxInf);
            if(where < P) {
                Update(1, 1, P, where + 1, P, -1);
            }
        } else {
            NlogN_solution += 1LL * arbint[1].first_available;
            int where = arbint[1].index_first;
            Update(1, 1, P, where, where, +kMaxInf);
            if(where < P) {
                Update(1, 1, P, where + 1, P, -1);
            }
        }
    }
    printf("%lld\n", NlogN_solution);
}

int main() {
    ReadInput();
    NlogN_Idea();
    //BruteForce();
    return 0;
}
