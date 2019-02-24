/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
FILE *fin = freopen("kdist.in", "r", stdin);
FILE *fout = freopen("kdist.out", "w", stdout);

const int MAX_N = 1 + 200000;
const int MAX_INF = 0x3fffffff;
const int bufferDim = 100000;

class inputReader {

private:
        char buffer[bufferDim];
        int pos = 0;

        bool digit(char c) {

            return('0' <= c && c <= '9');
        }
public:

        void getBuffer() {

            fread(buffer, 1, bufferDim, stdin);
            pos = 0;
        }

        void getInt(int &nr) {

            nr = 0;
            while(!digit(buffer[pos]))
                if(++pos == bufferDim)
                    getBuffer();
            while(digit(buffer[pos])) {

                nr = nr * 10 + buffer[pos] - '0';
                if(++pos == bufferDim)
                    getBuffer();
            }
        }
} cin;

/*------------------------*/
vector <int> G[MAX_N]; /* chestii generale */
int color[MAX_N], depth[MAX_N];
int n, k;

/*------------------------*/
int first[MAX_N], currentDepth[2 * MAX_N], list[2 * MAX_N]; /* parcurgere Euler + arbore de intervale */
int sTree[16 * MAX_N];
int listSize;
bool checked[MAX_N];


struct mystruct {
    int node, x, y;
    mystruct(const int &node, const int &x, const int &y) {
        this->node = node; this->x = x; this->y = y;
    }
    bool operator <(const mystruct &other) const {
        return depth[this->node] > depth[other.node];
    }
};

/*------------------------*/
vector <int> colorList[MAX_N]; /* pentru rezolvarea nodurilor de o anumita culoare */
int father[MAX_N], cnt[MAX_N];
vector <mystruct> nodes;
/*------------------------*/


void readData() {
    cin.getBuffer();
    cin.getInt(n); cin.getInt(k);

    for(int i = 1; i < n; ++i) {
        int u, v; cin.getInt(u); cin.getInt(v);
        G[u].push_back(v); G[v].push_back(u);
    }
    for(int i = 1; i <= n; ++i) {
        cin.getInt(color[i]);
    }
}

void eulerianDfs(int node, int level) {
    checked[node] = true;
    depth[node] = level;

    list[++listSize] = node;
    currentDepth[listSize] = level;
    first[node] = listSize;

    colorList[color[node]].push_back(node);

    for(vector <int>::iterator it = G[node].begin(); it != G[node].end(); ++it)
        if(!checked[*it]) {
            eulerianDfs(*it, level + 1);

            list[++listSize] = node;
            currentDepth[listSize] = level;
        }
}

void buildSTree(int node, int left, int right) {
    if(left == right) {
        sTree[node] = left;
        return;
    }

    int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
    buildSTree(leftSon, left, mid);
    buildSTree(rightSon, mid + 1, right);

    if(currentDepth[sTree[leftSon]] <= currentDepth[sTree[rightSon]]) {
        sTree[node] = sTree[leftSon];
    }
    else {
        sTree[node] = sTree[rightSon];
    }
}

int answer, answerDepth;

void query(int node, int left, int right, int first, int last) {
    if(first <= left && right <= last) {
        if(currentDepth[sTree[node]] < answerDepth) {
            answer = list[sTree[node]];
            answerDepth = currentDepth[sTree[node]];
        }
        return;
    }

    int mid = (left + right) >> 1, leftSon = node << 1, rightSon = leftSon + 1;
    if(first <= mid) {
        query(leftSon, left, mid, first, last);
    }
    if(mid < last) {
        query(rightSon, mid + 1, right, first, last);
    }
}

int LCA(int a, int b) {
    int x = first[a], y = first[b];
    if(x > y) {
        swap(x, y);
    }
    answer = answerDepth = MAX_INF;
    query(1, 1, listSize, x, y);

    return answer;
}

int group(int x) {
    if(x != father[x]) {
        father[x] = group(father[x]);
    }
    return father[x];
}

void unite(int x, int y) {
    x = group(x);
    y = group(y);
    cnt[y] += cnt[x];
    cnt[x] = 0;
    father[x] = y;
}

bool cmp(int a, int b) {
    return depth[a] > depth[b];
}

void solveColor(int index) {

    long long answer = 0;
    int count = (int)colorList[index].size();
    if(!count) {
        printf("0\n");
        return;
    }

    for(vector <int>::iterator it = colorList[index].begin(); it != colorList[index].end(); ++it) {
        answer += 1LL * depth[*it] * (count - 1);
    }

    nodes.clear();
    for(int i = 1; i < count; ++i) {
        int node = LCA(colorList[index][i - 1], colorList[index][i]);
        nodes.push_back(mystruct(node, colorList[index][i - 1], colorList[index][i]));
    }

    sort(nodes.begin(), nodes.end());
    for(vector <mystruct>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
        int g1 = group(it->x);
        int g2 = group(it->y);
        answer -= 2LL * depth[it->node] * cnt[g1] * cnt[g2];
        unite(g1, g2);
    }

    printf("%lld\n", answer);
}

int main() {

    readData();
    eulerianDfs(1, 1);
    buildSTree(1, 1, listSize);

    for(int i = 1; i <= n; ++i) {
        father[i] = i;
        cnt[i] = 1;
    }
    for(int i = 1; i <= k; ++i) {
        solveColor(i);
    }
    return 0;
}
