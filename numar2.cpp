/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("numar2.in", "r", stdin);
FILE *fout = freopen("numar2.out", "w", stdout);

const int MAX_N = 1 + 100;
const int MAX_P = 50000;

int a[MAX_N];
int n, m;

int p[MAX_P];
int pos, limit;

void readData() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    limit = m * a[1];
}

void back(int cnt, int index, int prod) {
    if(prod > limit) {
        return;
    }
    else {
        if(cnt % 2 == 1) {
            p[++pos] = prod;
        }
        else {
            p[++pos] = -prod;
        }

        for(int i = index + 1; i <= n; ++i) {
            if(a[i] <= limit / prod) {
                back(cnt + 1, i, prod * a[i]);
            }
        }
    }
}

int countLower(int val) {
    int answer = 0;
    for(int i = 1; i <= pos; ++i) {
        if(p[i] == 0) {
            while(1);
        }
        answer += val / p[i];
    }
    return answer;
}

int binarySearch() {
    int answer = 1, left = 1, right = limit;
    while(left <= right) {
        int mid = (left + right) >> 1;
        if(countLower(mid) >= m) {
            answer = mid; right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return answer;
}

int main() {
    readData();
    for(int i = 1; i <= n; ++i) {
        back(1, i, a[i]);
    }
    printf("%d", binarySearch());
    return 0;
}
