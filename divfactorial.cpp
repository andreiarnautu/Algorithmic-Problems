/**
  *  Worg
  */
#include <iostream>

using namespace std;

int main() {
    int n;
    long long fact = 1;

    cin >> n;
    for(int i = 2; i <= n; i++) {
        fact *= i;
    }
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        if(fact % x == 0) {
            cout << x << " ";
        }
    }

    return 0;
}
