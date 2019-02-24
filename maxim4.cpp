#include <fstream>

using namespace std;
ifstream cin("maxim4.in");
ofstream cout("maxim4.out");

int main() {
    int max_value = -1, count = 0;
    int n; cin >> n;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        if(x == max_value) {
            count ++;
        } else if(x > max_value) {
            max_value = x; count = 1;
        }
    }

    cout << max_value << " " << count;
    return 0;
}
