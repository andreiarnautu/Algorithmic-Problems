/**
  *  Worg
  */
#include <cstdio>

using namespace std;
FILE *fin = freopen("buget.in", "r", stdin);
FILE *fout = freopen("buget.out", "w", stdout);

const int MAX_N = 1 + 100000;

long long int v[MAX_N];
long long int b;
int n;


void readData() {

    scanf("%d %lld ", &n, &b);
    for(int i = 1; i <= n; ++i)
        scanf("%lld ", &v[i]);
}

long long int sumUnderValue(long long int val) {

    long long int ret = 0;
    for(int i = 1; i <= n; ++i)
        ret += ((v[i] < val) ? v[i] : val);
    return ret;
}

void binarySearch() {

    long long int sol = 0, left = 0, right = 10000000000, mid;
    long long int wasted;

    while(left <= right) {

        mid = (left + right) >> 1;
        wasted = sumUnderValue(mid);

        if(wasted <= b)
            sol = mid, left = mid + 1;
        else
            right = mid - 1;
    }
    printf("%lld", sol);
}

int main() {

    readData();
    binarySearch();
    return 0;
}
