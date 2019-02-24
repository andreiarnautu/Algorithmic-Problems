/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define pb          push_back

using namespace std;
FILE *fin = freopen("licenta.in", "r", stdin);
FILE *fout = freopen("licenta.out", "w", stdout);

const int MAX_N = 10 + 100000;

pair<int,int> A[MAX_N], B[MAX_N];
int k, n, m, N, M;

void readData() {

    scanf("%d ", &k);
    scanf("%d ", &n);
    for(int i = 1; i <= n; ++i) {

        int x, y; scanf("%d %d ", &x, &y);
        if(y >= x + k)
            A[++N] = make_pair(x, y);
    }

    scanf("%d ", &m);
    for(int i = 1; i <= m; ++i) {

        int x, y; scanf("%d %d ", &x, &y);
        if(y >= x + k)
            B[++M] = make_pair(x, y);
    }
    sort(A + 1, A + N + 1);
    sort(B + 1, B + M + 1);
}

int binarySearchB(int val) {

    int left = 1, right = M, mid, sol = 0;
    while(left <= right) {

        mid = (left + right) >> 1;
        if(B[mid].first >= val)
            sol = mid, right = mid - 1;
        else
            left = mid + 1;
    }
    if(!sol)
        return -1;
    return B[sol].first;
}

int binarySearchA(int val) {

    int left = 1, right = N, mid, sol = 0;
    while(left <= right) {

        mid = (left + right) >> 1;
        if(A[mid].first >= val)
            sol = mid, right = mid - 1;
        else
            left = mid + 1;
    }
    if(!sol)
        return -1;
    return A[sol].first;
}


int main() {

    readData();
    if(!N || !M) {

        printf("-1");
        return 0;
    }

    bool posibil = false;
    int x = 2000000001;

    for(int i = 1; i <= N; ++i) {

        int val = binarySearchB(A[i].first);
        if(val != -1 && A[i].second - val >= k) {

            posibil = true;
            if(x > val)
                x = val;
        }
    }

    for(int i = 1; i <= M; ++i) {

        int val = binarySearchA(B[i].first);
        if(val != -1 && B[i].second - val >= k) {

            posibil = true;
            if(x > val)
                x = val;
        }
    }

    if(!posibil)
        printf("-1");
    else
        printf("%d %d", x, x + k);
    return 0;
}
