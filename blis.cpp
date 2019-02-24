/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("blis.in", "r", stdin);
FILE *fout = freopen("blis.out", "w", stdout);

const int MAX_LEN = 1 + 100000;
const int MAX_INF = 0x3fffffff;

char T[MAX_LEN];
int k, len;

int dp[MAX_LEN], dpPos;
vector < pair<int,int> > update[MAX_LEN];

void readData() {
    scanf("%d", &k);
    scanf("%s", T + 1);
    len = strlen(T + 1);
}

void taskOne() {
    int answer = 0, current = 0, i;
    for(i = 1; i <= min(len, k); ++i) {
        current = (current << 1) + T[i] - '0';
    }
    answer = current;

    for(; i <= len; ++i) {
        current = (current << 1) + T[i] - '0';
        current -= (T[i - k] - '0') << k;
        answer = max(answer, current);
    }
    printf("%d\n", answer);
}

void taskTwo() {
    for(int i = 1; i <= len; ++i) {
        dp[i] = MAX_INF;
    }

    for(int i = 1; i <= len; ++i) {
        int current = 0, limit = min(len, i + k - 1);
        for(int j = i; j <= limit; ++j) {
            current = (current << 1) + T[j] - '0';
            int left = 1, right = dpPos, sol = 1;

            if(current > dp[dpPos]) {
                update[j].push_back(make_pair(dpPos + 1, current));
                continue;
            }

            while(left <= right) {
                int mid = (left + right) >> 1;
                if(dp[mid] < current) {
                    left = mid + 1;
                    sol = mid;
                }
                else {
                    right = mid - 1;
                }
            }
            if(dp[sol + 1] > current) {
                update[j].push_back(make_pair(sol + 1, current));
            }
        }
        for(vector < pair<int,int> >::iterator it = update[i].begin(); it != update[i].end(); ++it) {
            if(dp[it->first] > it->second) {
                dp[it->first] = it->second;
                dpPos = max(dpPos, it->first);
            }
        }
       /* for(int j = 1; j <= dpPos; ++j) {
            printf("%d ", dp[j]);
        }
        printf("\n");*/
    }
    printf("%d", dpPos - 1);
}

int main() {
    readData();
    taskOne();
    taskTwo();
}
