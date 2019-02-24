/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
FILE *fin = freopen("bete.in", "r", stdin);
FILE *fout = freopen("bete.out", "w", stdout);

const int MAX_N = 100, MAX_S = 10000;

bool dp[1 + MAX_S];
int stickLen[1 + MAX_N], before[1 + MAX_S];
int stickCount, totalSum, currentSum;

vector <int> sol;

void readData() {

    scanf("%d%d", &stickCount, &totalSum);
    for(int i = 1; i <= stickCount; ++i)
        scanf("%d", &stickLen[i]);
}

void updateDp(int index) {

    for(int i = min(currentSum, totalSum - stickLen[index]); i >= 0; --i)
        if(dp[i] && !dp[i + stickLen[index]]) {

            dp[i + stickLen[index]] = true;
            before[i + stickLen[index]] = index;
        }

    currentSum += stickLen[index];
}

int main() {

    readData();
    dp[0] = true;
    for(int i = 1; i <= stickCount; ++i)
        updateDp(i);

    if(dp[totalSum]) {

        printf("DA\n");
        int pos = totalSum;
        while(pos != 0) {

            sol.push_back(before[pos]);
            pos -= stickLen[before[pos]];
        }

        printf("%d\n", (int)sol.size());
        for(int i = (int)sol.size() - 1; i >= 0; --i)
            printf("%d ", sol[i]);
    }
    else  {
        printf("NU");
    }
    return 0;
}
