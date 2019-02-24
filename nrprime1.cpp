#include <iostream>

using namespace std;

int main() {
    int n, m; cin >> n >> m;
    int sol = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int x; cin >> x;
            if(j % 2 == 1) {
                if(x >= 2) {
                    bool ok = true;
                    for(int k = 2; k * k <= x; k++) {
                        if(x % k == 0) {
                            ok = false; break;
                        }
                    }
                    if(ok) {
                        sol ++;
                    }
                }
            }
        }
    }
    cout << sol;
    return 0;
}
