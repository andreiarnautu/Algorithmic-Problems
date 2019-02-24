/**
  *  Worg
  */
#include <iostream>

using namespace std;

int n;
int v[1001];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    for(int i = 1; i <= n - 1; i++) {
        if(v[i] != 0 && v[i + 1] != 0) {
            cout << "NU"; return 0;
        }
    }

    cout << "DA";
    return 0;
}
