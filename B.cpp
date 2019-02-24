/**
  *  Worg
  */
#include <map>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 25;

int mat[MAX_N][MAX_N];
int wh[MAX_N];
int N, M;

map< pair< int,int >, int > Map;

int main() {
    cin >> N >> M;
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            cin >> mat[i][j];
        }
    }
    int no = 0;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            wh[mat[i][j]] = j;
        }
        int cnt = 0;
        pair< int,int > A;
        pair< int,int > B;
        for(int j = 1; j <= M; j++) {
            if(mat[i][j] != j) {
                cnt ++;
                wh[mat[i][j]] = wh[j];
                swap(mat[i][j], mat[i][wh[j]]);
                if(cnt == 1) {
                    A = make_pair(j, wh[j]);
                } else {
                    B = make_pair(j, wh[j]);
                }
            }
        }
        if(cnt > 2) {
            cout << "NO"; return 0;
        } else if(cnt == 2) {
            no ++;
            Map[A] ++;
            Map[B] ++;
        }
    }
    if(no == 0) {
        cout << "YES"; return 0;
    }

    bool ok = false;
    for(map< pair< int,int >, int >::iterator it = Map.begin(); it != Map.end(); it++) {
        if(it->second == no) {
            ok = true; break;
        }
    }

    if(ok) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}
