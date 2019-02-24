/**
  *  Worg
  *
  *  Complexitate: O(T * lg(L) * log(N))
  */


#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;
FILE *fin = freopen("dragonball.in", "r", stdin);
FILE *fout = freopen("dragonball.out", "w", stdout);

const int MAX_N = 5 + 1000 + 1;
const int MAX_LEN = 5 + 10000;
const int BASE = 1000000;

char s[MAX_LEN];
int N, T;

int vec[MAX_N][MAX_LEN];
int dist[MAX_N][MAX_LEN];
int bonus[MAX_N];

/*------------------------------------------------------------------------*/

void write(int *A) {
    for(int i = A[0]; i > 0; --i) {
        if(i < A[0]) {
            if(A[i] < 100000) {
                printf("0");
            }
            if(A[i] < 10000) {
                printf("0");
            }
            if(A[i] < 1000) {
                printf("0");
            }
            if(A[i] < 100) {
                printf("0");
            }
        }
        printf("%d", A[i]);
    }
    printf("\n");
}

void assignValue(int *A) {
    A[0] = strlen(s);

    int current = 1, rest = A[0] % 6;
    if(!rest) {
        rest = 6;
    }
    for(int i = 0; i < rest; ++i) {
        A[current] = A[current] * 10 + s[i] - '0';
    }
    current++;

    for(int i = rest; i < A[0]; i += 6) {
        for(int j = i; j < i + 6; ++j) {
            A[current] = A[current] * 10 + s[j] - '0';
        }
        current++;
        A[current] = 0;
    }

    current--;
    int left = 1, right = current;
    while(left < right) {
        swap(A[left], A[right]);
        left++;
        right--;
    }
}

void assignValue(int *A, int *B) {
    for(int i = 0; i <= B[0]; ++i) {
        A[i] = B[i];
    }
}

void difference(int *A, int *B) {
    int i, t = 0;
    for(i = 1; i <= A[0]; ++i) {
        A[i] -= ((i <= B[0]) ? B[i] : 0) + t;
        A[i] += (t = A[i] < 0) * BASE;
    }
    while(A[0] > 1 && A[A[0]] == 0) {
        A[0]--;
    }
}

void divide(int index) {
    int i, t = 0;

    for(i = vec[index][0]; i > 0; --i, t %= bonus[index]) {
        dist[index][i] = (t = t * BASE + vec[index][i]) / bonus[index];
    }
    dist[index][0] = vec[index][0];
    while(dist[index][0] > 1 && !dist[index][dist[index][0]]) {
        dist[index][0]--;
    }

    if(t > 0) {
        for(i = 1; i <= dist[index][0] && dist[index][i] == BASE - 1; ++i) {
            dist[index][i] = 0;
        }
        if(i <= dist[index][0]) {
            dist[index][i]++;
        }
        else {
            dist[index][0] = i;
            dist[index][i] = 1;
        }
    }
}

bool compare(int *A, int *B) {
    if(A[0] != B[0]) {
        return A[0] > B[0];
    }
    else {
        for(int i = A[0]; i > 0; --i)
            if(A[i] != B[i]) {
                return A[i] > B[i];
            }
        return 1;
    }
}

/*------------------------------------------------------------------------*/

void readData() {

    scanf("%d%d ", &N, &T);
    gets(s); assignValue(vec[++N]);

    for(int i = 1; i < N; ++i) {
        gets(s); assignValue(vec[i]);
    }
}

void getDistances() {

    for(int i = N; i > 0; --i) {
        difference(vec[i], vec[i - 1]);
        assignValue(dist[i], vec[i]);
        bonus[i] = 1;
    }
}

class comp {

public:
        bool operator() (const int &a, const int &b) {
            return compare(dist[a], dist[b]) == 0;
        }
};

priority_queue <int, vector<int>, comp> pq;

void solveSteps() {

    for(int i = N; i > 0; --i) {
        pq.push(i);
    }

    for(int i = 1; i <= T; ++i) {
        int index = pq.top(); pq.pop();
        bonus[index]++;
        divide(index);
        pq.push(index);
    }

    int index = pq.top();
    write(dist[index]);
}

int main() {

    readData();
    getDistances();
    solveSteps();
    return 0;
}
