/**
  *  Worg
  */
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <algorithm>

#define lsb(i) (i & (-i))

using namespace std;
FILE *fin = freopen("klsecv.in", "r", stdin);
FILE *fout = freopen("klsecv.out", "w", stdout);

const int MAX_N = 1 + 20000;
const int MAX_Q = 1 + 20000;
const int MAX_LOG = 1 + 15;
int Zero = 0;

/*-------- Input data --------*/
struct Query {
    int L, K, index;

    Query(const int &L, const int &K, const int &index) {
        this->L = L; this->K = K; this->index = index;
    }
    bool operator <(const Query &other) const {
        if(this->L != other.L) {
            return this->L < other.L;
        } else {
            return this->index < other.index;
        }
    }
};

int T;
int N, Q;
char S[MAX_N];
vector< Query > Queries;
/*-------- Suffix Arrays --------*/
int Index[MAX_LOG][MAX_N];
int Count[MAX_N], id1[MAX_N], id2[MAX_N], trueID[MAX_N];
/*-------- AIB --------*/
int AIB[MAX_N];
/*-------- Solution --------*/
int queryAnswer[MAX_Q];
/*-------- --------*/

void readInput() {
    scanf("%s", S);
    N = strlen(S);
    S[N ++] = '$';
    S[N] = 0;
    scanf("%d", &Q);
    for(int i = 1; i <= Q; i++) {
        int L, K;
        scanf("%d%d", &L, &K);
        Queries.push_back(Query(L, K, i));
    }
    sort(Queries.begin(), Queries.end());
    reverse(Queries.begin(), Queries.end());
}

int& index(const int &i, const int &j) {
    if(j < MAX_N) {
        return Index[i][j];
    } else {
        return Zero;
    }
}

void buildSuffixArrays() {
    for(int i = 0; i < N; i++) {
        Count[i] = 0;
    }
    for(int i = 0; i < N; i++) {
        Count[(int)S[i]] ++;
    }
    for(int i = 0, j = 0; i < 256; i++) {
        if(Count[i]) {
            Count[i] = j++;
        }
    }
    for(int i = 0; i < N; i++) {
        index(0, i) = Count[(int)S[i]];
    }

    for(int j = 1, L = 1; j < MAX_LOG; j++, L <<= 1) {
        /* construim id1 */
        for(int i = 0; i < N; i++) {
            Count[i] = 0;
        }
        for(int i = 0; i < N; i++) {
            Count[index(j - 1, i + L)] ++;
        }
        for(int i = 1; i < N; i++) {
            Count[i] += Count[i - 1];
        }
        for(int i = N - 1; i >= 0; i--) {
            id1[--Count[index(j - 1, i + L)]] = i;
        }
        /* construim id2 */
        for(int i = 0; i < N; i++) {
            Count[i] = 0;
        }
        for(int i = 0; i < N; i++) {
            Count[index(j - 1, i)] ++;
        }
        for(int i = 1; i < N; i++) {
            Count[i] += Count[i - 1];
        }
        for(int i = N - 1; i >= 0; i--) {
            id2[--Count[index(j - 1, id1[i])]] = id1[i];
        }

        index(j, id2[0]) = 0;
        for(int i = 1; i < N; i++) {
            if(index(j - 1, id2[i]) == index(j - 1, id2[i - 1]) &&
                        index(j - 1, id2[i] + L) == index(j - 1, id2[i - 1] + L)) {
                index(j, id2[i]) = index(j, id2[i - 1]);
            } else {
                index(j, id2[i]) = index(j, id2[i - 1]) + 1;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        id1[index(MAX_LOG - 1, i)] = i;
        trueID[i] = index(MAX_LOG - 1, i);
    }
}

void testSA() {
    for(int i = 0; i < N; i++) {
        printf("%s\n", S + id1[i]);
    }
   /* for(int i = 0; i < N; i++) {
        printf("%d %d\n", i, trueID[i]);
    }
    printf("\n");*/
}

void clearData() {
    Queries.clear();
    for(int j = 0; j < MAX_LOG; j++) {
        for(int i = 0; i < MAX_N; i++) {
            Index[j][i] = 0;
        }
    }

    for(int i = 0; i < MAX_N; i++) {
        Count[i] = id1[i] = id2[i] = trueID[i] = AIB[i] = 0;
    }
}

void aibUpdate(int pos) {
    if(!pos) {return;}
    for(int i = pos; i < N; i += lsb(i)) {
        AIB[i] ++;
    }
}

int aibQuery(int pos) {
    if(!pos) {return 0;}
    int Answer = 0;
    for(int i = pos; i > 0; i -= lsb(i)) {
        Answer += AIB[i];
    }
    return Answer;
}

int binarySearch(int K) {
    int left = 1, right = N - 1, Answer = 1;

    while(left <= right) {
        int mid = (left + right) >> 1;
        if(aibQuery(mid) >= K) {
            Answer = mid; right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return Answer;
}

void answerQueries() {
    int where = 0;
    for(Query query : Queries) {
        if(N - query.L > where) {
            for(; where < N - query.L; where++) {
                aibUpdate(trueID[where]);
               // printf("%d; ", trueID[where]);
            }
        }
        queryAnswer[query.index] = id1[binarySearch(query.K)] + 1;
    }
    for(int i = 1; i <= Q; i++) {
        printf("%d\n", queryAnswer[i]);
    }
}

int main() {
    int T; scanf("%d", &T);
    for(; T; T--) {
        readInput();
        buildSuffixArrays();
        //testSA();
        answerQueries();
        clearData();
    }

    return 0;
}
