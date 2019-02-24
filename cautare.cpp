/**
  *  Worg
  */
#include <iostream>

using namespace std;

int x[1001], y;
int n, m;

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    cin >> m;
    for(int i = 1; i <= m; i++) {
        cin >> y;
        bool ok = false;
        for(int j = 1; j <= n; j++) {
            if(x[j] == y) {
                ok = true; break;
            }
        }
        cout << ok << " ";
    }
    return 0;
}
