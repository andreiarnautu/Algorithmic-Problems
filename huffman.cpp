/**
  *  Worg
  */
#include <cstdio>
#include <deque>

using namespace std;
FILE *fin = freopen("huffman.in", "r", stdin);
FILE *fout = freopen("huffman.out", "w", stdout);

const int MAX_N = 1 + 1000000;
const int bufferDim = 1000000;

/*---------------------------------*/

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

struct Node {
public:

    int leftSon, rightSon;
    int index; /* precisely, this node reffers to V[index] */
    long long weight; /* the subtree's total weight */

    Node() {
        this->leftSon = this->rightSon = this->index = 0;
    }
    Node(const int index, const int weight) {
        this->index = index; this->weight = weight;
    }
    Node(const int leftSon, const int rightSon, const int index, const int weight) {
        this->leftSon = leftSon; this->rightSon = rightSon; this->index = index; this->weight = weight;
    }
};

Node nodes[MAX_N * 2];
int currentIndex;

int V[MAX_N * 2];
int N;
/*---------------------------------*/
deque< int > specificNodes, regularNodes;
pair< int, long long > SOL[MAX_N];
long long totalLength;
/*---------------------------------*/

void readData() {
    cin.getBuffer();
    cin.getInt(N);
    for(int i = 1; i <= N; i++) {
        cin.getInt(V[i]);
        nodes[i] = Node(i, V[i]);
        specificNodes.push_back(i);
    }
}

void makeFather(int u, int v) {
    currentIndex++;
    nodes[currentIndex] = Node(u, v, 0, nodes[u].weight + nodes[v].weight);
    regularNodes.push_back(currentIndex); /* we add the current node to the end of the regularNodes list */
    V[currentIndex] = V[u] + V[v];
}

void buildTree() {
    while((int)specificNodes.size() + (int)regularNodes.size() > 1) {
        int u, v;

        if((int)regularNodes.size() > 1 && (((int)specificNodes.size() > 0 && V[regularNodes[1]] < V[specificNodes[0]])
                                            || specificNodes.size() == 0)) {
            u = regularNodes[0]; v = regularNodes[1];
            regularNodes.pop_front(); regularNodes.pop_front();
        } else if((int)specificNodes.size() > 1 && (((int)regularNodes.size() > 0 && V[specificNodes[1]] < V[regularNodes[0]])
                                                    || regularNodes.size() == 0)) {
            u = specificNodes[0]; v = specificNodes[1];
            specificNodes.pop_front(); specificNodes.pop_front();
        } else {
            u = specificNodes[0]; v = regularNodes[0];
            regularNodes.pop_front(); specificNodes.pop_front();
        }

        makeFather(u, v);
    }

    if(!specificNodes.empty()) {
        makeFather(currentIndex, specificNodes[0]);
        specificNodes.pop_front();
    }
}

void DFS(int node = currentIndex, int length = 0, long long val = 0) {
    if(nodes[node].index != 0) {
        SOL[nodes[node].index] = make_pair(length, val);
        totalLength += 1LL * length * V[nodes[node].index];
    } else {
        DFS(nodes[node].leftSon, length + 1, val * 2);
        DFS(nodes[node].rightSon, length + 1, val * 2 + 1);
    }
}

void writeData() {
    printf("%lld\n", totalLength);
    for(int i = 1; i <= N; ++i) {
        printf("%d %lld\n", SOL[i].first, SOL[i].second);
    }
}

int main() {
    readData();
    currentIndex = N;
    buildTree();
    DFS();
    writeData();
}
