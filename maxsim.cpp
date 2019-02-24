/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("maxsim.in");
ofstream cout("maxsim.out");

int n;
int v[1001];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    int stanga, dreapta;
    if(n % 2 == 1) {
        stanga = n / 2; dreapta = stanga + 2;
    } else {
        stanga = n / 2; dreapta = stanga + 1;
    }

    int max_sum = -1, i, j;
    while(stanga >= 1) {
        if(v[stanga] + v[dreapta] >= max_sum) {
            max_sum = v[stanga] + v[dreapta];
            i = stanga; j = dreapta;
        }
        stanga --; dreapta ++;
    }

    cout << max_sum << " " << i << " " << j;
    return 0;
}
