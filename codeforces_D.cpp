/**
  *  Worg
  */
#include <string>
#include <cstring>
#include <iostream>

using namespace std;
//ifstream cin("main.in");
//ofstream cout("main.out");

long long int N;
int queries;

long long int x;
int len;
char s[100002];

long long int root;


void Simulate(long long int x, char *cursor) {
    if(*cursor == '\0') {
        cout << x << '\n';
    } else if(*cursor == 'U') {
        if(x == root) {
            Simulate(x, cursor + 1);
        } else {
            long long int lsb = x & (-x);
            long long C1 = x - lsb;
            long long lsb1 = C1 & (-C1);
            if(lsb1 / lsb == 2) {
                Simulate(x - lsb, cursor + 1);
            } else {
                Simulate(x + lsb, cursor + 1);
            }
        }
    } else if(*cursor == 'L') {
        long long int lsb = x & (-x);
        if(lsb == 1) {
            Simulate(x, cursor + 1);
        } else {
            Simulate(x - lsb / 2, cursor + 1);
        }
    } else if(*cursor == 'R') {
        long long int lsb = x & (-x);
        if(lsb == 1) {
            Simulate(x, cursor + 1);
        } else {
            Simulate(x + lsb / 2, cursor + 1);
        }
    }
}

int main() {
    cin >> N >> queries;
    root = (N + 1) / 2;

    for(int i = 1; i <= queries; i++) {
        cin >> x;
        cin >> s;
        Simulate(x, s);
    }

    return 0;
}
