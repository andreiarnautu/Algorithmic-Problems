/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

int n;
int a[200001];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a + 1, a + n + 1);

    int min_dif = 2000000001, cnt = 0;
    for(int i = 2; i <= n; i++) {
        if(min_dif > a[i] - a[i - 1]) {
            min_dif = a[i] - a[i - 1];
            cnt = 1;
        } else if(min_dif == a[i] - a[i - 1]) {
            cnt ++;
        }
    }

    printf("%d %d\n", min_dif, cnt);
    return 0;
}
