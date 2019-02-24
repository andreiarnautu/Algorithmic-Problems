/**
  *  Worg
  */
#include <deque>
#include <cstdio>
#include <algorithm>

using namespace std;
FILE *fin = freopen("calandrinon.in", "r", stdin);
FILE *fout = freopen("calandrinon.out", "w", stdout);

const int MAX_N = 1 + 1000000,
          sigma = 30;

deque < int > pos[sigma];

char text[MAX_N];
int n, maxVal = 'z' - 'a', lastPos;
bool inText[MAX_N], suntElemente;

void insertPositions() {

    for(int i = 0; i < n; ++i) {

        int val = text[i] - 'a';
        pos[val].push_back(i);
    }

    lastPos = MAX_N;
    for(int i = 0; i <= maxVal; ++i)
        if(!pos[i].empty())
            lastPos = min(lastPos, pos[i].back());
}

void findCharacter(int x) {

    int bestVal = 100;

    for(int i = maxVal; i >= 0; --i)
        if(!pos[i].empty()) {

            if(pos[i].front() <= lastPos)
                bestVal = i;
        }

    if(bestVal == 100)
        return;

    int place = pos[bestVal].front();
    printf("%c", 'a' + bestVal);
    pos[bestVal].clear();

    for(int i = 0; i <= maxVal; ++i)
        while(!pos[i].empty() && pos[i].front() < place)
            pos[i].pop_front();
}

void updateLastPos() {

    lastPos = MAX_N;
    suntElemente = false;
    for(int i = 0; i <= maxVal; ++i)
        if(!pos[i].empty()) {

            lastPos = min(lastPos, pos[i].back());
            suntElemente = true;
        }
}

int main() {

    scanf("%d ", &n);
    gets(text);
    insertPositions();
    suntElemente = true;
    for(int i = 0; i < n && suntElemente; ++i) {

        findCharacter(i);
        updateLastPos();

    }
    return 0;
}
