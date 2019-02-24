/**
  *  Worg
  */
#include <string>
#include <iostream>

using namespace std;

const string a = "monday";
const string b = "tuesday";
const string c = "wednesday";
const string d = "thursday";
const string e = "friday";
const string f = "saturday";
const string g = "sunday";

int Value(string s) {
    if(s == a) {
        return 1;
    }
    if(s == b) {
        return 2;
    }
    if(s == c) {
        return 3;
    }
    if(s == d) {
        return 4;
    }
    if(s == e) {
        return 5;
    }
    if(s == f) {
        return 6;
    }
    return 7;
}

int main() {
    string A, B; cin >> A >> B;

    int m = Value(A);
    int n = Value(B);

    int k = m + 2, p = m + 3;
    if(k > 7) {
        k -= 7;
    }
    if(p > 7) {
        p -= 7;
    }

    if(m == n || k == n || p == n) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
