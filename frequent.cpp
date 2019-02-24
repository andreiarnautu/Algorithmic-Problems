/**
  *  Worg
  */
#include <cmath>
#include <stack>
#include <cstdio>
#include <cstring>
#include <utility>
#include <algorithm>

FILE *fin = freopen("frequent.in", "r", stdin); FILE *fout = freopen("frequent.out", "w", stdout);

const int kMaxN = (200000 + 5) << 1;
const int kMaxLog = 20;
int ZERO = 0;

/*------- Input data --------*/
int K, N;
char word[kMaxN], S[kMaxN];
/*------- Suffix array --------*/
int originalString[kMaxN];

int idx[kMaxLog][kMaxN];
int count[kMaxN], id1[kMaxN], id2[kMaxN], suffix[kMaxN], where[kMaxN];

int lcp[kMaxN];
/*------- Solution --------*/
std::stack<int > stack;
int left[kMaxN], prev[kMaxN];

int solution[kMaxN];
int fenwick[kMaxN];
/*------- --------*/

int lsb(int x) {
    return x & (-x);
}

void UpdateFenwick(int index, int value) {
    for(int i = index + 1; i < kMaxN; i += lsb(i)) {
        fenwick[i] += value;
    }
}

int QueryFenwick(int index) {
    int answer = 0;
    for(int i = index + 1; i > 0; i -= lsb(i)) {
        answer += fenwick[i];
    }
    return answer;
}

void ReadInput() {
    scanf("%d", &K);
    for(int i = 0; i < K; i++) {
        scanf("%s", word);
        for(int j = 0, length = std::strlen(word); j < length; j++) {
            originalString[N] = i;
            S[N ++] = word[j];
        }
        S[N ++] = '$';
    }
}

int& Index(int i, int j) {
    if(j < kMaxN) {
        return idx[i][j];
    } else {
        return ZERO;
    }
}

void BuildSuffixArray() {
    for(int i = 0; i < N; i++) {
        count[(int)S[i]] ++;
    }
    for(int i = 0, j = 0; i < 256; i++) {
        if(count[i] != 0) {
            count[i] = j ++;
        }
    }
    for(int i = 0; i < N; i++) {
        Index(0, i) = count[(int)S[i]];
    }

    for(int j = 1, L = 1; j < kMaxLog; j++, L <<= 1) {
        //  2nd halves
        for(int i = 0; i < N; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < N; i++) {
            count[Index(j - 1, i + L)] ++;
        }
        for(int i = 1; i < N; i++) {
            count[i] += count[i - 1];
        }
        for(int i = N - 1; i >= 0; i--) {
            id1[-- count[Index(j - 1, i + L)]] = i;
        }

        //  1st halves
        for(int i = 0; i < N; i++) {
            count[i] = 0;
        }
        for(int i = 0; i < N; i++) {
            count[Index(j - 1, i)] ++;
        }
        for(int i = 1; i < N; i++) {
            count[i] += count[i - 1];
        }
        for(int i = N - 1; i >= 0; i--) {
            id2[-- count[Index(j - 1, id1[i])]] = id1[i];
        }

        //  Unite halves
        Index(j, id2[0]) = 0;
        for(int i = 1; i < N; i++) {
            if(Index(j - 1, id2[i]) == Index(j - 1, id2[i - 1]) && Index(j - 1, id2[i] + L) == Index(j - 1, id2[i - 1] + L)) {
                Index(j, id2[i]) = Index(j, id2[i - 1]);
            } else {
                Index(j, id2[i]) = Index(j, id2[i - 1]) + 1;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        suffix[Index(kMaxLog - 1, i)] = i;
        where[i] = Index(kMaxLog - 1, i);
    }
}

int Next(int k) {
    return (k == 0) ? 0 : k - 1;
}

void BuildLCP() {
    //  Kasai's algorithm
    for(int i = 0, k = 0; i < N; i++, k = Next(k)) {
        if(where[i] == N - 1) {
            k = 0;
        } else {
            int j = suffix[where[i] + 1];
            while(i + k < N && j + k < N && S[i + k] == S[j + k] && S[i + k] != '$') {  // && S[i + k] != '$'
                k ++;
            }
        }
        lcp[where[i]] = k;
    }
    for(int i = N - 1; i > 0; i--) {
        lcp[i] = lcp[i - 1];
    }
}

int GetDistinct(int left, int right) {
    return QueryFenwick(right) - QueryFenwick(left - 1);
}

void BuildSolution() {
    stack.push(0);

    for(int i = 0; i <= N; i++) {
        prev[i] = -1;
    }

    for(int i = 1; i <= N; i++) {
        while(!stack.empty() && lcp[i] < lcp[stack.top()]) {
            int distinctCount = GetDistinct(left[stack.top()], i - 1);

            solution[distinctCount] = std::max(solution[distinctCount], lcp[stack.top()]);

            stack.pop();
        }

        if(!stack.empty() && lcp[stack.top()] == lcp[i]) {
            left[i] = left[stack.top()];
        } else {
            left[i] = stack.top();
        }

        stack.push(i);

        if(prev[originalString[suffix[i]]] != -1) {
            UpdateFenwick(prev[originalString[suffix[i]]], -1);
        }
        UpdateFenwick(i, 1);
        prev[originalString[suffix[i]]] = i;
    }
}

void WriteOutput() {
    for(int i = K - 1; i >= 2; i--) {
        solution[i] = std::max(solution[i], solution[i + 1]);
    }

    for(int i = 2; i <= K; i++) {
        printf("%d\n", solution[i]);
    }
}

int main() {
    ReadInput();
    BuildSuffixArray();
    BuildLCP();
    BuildSolution();
    WriteOutput();
    return 0;
}
