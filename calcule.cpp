/**
  *  Worg
  */
#include <cstdio>

FILE *fin = freopen("calcule.in", "r", stdin);
FILE *fout = freopen("calcule.out", "w", stdout);

const int MAX_N = 100000, MAX_K = 50000, MOD = 20011;

int count[1 + MAX_K], lastElem[1 + MAX_N + 1];
int n, k;

int secvCount, substrCount;

int binarySearch(int value) {

    int left = 1, right = substrCount + 1, mid, ret = substrCount + 1;

    while(left <= right) {

        mid = (left + right) >> 1;
        if(lastElem[mid] >= value) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
            ret = mid;
        }
    }
    return ret;
}

int main() {

    scanf("%d%d", &n, &k);

    int elem, sum = 0;
    for(int i = 1; i <= n; ++i) {

        scanf("%d", &elem);
        sum = (sum + elem) % k;
        secvCount = (secvCount + count[sum]) % MOD;
        if(!sum)
            secvCount = (secvCount + 1) % MOD;
        count[sum]++;

        int pos = binarySearch(elem);
        if(pos == substrCount + 1) {
            lastElem[++substrCount] = elem;
        }
        else {
            lastElem[pos] = elem;
        }
    }

    printf("%d\n%d\n", substrCount, secvCount);
    return 0;
}
