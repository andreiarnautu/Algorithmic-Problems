/**
  *  Worg
  */
#include <fstream>

#define dim     50500
#define inFile  "distante.in"
#define outFile "distante.out"

using namespace std;
ifstream cin(inFile);
ofstream cout(outFile);

int dmin[dim];
int n, m, s;

void solveTest() {

    cin >> n >> m >> s;
    for(int i = 1; i <= n; ++i)
        cin >> dmin[i];

    int x, y, z, ok = 1;
    for(int i = 1; i <= m; ++i) {

        cin >> x >> y >> z;
        if(dmin[x] + z < dmin[y] || dmin[y] + z < dmin[x])
            ok = 0;
    }

    cout << ((dmin[s] == 0 && ok) ? "DA\n" : "NU\n");
}

int main() {

    int T;
    for(cin >> T; T; --T)
        solveTest();
    return 0;
}
