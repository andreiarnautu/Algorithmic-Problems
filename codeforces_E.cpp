/**
  *  Worg
  */
#include <iostream>

using namespace std;

const int kMaxN = 1 + 500;
const int kMaxStep = 50000;

int n;
int a[kMaxN];

bool Try() {
    //  nvm...

}

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int j = 1; j <= kMaxStep; j++) {
        bool result = Try(j);
        if(result) {
            cout << j; return 0;
        }
    }
    return 0;
}
