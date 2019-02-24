/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define inFile  "dreptunghi.in"
#define outFile "dreptunghi.out"

using namespace std;

int main() {

    freopen(inFile, "r", stdin);
    freopen(outFile, "w", stdout);

    int x, y, r;
    long long int ans = 0;
    scanf("%d %d", &x, &y);
    if(x < y)
        swap(x, y);
    while(y) {

        ans += y * (x / y);
        r = x % y;
        x = y, y = r;
    }
    printf("%lld", ans);
    return 0;
}
