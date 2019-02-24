/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define mid ((left + right) >> 1)

using namespace std;
FILE *fin = freopen("diapazon.in", "r", stdin);
FILE *fout = freopen("diapazon.out", "w", stdout);

const long long MOD = 1000000007;
const int MAX_N = 1 + 100000;
const int bufferDim = 100000;

/*-------- Input reader --------*/
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
                if(++ pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {
                nr = nr * 10 + buffer[pos] - '0';
                if(++ pos == bufferDim)
                    getBuffer();
            }
        }
} cin;
/*-------- Input data --------*/
struct Diapazon {
    int left, right;
    int indexLeft, indexRight;
    long long p, q, realQ;
};

int N;
Diapazon diapazon[MAX_N];

int index;
vector< int > vec;
unordered_map< int,int > Map;
/*-------- Segment tree data --------*/
struct Node {
    long long prod;
    long long sum;
    Node *left;
    Node *right;

    Node() {
        this->prod = 1;
        this->sum = 0;
        this->left = this->right = NULL;
    }
};

Node *Root = new Node;
bool solvedLeft[MAX_N << 2], solvedRight[MAX_N << 2];
/*----------------*/

long long Pow(long long a, long long b) {
    long long Answer = 1, aux = a;
    for(long long i = 1; i <= b; i <<= 1) {
        if(i & b) {
            Answer = (Answer * aux) % MOD;
        }
        aux = (aux * aux) % MOD;
    }
    return Answer;
}

void Spread(Node *node) {
    if(node->prod == 1) {
        return;
    }

    if(node->left != NULL) {
        node->left->prod = (node->left->prod * node->prod);
        if(node->left->prod >= MOD) {
            node->left->prod %= MOD;
        }
    }
    if(node->right != NULL) {
        node->right->prod = (node->right->prod * node->prod);
        if(node->right->prod >= MOD) {
            node->right->prod %= MOD;
        }
    }
    node->sum = (node->prod * node->sum);
    if(node->sum >= MOD) {
        node->sum %= MOD;
    }
    node->prod = 1;
}

void updateNode(Node *node) {
    if(node->left == NULL && node->right == NULL) {
        return;
    }
    node->sum = 0;
    if(node->left != NULL) {
        Spread(node->left);
        node->sum = (node->sum + node->left->sum);
    }
    if(node->right != NULL) {
        Spread(node->right);
        node->sum = (node->sum + node->right->sum);
    }

    if(node->sum >= MOD) {
        node->sum %= MOD;
    }
}

void Update(Node *node, int left, int right, int first, int last, long long value) {
    Spread(node);

    if(first <= left && right <= last) {
        node->prod = (node->prod * value);
        if(node->prod >= MOD) {
            node->prod %= MOD;
        }
        Spread(node);
    } else {
        if(first <= mid && node->left != NULL) {
            Update(node->left, left, mid, first, last, value);
        }
        if(mid < last && node->right != NULL) {
            Update(node->right, mid + 1, right, first, last, value);
        }

        updateNode(node);
    }
}

void addValue(Node *node, int left, int right, int value, long long coef) {
    Spread(node);

    node->sum = (node->sum + coef);
    node->sum -= (node->sum >= MOD) * MOD;
    if(left == right) {
        return;
    } else {
        if(value <= mid) {
            if(node->left == NULL) {
                node->left = new Node();
            }
            addValue(node->left, left, mid, value, coef);
        } else {
            if(node->right == NULL) {
                node->right = new Node();
            }
            addValue(node->right, mid + 1, right, value, coef);
        }
        //updateNode(node);
    }
}

void Query(Node *node, int left, int right, int first, int last, long long &Answer) {
    Spread(node);

    if(first <= left && right <= last) {
        Answer = (Answer + node->sum);
        Answer -= (Answer >= MOD) * MOD;
    } else {
        if(first <= mid && node->left != NULL) {
            Query(node->left, left, mid, first, last, Answer);
        }
        if(mid < last && node->right != NULL) {
            Query(node->right, mid + 1, right, first, last, Answer);
        }
    }
}

