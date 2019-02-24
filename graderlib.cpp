#ifndef __GRADERLIB_CPP__
#define __GRADERLIB_CPP__

#include "graderlib.h"

#include "icc.h"

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

// just set this value to false to stop debug dumps.
const bool DEBUG_MODE = true;
#define DEBUG(...) do { if(DEBUG_MODE) {__VA_ARGS__;} } while(0)

// Test Data
int n, current_edge, num_steps;
vector<pair<int, int> > edges_order;

void finish(const string& message) {
    fprintf(stderr, "%s\n", message.c_str());

    ofstream fout("icc.out");
    fout << message << '\n';
    fout.close();

    exit(0);
}

// implementation sugar. if !condition -> setScore(message)
void expect(bool condition, const string& message) {
    if (not condition) {
        finish(message);
    }
}

extern "C" {

// implementation of query function called by you.
int query(int a, int b, int *A, int *B) {
    num_steps += 1;

    DEBUG({
        fprintf(stderr, "[Query]\n{");
        for (int i = 0; i < a; i += 1) { fprintf(stderr, "%d%s", A[i], ((i + 1 != a) ? (",\t") : (""))); }
        fprintf(stderr, "}\n{");
        for (int i = 0; i < b; i += 1) { fprintf(stderr, "%d%s", B[i], ((i + 1 != b) ? (",\t") : (""))); }
        fprintf(stderr, "}\n\n");
    });

    vector<int> left(n + 1, 0), right(n + 1, 0);

    for (int i = 0; i < a; i += 1) {
        // sanity check
        expect(1 <= A[i] and A[i] <= n, "Query cities not in range [1, n]");

        left[A[i]] = 1;
    }

    for (int i = 0; i < b; i += 1) {
        // sanity check
        expect(1 <= B[i] and B[i] <= n, "Query cities not in range [1, n]");

        right[B[i]] = 2;

        expect(left[B[i]] == 0, "The query sets must be disjoint");
    }

    bool ok = false;
    for (int i = 0; i <= current_edge; i += 1) {
        ok |= (left[edges_order[i].first] + right[edges_order[i].second] == 3);
        ok |= (left[edges_order[i].second] + right[edges_order[i].first] == 3);
    }

    return ok;
}


void setRoad(int a, int b) {
    int x = edges_order[current_edge].first;
    int y = edges_order[current_edge].second;

    if (x > y) { swap(x, y); }

    if (a > b) { swap(a, b); }

    DEBUG({
        fprintf(stderr, "[SetRoad]\nGiven Road\t%d\t%d\nActual Road\t%d\t%d\n\n\n\n", a, b, x, y);
    });

    if ((a == x and b == y) or (a == y and b == x)) {
        current_edge += 1;
        if (current_edge == n - 1) {
            string STRING = "Ok! Used ";
            STRING += to_string(num_steps);// + to_string(10) + " queries";
            finish("Ok! Used " + to_string(num_steps) + " queries");
        }
    } else {
        finish("Wrong guessed road! Actual road [" + to_string(x) + ", " + to_string(y) + "]" +
            "\tGot [" + to_string(a) + ", " + to_string(b) + "]");
    }
}

void startGrader() {
    // read graph from input
    ifstream fin("icc.in");
    fin >> n;

    edges_order.resize(n - 1);
    for (int i = 0; i < n - 1; i += 1) {
        fin >> edges_order[i].first >> edges_order[i].second;
    }

    current_edge = 0;
    num_steps = 0;
}

int numCities() {
    return n;
}

void quietFinish() {
    finish("Not all roads have been guessed.");
}

}
#endif // __GRADERLIB_CPP__
