/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

//FILE *fin = freopen("main.in", "r", stdin); FILE *fout = freopen("main.out", "w", stdout);

const int sigma = 26;
const int kMaxN = 1e5 + 1;

char s[kMaxN];
int v[kMaxN];

long long cnt[sigma], appCount[sigma];

int main() {
    scanf("%s", s); int N = std::strlen(s);
    int K; scanf("%d", &K);

    if(1LL * N * (N + 1) / 2 < K) {
        printf("No such line.\n"); return 0;
    }

    int len = N;
    for(int i = 0; i < N; i++) {
        v[i] = i;
    }

    while(K > 0) {
        memset(cnt, 0, sizeof(cnt)); memset(appCount, 0, sizeof(appCount));

        for(int i = 0; i < len; i++) {
            cnt[s[v[i]] - 'a'] += N - v[i];
            appCount[s[v[i]] - 'a'] ++;
        }

        char ch = 'a';
        for(char c = 'a'; c <= 'z'; c++) {
            if(K <= cnt[c - 'a']) {
                ch = c; break;
            } else {
                K -= cnt[c - 'a'];
            }
        }

        printf("%c", ch);
        K -= appCount[ch - 'a'];

        int newLen = 0;
        for(int i = 0; i < len; i++) {
            if(s[v[i]] == ch && v[i] + 1 < N) {
                v[newLen++] = v[i] + 1;
            }
        }
        len = newLen;
    }
    printf("\n");

	return 0;
}