void getValue(Node *node, int left, int right, int value, long long &Answer) {
    Spread(node);

    if(left == right) {
        Answer = node->sum;
    } else {
        if(value <= mid && node->left != NULL) {
            getValue(node->left, left, mid, value, Answer);
        }
        if(mid < value && node->right != NULL) {
            getValue(node->right, mid + 1, right, value, Answer);
        }
    }
}

void readInput() {
    cin.getBuffer();
    cin.getInt(N);

    for(int i = 1; i <= N; i++) {
        cin.getInt(diapazon[i].left); cin.getInt(diapazon[i].right);
        int p, q; cin.getInt(p); cin.getInt(q);
        diapazon[i].p = 1LL * p; diapazon[i].q = 1LL * q;
        vec.push_back(diapazon[i].left);
        vec.push_back(diapazon[i].right);
        diapazon[i].realQ = Pow(diapazon[i].q, MOD - 2);
    }
    sort(vec.begin(), vec.end());
    for(int val : vec) {
        if(Map.find(val) == Map.end()) {
            Map[val] = (++ index);
        }
    }
    for(int i = 1; i <= N; i++) {
        diapazon[i].indexLeft = Map[diapazon[i].left];
        diapazon[i].indexRight = Map[diapazon[i].right];
    }
}

void deleteTree(Node *node, int left, int right) {
    if(left == right) {
        delete node;
    } else {
        if(node->left != NULL) {
            deleteTree(node->left, left, mid);
        }
        if(node->right != NULL) {
            deleteTree(node->right, mid + 1, right);
        }
        delete node;
    }
}

long long solveRight() {
    addValue(Root, 1, index, diapazon[1].indexRight, 1);

    for(int i = 2; i <= N; i++) {
        long long Prob = 0;
        long long coef;
        Query(Root, 1, index, diapazon[i].indexLeft, diapazon[i].indexRight, Prob);

        coef = (diapazon[i].q * diapazon[i].realQ - diapazon[i].p * diapazon[i].realQ) % MOD;
        Update(Root, 1, index, diapazon[i].indexLeft, diapazon[i].indexRight, coef);

        coef = (diapazon[i].p * diapazon[i].realQ) % MOD;
        addValue(Root, 1, index, diapazon[i].indexRight, (coef * Prob) % MOD);
    }

    long long Answer = 0;
    for(int i = 1; i <= N; i++) {
        if(!solvedRight[diapazon[i].indexRight]) {
            long long Prob = 0;
            getValue(Root, 1, index, diapazon[i].indexRight, Prob);
            Answer = (Answer + Prob * diapazon[i].right) % MOD;
            solvedRight[diapazon[i].indexRight] = true;
        }
    }

    return Answer;
}

Node *Root2 = new Node;

long long solveLeft() {

    addValue(Root2, 1, index, diapazon[1].indexLeft, 1);
    for(int i = 2; i <= N; i++) {
        long long Prob = 0;
        long long coef;
        Query(Root2, 1, index, diapazon[i].indexLeft, diapazon[i].indexRight, Prob);

        coef = (diapazon[i].q * diapazon[i].realQ - diapazon[i].p * diapazon[i].realQ) % MOD;
        Update(Root2, 1, index, diapazon[i].indexLeft, diapazon[i].indexRight, coef);

        coef = (diapazon[i].p * diapazon[i].realQ) % MOD;
        addValue(Root2, 1, index, diapazon[i].indexLeft, (coef * Prob) % MOD);
    }

    long long Answer = 0;
    for(int i = 1; i <= N; i++) {
        if(!solvedLeft[diapazon[i].indexLeft]) {
            long long Prob = 0;
            getValue(Root2, 1, index, diapazon[i].indexLeft, Prob);
            Answer = (Answer + diapazon[i].left * Prob) % MOD;
            solvedLeft[diapazon[i].indexLeft] = true;
        }
    }

    return Answer;
}

int main() {
    readInput();
    long long expectedRight = solveRight();
    long long expectedLeft = solveLeft();
    long long Solution = (expectedRight - expectedLeft + MOD) % MOD;

    printf("%lld\n", Solution);
    return 0;
}
