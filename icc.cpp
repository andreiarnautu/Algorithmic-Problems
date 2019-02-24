/**
  *  Worg
  */
#include "icc.h"

#include <vector>
#include <random>
#include <algorithm>

using namespace std;

const int MAX_N = 1 + 100;

/*---------------------------*/
vector< int > comps[MAX_N];
int N;
vector< int > X, Y;
/*---------------------------*/


void initComps() {
    for(int i = 1; i <= N; i++) {
        comps[i].push_back(i);
    }
}

bool Verif(vector< int > Left, vector< int > Right) {
    vector< int > first, second;

    for(int i = 0; i < (int)Left.size(); i++) {
        for(vector< int >::iterator it = comps[Left[i]].begin(); it != comps[Left[i]].end(); it++) {
            first.push_back(*it);
        }
    }
    for(int i = 0; i < (int)Right.size(); i++) {
        for(vector< int >::iterator it = comps[Right[i]].begin(); it != comps[Right[i]].end(); it++) {
            second.push_back(*it);
        }
    }

    return (query((int)first.size(), (int)second.size(), first.data(), second.data()));
}

int GuessF(vector< int > First, vector< int > Second, int left, int right) {
    if(left == right) {
        return First[left];
    } else {
        int mid = (left + right) >> 1;

        vector< int > vec1, vec2;
        for(int i = left; i <= mid; i++) {
            for(vector< int >::iterator it = comps[First[i]].begin(); it != comps[First[i]].end(); it++) {
                vec1.push_back(*it);
            }
        }
        for(int i = 0; i < (int)Second.size(); i++) {
            for(vector< int >::iterator it = comps[Second[i]].begin(); it != comps[Second[i]].end(); it++) {
                vec2.push_back(*it);
            }
        }

        if(query((int)vec1.size(), (int)vec2.size(), vec1.data(), vec2.data())) {
            return GuessF(First, Second, left, mid);
        } else {
            return GuessF(First, Second, mid + 1, right);
        }
    }
}

int guessFirstComponent(int compCount) {
    vector< int > left, right;

    for(int i = 1 << 6; i >= 1; i >>= 1) {

        for(int j = 1; j <= compCount; j++) {
            if(i & j) {
                left.push_back(j);
            } else {
                right.push_back(j);
            }
        }
        if(!left.size() || !right.size()) {left.clear(); right.clear();continue;}

        if(Verif(left, right)) {
            X = left; Y = right; return false;
        } else {
            left.clear(); right.clear();
        }
    }

    return 0;
}

int guessFirstNode(vector< int > v1, vector< int > v2, int left, int right) {
    if(left == right) {
        return v1[left];
    } else {
        int mid = (left + right) >> 1;

        vector< int > vec;
        for(int i = left; i <= mid; i++) {
            vec.push_back(v1[i]);
        }

        if(query((int)vec.size(), (int)v2.size(), vec.data(), v2.data())) {
            return guessFirstNode(v1, v2, left, mid);
        } else {
            return guessFirstNode(v1, v2, mid + 1, right);
        }
    }
}

void run(int n) {
    N = n;
    int compCount = N;

    initComps();

    for(int roads = 0; roads < N - 1; roads++) {
        /* we have to guess the current road, but first we want to guess the connected components that contain the nodes */
        int firstComponent = guessFirstComponent(compCount);
        int rightComponent = 0;


        vector< int > v1;
        vector< int > v2;
        for(int i : X) {
                for(vector< int >::iterator it = comps[i].begin(); it != comps[i].end(); it++) {
                    v2.push_back(*it);
                }
        }
        for(int i : Y) {
                for(vector< int >::iterator it = comps[i].begin(); it != comps[i].end(); it++) {
                    v1.push_back(*it);
                }
        }


        int firstNode = guessFirstNode(v1, v2, 0, (int)v1.size() - 1);
        int secondNode = guessFirstNode(v2, v1, 0, (int)v2.size() - 1);

        for(int i = 1; i <= compCount; i++) {
            for(vector< int >::iterator it = comps[i].begin(); it != comps[i].end(); it++) {
                if(secondNode == *it) {
                    rightComponent = i;
                }
            }
        }
        for(int i = 1; i <= compCount; i++) {
            for(vector< int >::iterator it = comps[i].begin(); it != comps[i].end(); it++) {
                if(firstNode == *it) {
                    firstComponent = i;
                }
            }
        }



        setRoad(firstNode, secondNode);
        for(int i = 0; i < (int)comps[rightComponent].size(); i++) {
            comps[firstComponent].push_back(comps[rightComponent][i]);
        }
        comps[rightComponent].clear();

        swap(comps[compCount], comps[rightComponent]);
        compCount--;
    }
}
