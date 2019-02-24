/**
  *  Worg
  */
#include <fstream>

using namespace std;
ifstream cin("nraparitii.in");
ofstream cout("nraparitii.out");

int n;
int v[101];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    int sol = 0;
    for(int i = 1; i <= n; i++) {
        if(v[i] == v[n]) {
            sol ++;
        }
    }

    cout << sol;
    return 0;
}
