/**
  *  Worg
  */
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 11000;

int N;
long long C;
long long P[MAX_N];
long long S[MAX_N];
long long Mars[MAX_N];

void readData() {
    cin >> N >> C;
    for(int i = 1; i <= N; i++) {
        cin >> P[i];
    }
    for(int i = 1; i <= N; i++) {
        cin >> S[i];
    }
}

int main() {
    readData();

    long long Solution = 0;
    for(int i = 1; i <= N; i++) {
        Mars[i] += Mars[i - 1];
        P[i] += Mars[i];

        long long Chosen = min(S[i], P[i]);
        Solution += Chosen;
        P[i] -= Chosen;

        if(C) {
            long long dist = P[i] / C;
            if(dist > N) {
                dist = N;
            }
            Mars[i + 1] += C;
            Mars[i + dist + 1] -= C;

            long long Remained = P[i] - C * dist;
            P[i + dist + 1] += Remained;
        }
    }

    cout << Solution;
    return 0;
}
