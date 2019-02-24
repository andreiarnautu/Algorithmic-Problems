/**
  *  Worg
  */
#include <cstdio>

using namespace std;
//FILE *fin = freopen("main.in", "r", stdin);
//FILE *fout = freopen("main.out", "w", stdout);

int a[101];
int v[101];
int n, k;

int main() {
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= k; i++) {
        scanf("%d", &a[i]);
    }
    for(int i = 1; i <= n; i++) {
        v[i] = i;
    }

    int leader = 1;
    for(int i = 1; i <= k; i++) {
        int next = (leader + a[i] % n);
        if(next > n) next -= n;
        printf("%d ", v[next]);
        for(int j = next; j + 1 <= n; j++) {
            v[j] = v[j + 1];
        }
        n--;
        /*for(int j = 1; j <= n; j++) {
            printf("%d ", v[j]);
        }*/
        leader = next;
        if(leader > n) {
            leader = 1;
        }
        //printf("starting %d\n", leader);
    }
    return 0;
}
