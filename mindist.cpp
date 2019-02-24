/**
  *  Worg
  */
#include <cstdio>
#include <algorithm>

#define leftSon (node << 1)
#define rightSon ((node << 1) + 1)

using namespace std;
FILE *fin = freopen("mindist.in", "r", stdin);
FILE *fout = freopen("mindist.out", "w", stdout);

const int max_N = 1 + 50000;
const int max_C = 1 + 50000;
const int INF = 0x3fffffff;

struct DSTree {
    DSTree *left, *right;
    int minSum, maxSum, minDif, maxDif;

    DSTree() {
        left = right = NULL;
        minSum = minDif = INF;
        maxSum = maxDif = -INF;
    }
};

DSTree *root[max_N * 4], *auxNode;

void updateNode(DSTree *to, DSTree *from) {

    if(from == NULL) {return;}

    to->minSum = min(to->minSum, from->minSum);
    to->minDif = min(to->minDif, from->minDif);
    to->maxDif = max(to->maxDif, from->maxDif);
    to->maxSum = max(to->maxSum, from->maxSum);
}

void insertDSTree(DSTree *node, int left, int right, int x, int y) {
    if(left == right) {
        node->minSum = min(node->minSum, x + y);
        node->maxSum = max(node->maxSum, x + y);
        node->minDif = min(node->minDif, x - y);
        node->maxDif = max(node->maxDif, x - y);

    } else {
        int mid = (left + right) >> 1;

        if(y <= mid) {
            if(node->left == NULL) {
                node->left = new DSTree;
            }

            insertDSTree(node->left, left, mid, x, y);

        } else {
            if(node->right == NULL) {
                node->right = new DSTree;
            }

            insertDSTree(node->right, mid + 1, right, x, y);
            updateNode(node, node->right);
        }
        updateNode(node, node->left);
        updateNode(node, node->right);
    }
}

void insertSTree(int node, int left, int right, int x, int y) {
    insertDSTree(root[node], 1, max_C, x, y);

    if(left != right) {
        int mid = (left + right) >> 1;

        if(x <= mid) {
            insertSTree(leftSon, left, mid, x, y);
        } else {
            insertSTree(rightSon, mid + 1, right, x, y);
        }
    }
}

void queryDSTree(DSTree *node, int left, int right, int ymin, int ymax) {
    if(ymin <= left && right <= ymax) { /* interval complet, facem update */
        updateNode(auxNode, node);
    } else { /* mergem mai departe */
        int mid = (left + right) >> 1;

        if(ymin <= mid && node->left != NULL) {
            queryDSTree(node->left, left, mid, ymin, ymax);
        }
        if(mid < ymax && node->right != NULL) {
            queryDSTree(node->right, mid + 1, right, ymin, ymax);
        }
    }
}

void querySTree(int node, int left, int right, int xmin, int xmax, int ymin, int ymax) {
    if(xmin <= left && right <= xmax) {
        queryDSTree(root[node], 1, max_C, ymin, ymax);
    } else {
        int mid = (left + right) >> 1;

        if(xmin <= mid) {
            querySTree(leftSon, left, mid, xmin, xmax, ymin, ymax);
        }
        if(mid < xmax) {
            querySTree(rightSon, mid + 1, right, xmin, xmax, ymin, ymax);
        }
    }
}

void Initialize() {
    for(int i = 0; i < 4 * max_C; i++) {
        root[i] = new DSTree;
    }
}

void solveQueries(int queryCount) {
    for(int i = 1; i <= queryCount; i++) {
        int x, y; scanf("%d%d", &x, &y);
        int Answer = INF;

        /** cadranul 1 **/
        auxNode = new DSTree;
        querySTree(1, 1, max_C, x, max_C, y, max_C);
        if(auxNode->minSum != INF) {
            Answer = min(Answer, auxNode->minSum - x - y);
        }
        delete auxNode;

        /** cadranul 2 **/
        auxNode = new DSTree;
        querySTree(1, 1, max_C, 1, x, y, max_C);
        if(auxNode->maxDif != -INF) {
            Answer = min(Answer, x - y - auxNode->maxDif);
        }
        delete auxNode;

        /** cadranul 3 **/
        auxNode = new DSTree;
        querySTree(1, 1, max_C, 1, x, 1, y);
        if(auxNode->maxSum != -INF) {
            Answer = min(Answer, x + y - auxNode->maxSum);
        }
        delete auxNode;

        /** cadranul 4 **/
        auxNode = new DSTree;
        querySTree(1, 1, max_C, x, max_C, 1, y);
        if(auxNode->minDif != INF) {
            Answer = min(Answer, auxNode->minDif - x + y);
        }

        insertSTree(1, 1, max_C, x, y);

        if(Answer == INF) {
            Answer = 0;
        }
        printf("%d\n", Answer);
    }
}

int main() {
    int N; scanf("%d", &N);
    Initialize();
    solveQueries(N);
    return 0;
}
