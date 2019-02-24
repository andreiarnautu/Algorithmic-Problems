/**
  *  Worg
  */
#include <iostream>

using namespace std;

const long long MAX_INF = 1000000000000000;

long long N, M;
long long maxStep, act;
long long X, Y;

long long cmmdc(long long a, long long b) {
    long long r;
    while(b) {
        r = a % b; a = b; b = r;
    }
    return a;
}

inline long long gcd(long long a, long long b, long long &x, long long &y)
{
    if( !b )
    {
        x = 1, y = 0; return a;
    }
    long long x0, y0;
    long long div = gcd(b, a % b, x0, y0);
    x = y0;
    y = x0 - (a / b) * y0;
    return div;

}

long long getGCD(long long value, long long cat, long long state1, long long state2) {
    long long a = N;
    long long b = -M;
    long long x, y;
    long long Div = gcd(a, b, x, y);

    if(value % Div == 0) {
        long long x1 = x * (value / Div);
        long long y1 = y * (value / Div);

        if(x1 < 0 || y1 < 0 || x1 % 2  || y1 % 2 ) {
            return MAX_INF;
        } else {
          //  cout << x1 << " ";
            return (cat + x1 * a) % act;
        }
    } else {
        return MAX_INF;
    }
}

int main() {
    cin >> N >> M;
    maxStep = M * N / cmmdc(M, N);

    if((maxStep / M) % 2 == 1 || (maxStep / N) % 2 == 1) {
        act = maxStep * 2;
    } else {
        act = maxStep;
    }

    int K; cin >> K;



    for(int i = 1; i <= K; i++) {
        cin >> X >> Y;

        long long Ans = MAX_INF;
        Ans = min(Ans, getGCD(Y - X, X, 0, 0));
        Ans = min(Ans, getGCD(2 * M - Y - X, X, 0, 1));
        Ans = min(Ans, getGCD(Y - 2 * N + X, 2 * N - X, 1, 0));
        Ans = min(Ans, getGCD(2 * M - Y - 2 * N + X, 2 * N - X, 1, 1));

       /*cout << getGCD(Y - X, X, 0, 0) << '\n';
        cout << getGCD(2 * M - Y - X, X, 0, 1) << '\n';
        cout << getGCD(Y - 2 * N + X, 2 * N - X, 1, 0) << '\n';
        cout << getGCD(2 * M - Y - 2 * N + X, 2 * N - X, 1, 1) << '\n';*/

        if(Ans >= maxStep) {
            cout << "-1\n";
        } else {
            cout << Ans << '\n';
        }
    }
    return 0;
}
