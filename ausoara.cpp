/**
  *  Worg
  */
#include <cstdio>
#include <vector>

using namespace std;
FILE *fin = freopen("ausoara.in", "r", stdin);
FILE *fout = freopen("ausoara.out", "w", stdout);

const int MAX_N = 1 + 100;
const int MAX_M = 1 + 1000;
const int MAX_VAL = 1 + 1000000;
/*-----------------------*/
int mat[MAX_N][MAX_M];
int len[MAX_N];
int N;
/*-----------------------*/
short int cnt[MAX_VAL];
vector <int> SOL;
/*-----------------------*/

void readData() {
    scanf("%d", &N);
    for(int i = 1; i <= N; ++i) {
        scanf("%d", &len[i]);
        for(int j = 1; j <= len[i]; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void makeCnt() {
    for(int i = 1; i <= N; ++i) {
        for(int j = 1; j <= len[i]; ++j) {
            cnt[mat[i][j]]++;
            while(j < len[i] && mat[i][j] == mat[i][j + 1]) {
                j++;
            }
        }
    }
}

int firstPos(int index, int val) {
    int left = 1, right = len[index], answer = right;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(mat[index][mid] >= val) {
            answer = mid; right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}

int lastPos(int index, int val) {
    int left = 1, right = len[index], answer = left;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(mat[index][mid] <= val) {
            answer = mid; left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return answer;
}

void getSol() {
    for(int i = 1; i < MAX_VAL; ++i) {
        if(cnt[i] == N) {
            int quant = MAX_M;
            for(int j = 1; j <= N; ++j) {
                int A = firstPos(j, i);
                int B = lastPos(j, i);
                quant = min(quant, B - A + 1);
            }
            for(int j = 1; j <= quant; ++j) {
                SOL.push_back(i);
            }
        }
    }
    printf("%d ", (int)SOL.size());
    for(int i = 0; i < (int)SOL.size(); ++i) {
        printf("%d ", SOL[i]);
    }
}

int main() {
    readData();
    makeCnt();
    getSol();
    return 0;
}
