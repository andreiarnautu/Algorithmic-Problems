/**
  *  Worg
  */
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
ifstream cin("lant.in");
ofstream cout("lant.out");

const int MAX_C = 1 + 150;
const int MAX_LEN = 35;
const int MAX_INF = 0x3fffffff;

/*-------------------*/
string word[MAX_C];
int k, wordCount;
/*-------------------*/
int dp[MAX_LEN][MAX_LEN];
/*-------------------*/
vector <int> G[MAX_C];
int cnt[MAX_C];
/*-------------------*/

bool letter(char c) {
    return ('a' <= c && c <= 'z');
}

void readData() {
    cin >> k;
    string current;
    while(cin >> current) {
        int len = (int)current.size(), i = 0;
        while(i < len) {
            if(letter(current[i])) {
                string newWord;
                newWord += current[i];
                for(++i; i < len && letter(current[i]); ++i) {
                    newWord += current[i];
                }

                bool gasit = false;
                for(int i = 1; i <= wordCount; ++i) {
                    if(word[i] == newWord) {
                        gasit = true;
                    }
                }
                if(!gasit) {
                    word[++wordCount] = newWord;
                }
            }
            else {
                i++;
            }
        }
    }
}

int getDegree(const string &A, const string &B) {
    int n = (int)A.size();
    int m = (int)B.size();

    for(int i = 0; i < MAX_LEN; ++i) {
        for(int j = 0; j < MAX_LEN; ++j) {
            dp[i][j] = MAX_INF;
        }
    }

    for(int i = 0; i <= n; ++i) {
        dp[i][m] = n - i;
    }
    for(int j = 0; j <= m; ++j) {
        dp[n][j] = m - j;
    }

    for(int i = n - 1; i >= 0; --i) {
        for(int j = m - 1; j >= 0; --j) {
            if(A[i] == B[j]) {
                dp[i][j] = min(dp[i + 1][j + 1], min(dp[i + 1][j] + 1, dp[i][j + 1] + 1));
            }
            else {
                dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) + 1;
            }
        }
    }
    return dp[0][0];
}

void makeGraph() {
    for(int i = 1; i <= wordCount; ++i) {
        for(int j = i + 1; j <= wordCount; ++j) {
            if(getDegree(word[i], word[j]) <= k) {
                G[i].push_back(j);
            }
        }
    }
}

void treeDP(int node) {
    if(G[node].size() == 0) {
        cnt[node] = 1;
    }
    else {
        for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
            if(!cnt[*it]) {
                treeDP(*it);
            }
            cnt[node] += cnt[*it];
        }
    }
}

int main() {

    readData();
    makeGraph();
    treeDP(1);
    cout << cnt[1];
    return 0;
}
