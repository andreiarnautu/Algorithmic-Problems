/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("interclasare.in", "r", stdin);
FILE *fout = freopen("interclasare.out", "w", stdout);

const int MAX_N = 1 + 10000;
const int MAX_INF = 0x3fffffff;

/*---------------------*/
int A[MAX_N], B[MAX_N];
int N, M;
/*---------------------*/
int dp_1[MAX_N], dp_2[MAX_N], before_1[MAX_N], before_2[MAX_N], list_1[MAX_N], list_2[MAX_N];
int limit_1, limit_2, size_1, size_2;
/*---------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &M);
    for(int i = 1; i <= M; i++) {
        scanf("%d", &B[i]);
    }
}

void solveDP(int n, int *dp, int *v, int *before, int &limit) {
    for(int i = 1; i <= n; i++) {
        dp[i] = 0;
    }

    limit = 1;
    dp[1] = 1;

    for(int i = 2; i <= n; i++) {
        if(v[i] >= v[dp[limit]]) {
            before[i] = dp[limit];
            dp[++limit] = i;
        } else {
            int left = 1, right = limit, answer = 1;
            while(left <= right) {
                int mid = (left + right) >> 1;
                if(v[i] <= v[dp[mid]]) {
                    answer = mid; right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            if(v[dp[answer]] >= v[i]) {
                dp[answer] = i;
                before[i] = dp[answer - 1];
            }
        }
    }

}

void writeSol() {
    int answer = 0;
    for(int i = 1; i <= N; i++) {
        if(dp_1[i] != 0) {
            answer++;
        } else {
            break;
        }
    }

    for(int i = 1; i <= M; i++) {
        if(dp_2[i] != 0) {
            answer++;
        } else {
            break;
        }
    }

    printf("%d\n", answer);
}

void getList(int *list, int *before, int pos, int &size) {
    while(pos != 0) {
        list[++size] = pos;
        pos = before[pos];
    }
}

void writeSequence(int *v, int first, int last) {
    for(int i = first; i <= last; i++) {
        printf("%d ", v[i]);
    }
}

void writeArray() {
    int pos_1 = size_1, last_1 = 0;
    int pos_2 = size_2, last_2 = 0;

    while(pos_1 && pos_2) {
        if(A[list_1[pos_1]] <= B[list_2[pos_2]]) {
            writeSequence(A, last_1 + 1, list_1[pos_1]);
            last_1 = list_1[pos_1];
            pos_1--;
        } else {
            writeSequence(B, last_2 + 1, list_2[pos_2]);
            last_2 = list_2[pos_2];
            pos_2--;
        }
    }

    writeSequence(A, last_1 + 1, N);
    writeSequence(B, last_2 + 1, M);
}

int main() {
    readData();
    solveDP(N, dp_1, A, before_1, limit_1);
    solveDP(M, dp_2, B, before_2, limit_2);
    writeSol();
    getList(list_1, before_1, dp_1[limit_1], size_1);
    getList(list_2, before_2, dp_2[limit_2], size_2);
    writeArray();
    return 0;
}
